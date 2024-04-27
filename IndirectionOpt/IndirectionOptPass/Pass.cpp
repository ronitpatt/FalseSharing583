#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/DerivedTypes.h" // For PointerType
#include "llvm/Support/Casting.h" // For cast<>
#include "llvm/ADT/SmallVector.h"

#include  <iostream>

using namespace llvm;

namespace {

struct IndirectionOpt : public PassInfoMixin<IndirectionOpt> {

PreservedAnalyses run(Module &M, ModuleAnalysisManager &MAM) {
  LLVMContext &Context = M.getContext();
  const DataLayout &DL = M.getDataLayout();

  // TODO: right now, just looping over the global arrays. I have the other if-conditions to check for heap allocated arrays, 
  // but I'll add that in once Indirection  works for global arrays 
  for (GlobalVariable &GV : M.globals()) {
    if (GV.hasInitializer()) {
      Constant *Init = GV.getInitializer();
      errs() << "GV: " << GV.getName() << " Type: " << *Init->getType() << "\n";


      if (ArrayType *AT = dyn_cast<ArrayType>(Init->getType())) {
        // found an array
        errs() << "Transforming array: " << GV.getName() << "\n";

        // assuming we're working with arrays of chars/bytes
        Type *IntType = Type::getInt8Ty(Context);
        Type *IntPtrType = Type::getInt8PtrTy(Context);
        unsigned NumElements = AT->getNumElements();
        errs() << NumElements << "\n";

        // Assuming the first element should be even-indexed
        unsigned NumOddElements = NumElements / 2;
        unsigned NumEvenElements = (NumElements + 1) / 2;

        // create the new arrays for odd and even elements (new chunks per processor; assuming 2 processors 
        // (even elemnts are one processor, odd belong to the other))
        ArrayType *OddType = ArrayType::get(IntType, NumOddElements);
        ArrayType *EvenType = ArrayType::get(IntType, NumEvenElements);
        GlobalVariable *OddGV = new GlobalVariable(M, OddType, GV.isConstant(), GV.getLinkage(), nullptr, GV.getName() + ".odd");
        GlobalVariable *EvenGV = new GlobalVariable(M, EvenType, GV.isConstant(), GV.getLinkage(), nullptr, GV.getName() + ".even");
        
        // create the new array of pointers (i'm not modifying the original global array in-place; this will be copied into the original array)
        ArrayType *PtrArrayType = ArrayType::get(IntPtrType, NumElements);
        GlobalVariable *PtrArrayGV = new GlobalVariable(M, PtrArrayType, GV.isConstant(), GV.getLinkage(), nullptr, GV.getName() + ".ptr");

        // create the buffer arrays (temporarily store each processor's elements)
        std::vector<Constant*> OddElements;
        std::vector<Constant*> EvenElements;

        // find all of the actual even and odd data pieces
        for (unsigned i = 0; i < NumElements; ++i) {
          Constant *ElementValue = dyn_cast<Constant>(Init->getAggregateElement(i));
          if (i % 2 == 0) {
            EvenElements.push_back(ElementValue);
          } else {
            OddElements.push_back(ElementValue);
          }
        }

        Constant *OddArrayInit = ConstantArray::get(OddType, OddElements);
        Constant *EvenArrayInit = ConstantArray::get(EvenType, EvenElements);
        
        //TODO: padd OddGV and EvenGV to the starts of cache blocks


        // fill the odd and even arrays (new chunks per processor)
        OddGV->setInitializer(OddArrayInit);
        EvenGV->setInitializer(EvenArrayInit);

        // getting each elements pointer from the new chunks allocated to each processor (EvenGV, OddGV)
        // we'll put these pointers to elements in PtrElements
        std::vector<Constant*> PtrElements;

        Type *ElemType = Type::getInt8Ty(Context); // The element type of the arrays
        for (unsigned i = 0; i < NumElements; ++i) {
          Constant *ElementPtr;

          std::vector<Constant*> Indices;
          Indices.push_back(ConstantInt::get(Type::getInt32Ty(Context), 0)); // Index within the array
          Indices.push_back(ConstantInt::get(Type::getInt32Ty(Context), i / 2)); // Either Even or Odd index

          if (i % 2 == 0) { // Even element
            ElementPtr = ConstantExpr::getGetElementPtr(EvenType, EvenGV, Indices, true /* is in bounds */);
          } else { // Odd element
            ElementPtr = ConstantExpr::getGetElementPtr(OddType, OddGV, Indices, true /* is in bounds */);
          }

          PtrElements.push_back(ElementPtr);

          // Print the element address expression
          errs() << "Iteration: " << i << "\n";
          errs() << "Element ptr: " << *ElementPtr << "\n"; // This should print the GEP expression, not the array itself
        }


        // initialize the array of pointers with PtrElements (where we just put the pointers to even/odd elems)
        PtrArrayGV->setInitializer(ConstantArray::get(PtrArrayType, PtrElements));
        
        GlobalVariable *wordTwoGV = M.getNamedGlobal("word_two");
        SmallVector<User*, 8> Users(wordTwoGV->user_begin(), wordTwoGV->user_end());

        for (User* user : Users) {
          if (llvm::Instruction *inst = llvm::dyn_cast<llvm::Instruction>(user)) {
            // Now, iterate over the users of this instruction.
            llvm::SmallVector<llvm::User*, 8> instUsers(inst->user_begin(), inst->user_end());
            for (llvm::User* instUser : instUsers) {

                //if (auto* inst = dyn_cast<Instruction>(user)) {
                if (llvm::Instruction *userInst = llvm::dyn_cast<llvm::Instruction>(instUser)) {
                  errs() << "user instruction of: " << *userInst  << " user is " << *instUser << "\n";

                  IRBuilder<> Builder(userInst);

                  Type* IntPtrType = Builder.getInt8PtrTy(); // Get the LLVM type for 'i8*'.

                  Builder.SetInsertPoint(userInst);

                  // Assuming the operand is used within a GEP instruction
                  if (auto* GEP = dyn_cast<GetElementPtrInst>(userInst)) {
                    errs() << "found instruction with usage of old array: " << *GEP << "\n";

                    Value* index = GEP->getOperand(1);
                    //errs() << "operand" << *index << "\n";

                    std::vector<Value*> IndexVec = {Builder.getInt64(0), index}; // Where index is the LLVM value for your actual index.

                    // Create a GEP to access the pointer in the new array of pointers
                    Value* ptrGEP = Builder.CreateInBoundsGEP(IntPtrType, PtrArrayGV, index, "");

                    // Load the pointer to i8 (char*)
                    LoadInst* loadedPointer = Builder.CreateLoad(Builder.getInt8PtrTy(), ptrGEP, "");

                    // Replace the old GEP's usage with the loaded i8 value
                    GEP->replaceAllUsesWith(loadedPointer);

                    // Remove the old GEP from the parent basic block
                    GEP->eraseFromParent();

                    //inst->eraseFromParent();
                  }
                }

            }
          }
        }
    
        errs() << "flag:\n";

        // Now remove the original global variable
        // wordTwoGV->eraseFromParent();
      }

    }
    //temp:
    break;
  }

errs() << "Module state before potential crash: \n";
M.print(llvm::errs(), nullptr);

  // Since we are altering the IR in place, we need to return `PreservedAnalyses::none()`.
  return PreservedAnalyses::none();
}
};

}

extern "C" ::llvm::PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK llvmGetPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "IndirectionOpt", "v0.1",
    [](PassBuilder &PB) {
      PB.registerPipelineParsingCallback(
        [](StringRef Name, ModulePassManager &FPM,
        ArrayRef<PassBuilder::PipelineElement>) {
          if(Name == "func-name"){
            FPM.addPass(IndirectionOpt());
            return true;
          }
          return false;
        }
      );
    }
  };
}
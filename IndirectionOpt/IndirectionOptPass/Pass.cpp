#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

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
      if (ArrayType *AT = dyn_cast<ArrayType>(Init->getType())) {
        // found an array
        errs() << "Transforming array: " << GV.getName() << "\n";

        // assuming we're working with arrays of chars/bytes
        Type *IntType = Type::getInt8Ty(Context);
        Type *IntPtrType = Type::getInt8PtrTy(Context);
        unsigned NumElements = AT->getNumElements();

        // create the new arrays for odd and even elements (new chunks per processor; assuming 2 processors 
        // (even elemnts are one processor, odd belong to the other))
        ArrayType *OddType = ArrayType::get(IntType, (NumElements + 1) / 2);
        ArrayType *EvenType = ArrayType::get(IntType, NumElements / 2);
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
          errs() << "Element Pos: " << i << ", Loc: " << ElementValue << ", Val: " << *ElementValue << "\n";
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

        // Print the initializers to verify their correctness
        errs() << "\n\nOdd array loc: " << OddArrayInit << "\n";
        errs() << "Odd array initializer: " << *OddArrayInit << "\n";

        errs() << "Even array loc: " << EvenArrayInit << "\n";
        errs() << "Even array initializer: " << *EvenArrayInit << "\n\n\n";


        // Code works until this point. Two new chunks of memory are created: EvenGV and OddGV. 
          // EvenGV stores all of the even elements, OddGV stores all of the odd elements. 
// ------------------------------------------------------------


        std::vector<Constant*> PtrElements;

//method 1 for getting each elements pointer from the new chunks allocated to each processor (EvenGV, OddGV)
//we'll put these pointers to elements in PtrElements. 

/*
  Example:
  word[] = h e l l o w o r l d      (from test.c)
          0 1 2 3 4 5 6 7 8 9      (index)

  Each element of PtrElements should point individually to elements from OddGV and EvenGV 
  which contain the contents of the array "word", split up by processor.

  PtrElements: [ &EvenGV[0], &OddGV[0], &EvenGV[1], &OddGV[1], ... ]
*/

        // Even elements iteration. (this is where my problems lie rn. focusing on just getting the EvenGV ptrs for each element)
        for (unsigned i = 0; i < EvenElements.size(); ++i) {
          std::vector<Constant*> IdxList = {
            ConstantInt::get(Type::getInt32Ty(Context), 0),
            ConstantInt::get(Type::getInt32Ty(Context), i)
          };
          
          Constant *GEP = ConstantExpr::getGetElementPtr(
            EvenType, EvenGV, ArrayRef<Constant*>(IdxList), false /* is in bounds */);
          
          errs() << "\nIteration: " << i << "\n";
          errs() << "Element ptr: " << GEP << "\n"; // This should print the GEP expression, not the array itself
          errs() << "Element: " << *GEP << "\n"; // This should print the GEP expression, not the array itself
          
          /* 
            context:
              This is what OddGV and EvenGV are up until this point; they're right "H e l l o w o r l d \0")
              OddGV: [5 x i8] c"elwrd"     
              EvenGV: [6 x i8] c"hlool\00"

            these lines should just print something like:
              (first param is the type, a 6 element array of bytes; second param is array itself; 
              third param is starting index, fourth param is offset) ----> 
              so these lines should grab the ptrs for the 0th,1st, etc. elements of word.even (this is EvenGV)

              ptr getelementptr inbounds ([6 x i8], ptr @word.even, i32 0, i32 0)
              ptr getelementptr inbounds ([6 x i8], ptr @word.even, i32 0, i32 1)
              ptr getelementptr inbounds ([6 x i8], ptr @word.even, i32 0, i32 2)
              ptr getelementptr inbounds ([6 x i8], ptr @word.even, i32 0, i32 4)
              ptr getelementptr inbounds ([6 x i8], ptr @word.even, i32 0, i32 5)
              ptr getelementptr inbounds ([6 x i8], ptr @word.even, i32 0, i32 6)

            instead..
            I get:

              @word.even = global [5 x i8] c"hlool\00"
              ptr getelementptr inbounds ([5 x i8], ptr @word.even, i32 0, i32 1)
              ptr getelementptr inbounds ([5 x i8], ptr @word.even, i32 0, i32 2)
              ptr getelementptr inbounds ([5 x i8], ptr @word.even, i32 0, i32 3)
              ptr getelementptr inbounds ([5 x i8], ptr @word.even, i32 0, i32 4)
              ptr getelementptr inbounds ([5 x i8], ptr @word.even, i64 1, i32 0)

            1. the first line is printing the whole even array for some reason. it's also 5xi8 isntead of 6xi8
            2. the last line has the wrong offset (I think it's overflowing because of the first issue).

            So basically, I'm not sure why getGetElementPtr isn't working when I want the pointer of the 0th element
              as right now it's printing the whole array.

          */

          PtrElements.push_back(GEP);
        }

        // // Odd elements iteration.
        // for (unsigned i = 0; i < OddElements.size(); ++i) {
        //   std::vector<Constant*> IdxList = {
        //     ConstantInt::get(Type::getInt32Ty(Context), 0),
        //     ConstantInt::get(Type::getInt32Ty(Context), i)
        //   };

        //   Constant *GEP = ConstantExpr::getGetElementPtr(
        //     OddType, OddGV, ArrayRef<Constant*>(IdxList), true /* is in bounds */);

        //   // For odd elements, we only start adding them after we've added all even
        //   // elements, hence the index should be offset by the number of even elements.
        //   PtrElements.push_back(GEP);
        // }


//method 2 for getting each elements pointer from the new chunks allocated to each processor (EvenGV, OddGV)
//we'll put these pointers to elements in PtrElements

        // Type *ElemType = Type::getInt8Ty(Context); // The element type of the arrays
        // for (unsigned i = 0; i < NumElements; ++i) {
        //   Constant *ElementPtr;

        //   std::vector<Constant*> Indices;
        //   Indices.push_back(ConstantInt::get(Type::getInt32Ty(Context), 0)); // Index within the array
        //   Indices.push_back(ConstantInt::get(Type::getInt32Ty(Context), i / 2)); // Either Even or Odd index

        //   if (i % 2 == 0) { // Even element
        //     ElementPtr = ConstantExpr::getGetElementPtr(
        //       EvenType->getElementType(), 
        //       EvenGV, 
        //       Indices,
        //       true /* is in bounds */
        //     );
        //   } else { // Odd element
        //     ElementPtr = ConstantExpr::getGetElementPtr(
        //       OddType->getElementType(), 
        //       OddGV, 
        //       Indices,
        //       true /* is in bounds */
        //     );
        //   }

        //   PtrElements.push_back(ElementPtr);

        //   // Print the element address expression
        //   errs() << "Iteration: " << i << "\n";
        //   errs() << "Element ptr: " << *ElementPtr << "\n"; // This should print the GEP expression, not the array itself
        // }

  // temporary; just want to terminate the program early since the above issue causes it to infinetnly loop
  return PreservedAnalyses::none();

        // // initialize the array of pointers with PtrElements (where we just put the pointers to even/odd elems)
        // PtrArrayGV->setInitializer(ConstantArray::get(PtrArrayType, PtrElements));

        // // replace all uses of the original array with this new array of pointers
        // GV.replaceAllUsesWith(PtrArrayGV);

        // // remove the original global variable if it's not needed anymore
        // GV.eraseFromParent();
      }
    }
  }

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

#include "llvm/Analysis/BlockFrequencyInfo.h"
#include "llvm/Analysis/BranchProbabilityInfo.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/Support/Format.h"

#include "llvm/Analysis/TargetTransformInfo.h"

#include  <iostream>
#include <unordered_map>
#include <vector>

using namespace llvm;

namespace {

struct HW1Pass : public PassInfoMixin<HW1Pass> {

  PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {
    // These variables contain the results of some analysis passes.
    // Go through the documentation to see how they can be used.

   
    // FuncName, DynOpCount, %IALU, %FALU, %MEM, %Biased-Br, %Unbiased-Br, %Others, given a singular function F
    // errs() << ", " << DynOpCounts;

    // size_t cache_line = cache_line_size();

    // std::unordered_map<int, std::vector<std::pair<int, IRBuilder<>>> idx_to_align;
    std::map<int, std::vector<std::pair<int, AllocaInst*>>> idx_to_align;


    unsigned num_arrays = 0;
    
    unsigned CacheBlockSize = 64;


    Type *ElemTy;

    // IRBuilder<> Builder;

    AllocaInst *Alloca_global;

    errs() << "FLAG 1\n ";

    LLVMContext &Ctx = F.getContext();


    for (auto &BB : F) {
      for (auto &I : BB) {
        if (auto *Alloca = dyn_cast<AllocaInst>(&I)) {
          num_arrays++;
          // assume num processors 
          errs() << "FLAG 2\n ";
          
          if (Alloca->getAllocatedType()->isArrayTy()) { // finds array type: 
            
            errs() << "FLAG 3\n ";

            Alloca_global = Alloca;
            // IRBuilder<> Builder(Alloca_global);


            // Query cache block size information

            errs() << "FLAG 4\n ";

            ElemTy = Alloca->getAllocatedType()->getArrayElementType();
            auto &TTI = FAM.getResult<TargetIRAnalysis>(F);
            uint64_t ElemSize = F.getParent()->getDataLayout().getTypeAllocSize(ElemTy);
            unsigned BaseAlignment = alignof(Alloca->getAllocatedType()->getArrayElementType());

            Value *ArrayPtr = Alloca;

            for (unsigned i = 0; i < Alloca->getAllocatedType()->getArrayNumElements(); ++i) {
              errs() << "Num Elements\n ";
              // get alignment memory

              // 1. get current spot in memory
              // 2. switch them around

              unsigned Offset = i * sizeof(int); // Example: Assuming integer array, 4 bytes per element

              // Create GEP (GetElementPtr) instruction to access the i-th element
              IRBuilder<> Builder(&BB, BB.getFirstInsertionPt());
              Value *ElementPtr = Builder.CreateGEP(ElemTy, ArrayPtr, {Builder.getInt32(0), Builder.getInt32(i)});

               errs() << "Heres\n ";

              // Print the address of the current element

              Value *ElementAddr = Builder.CreatePtrToInt(ElementPtr, Type::getInt64Ty(Ctx));
              Function *PtrToIntFunc = Intrinsic::getDeclaration(F.getParent(), Intrinsic::ptrtoint, {ElementAddr->getType()});
              Builder.CreateCall(PtrToIntFunc, {ElementAddr}, "");
            }
            // Builder(Alloca);

            for (unsigned i = 0; i < dyn_cast<ConstantInt>(Alloca->getArraySize())->getZExtValue(); ++i) { // save cache block for every element

              unsigned ElemAlignment = std::max(BaseAlignment, CacheBlockSize * (i + 1));
              unsigned NumCacheBlocks = (ElemSize + ElemAlignment - 1) / ElemAlignment; // helper var for debugging
              
              // auto *NewAlloca = Builder.CreateAlloca(ElemTy);
              idx_to_align[i].push_back({ElemAlignment, Alloca});

              // idx_to_align[i].push_back(std::make_pair(ElemAlignment, Builder));

              // NewAlloca->setAlignment(Align(ElemAlignment));
            }
            
            errs() << "Found array: " << *Alloca << "\n";
          }
        }
      }
    }

    // Alignment : 

   

    for (const auto& pair : idx_to_align) {
        for(auto x: pair.second){ // pair of alignment idx and alloca address
          IRBuilder<> Builder(x.second);
          auto *NewAlloca = Builder.CreateAlloca(ElemTy);
          errs() << "X First: " << x.first << "\n";
          NewAlloca->setAlignment(Align(x.first));
        }
    }


    // find an array and do some indirection

    // put each element in its own cache block 

    errs() << "Hello World" << "\n";

    return PreservedAnalyses::all();
  }
};
}

extern "C" ::llvm::PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK llvmGetPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "HW1Pass", "v0.1",
    [](PassBuilder &PB) {
      PB.registerPipelineParsingCallback(
        [](StringRef Name, FunctionPassManager &FPM,
        ArrayRef<PassBuilder::PipelineElement>) {
          if(Name == "hw1"){
            FPM.addPass(HW1Pass());
            return true;
          }
          return false;
        }
      );
    }
  };
}

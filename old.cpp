#include "llvm/Analysis/BlockFrequencyInfo.h"
#include "llvm/Analysis/BranchProbabilityInfo.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/Support/Format.h"

#include "llvm/Analysis/TargetTransformInfo.h"

#include  <iostream>

using namespace llvm;

namespace {

struct HW1Pass : public PassInfoMixin<HW1Pass> {

  PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {
    // These variables contain the results of some analysis passes.
    // Go through the documentation to see how they can be used.

   
    // FuncName, DynOpCount, %IALU, %FALU, %MEM, %Biased-Br, %Unbiased-Br, %Others, given a singular function F
    // errs() << ", " << DynOpCounts;

    // size_t cache_line = cache_line_size();

    // vector<int> idx_to_alignment;

    // unordered_map<int, vector<int>> idx_to_align;

    unsigned num_arrays = 0;
    
    unsigned CacheBlockSize = 64;



    for (auto &BB : F) {
      for (auto &I : BB) {
        if (auto *Alloca = dyn_cast<AllocaInst>(&I)) {
          num_arrays++;
          // assume num processors 
          if (Alloca->getAllocatedType()->isArrayTy()) {

            Type *ElemTy = Alloca->getAllocatedType()->getArrayElementType();

            auto &TTI = FAM.getResult<TargetIRAnalysis>(F);
            // Query cache block size information

            unsigned ElemAlignment = std::max( static_cast<unsigned>(Alloca->getAlign().value()), CacheBlockSize); // not fetching cache block size correctly
            
            Alloca->setAlignment(Align(ElemAlignment));

            uint64_t ElemSize = F.getParent()->getDataLayout().getTypeAllocSize(ElemTy);

            unsigned NumCacheBlocks = (ElemSize + CacheBlockSize - 1) / CacheBlockSize;

            IRBuilder<> Builder(Alloca);

            for (unsigned i = 0; i < NumCacheBlocks; ++i) { // save cache block for every element
              auto *NewAlloca = Builder.CreateAlloca(ElemTy);
              NewAlloca->setAlignment(Align(ElemAlignment));
            }
            
            errs() << "Found array: " << *Alloca << "\n";
          }
        }
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
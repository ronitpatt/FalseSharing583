
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

    std::unordered_map<int, std::vector<int>> idx_to_align;

    unsigned num_arrays = 0;
    
    unsigned CacheBlockSize = 64;


    Type *ElemTy;

    // IRBuilder<> Builder;

    AllocaInst *Alloca_global;


    for (auto &BB : F) {
      for (auto &I : BB) {
        if (auto *Alloca = dyn_cast<AllocaInst>(&I)) {
          num_arrays++;
          // assume num processors 
          
          if (Alloca->getAllocatedType()->isArrayTy()) {

            Alloca_global = Alloca;
            // IRBuilder<> Builder(Alloca_global);


            // Query cache block size information

            ElemTy = Alloca->getAllocatedType()->getArrayElementType();
            auto &TTI = FAM.getResult<TargetIRAnalysis>(F);
            uint64_t ElemSize = F.getParent()->getDataLayout().getTypeAllocSize(ElemTy);
            unsigned BaseAlignment = alignof(Alloca->getAllocatedType()->getArrayElementType());

            // Builder(Alloca);

            for (unsigned i = 0; i < dyn_cast<ConstantInt>(Alloca->getArraySize())->getZExtValue(); ++i) { // save cache block for every element

              unsigned ElemAlignment = std::max(BaseAlignment, CacheBlockSize * (i + 1));
              unsigned NumCacheBlocks = (ElemSize + ElemAlignment - 1) / ElemAlignment; // helper var for debugging
              
              // auto *NewAlloca = Builder.CreateAlloca(ElemTy);
              idx_to_align[i].push_back(ElemAlignment);
              // NewAlloca->setAlignment(Align(ElemAlignment));
            }
            
            errs() << "Found array: " << *Alloca << "\n";
          }
        }
      }
    }

    // Alignment : 


    // for (const auto& pair : idx_to_align) {
    //     for(int x: pair.second){
    //       auto *NewAlloca = Builder.CreateAlloca(ElemTy);
    //       NewAlloca->setAlignment(Align(x));
    //     }
    // }


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

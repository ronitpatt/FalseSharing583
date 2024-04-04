#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include  <iostream>

using namespace llvm;

#include <stdio.h>

size_t cache_line_size() {
    FILE * p = 0;
    p = fopen("/sys/devices/system/cpu/cpu0/cache/index0/coherency_line_size", "r");
    unsigned int i = 0;
    if (p) {
        fscanf(p, "%d", &i);
        fclose(p);
    }
    return i;
}


namespace {
  struct FsharingPass : public PassInfoMixin<FsharingPass> {
      PreservedAnalyses run(Module &M, ModuleAnalysisManager &) {
          size_t cache_line = cache_line_size();
          for (GlobalVariable &GV : M.globals()) {
              if (GV.hasInitializer()) {
                Constant *Init = GV.getInitializer();
                GV.setAlignment(Align(cache_line));
                errs() << Init->getType()->isStructTy() << "\n";
                if (Init->getType()->isStructTy()){
                    StructType *ST = dyn_cast<StructType>(Init->getType());
                    for (unsigned i = 0; i < ST->getNumElements(); i++) {
                        Type *T = ST->getElementType(i);
                        T->
                    }
                }
                errs() << "Found global variable: " << GV.getName() << "\n";
            }
          }
          return PreservedAnalyses::all();
      }
  };
}



extern "C" ::llvm::PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK llvmGetPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "FsharingPass", "v0.1",
    [](PassBuilder &PB) {
      PB.registerPipelineParsingCallback(
        [](StringRef Name, ModulePassManager &MPM,
        ArrayRef<PassBuilder::PipelineElement>) {
          if (Name == "fsharing-pass") {
            MPM.addPass(FsharingPass());
            return true;
          }
          return false;
        }
      );
    }
  };
}
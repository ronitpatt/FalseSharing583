#include <stdio.h>
#include "llvm/IR/InstVisitor.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Instruction.h"
#include  <iostream>
#include  <set>
#include <map>
#include "Pass.h"

namespace llvm {
namespace {
  void printThings(Module& M) {
    for (auto &F : M) {
      if (F.getName().find("doPrint") != std::string::npos) {
        continue;
      }
      ReplaceTypeVisitor visitor{};
      visitor.visit(F);
    }
  }

  struct RPass : public PassInfoMixin<RPass> {
      PreservedAnalyses run(Module &M, ModuleAnalysisManager &) {
        errs () << "HI\n"; 
        printThings(M);
        return PreservedAnalyses::all();
      }
  };
}



extern "C" ::llvm::PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK llvmGetPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "PrintPass", "v0.1",
    [](PassBuilder &PB) {
      PB.registerPipelineParsingCallback(
        [](StringRef Name, ModulePassManager &MPM,
        ArrayRef<PassBuilder::PipelineElement>) {
          if (Name == "print-pass") {
            MPM.addPass(RPass());
            return true;
          }
          return false;
        }
      );
    }
  };
}
};
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
#include "llvm/Support/raw_ostream.h"
#include "Pass.h"
#include <fstream>
#include <sstream>
#include <unordered_map>

namespace llvm {
namespace {

  void replaceUsesInFunction(Function* func, StructType* oldType, StructType* newType, std::vector<int> &order) {
      ReplaceTypeVisitor visitor{oldType, newType, order};
      visitor.visit(func);
  }

  void replaceType(Module &M, StructType *oldStructType, StructType *newStructType, std::vector<GlobalVariable*> gvs, std::vector<int> &order) {
    for (auto &F : M) {
      replaceUsesInFunction(&F, oldStructType, newStructType, order);
    }
  }

  void padStruct(StructType* oldStructType, Module& M, std::vector<int> newOrder) {
    std::vector<Type *> fieldTypes;
    
    for (unsigned i = 0; i < oldStructType->getNumElements(); ++i) {
        fieldTypes.push_back(oldStructType->getElementType(newOrder[i]));
    }
    StructType *newStructType = StructType::create(M.getContext(), fieldTypes, oldStructType->getName().str() + "reorder");
    GlobalVariable* globalVar = new GlobalVariable(M, newStructType, false, GlobalValue::ExternalLinkage, nullptr, "myGlobalVar");
    replaceType(M, oldStructType, newStructType, {}, newOrder);
  }

  struct ReorderPass : public PassInfoMixin<ReorderPass> {
      PreservedAnalyses run(Module &M, ModuleAnalysisManager &) {
        std::ifstream file ("reorder.txt");
        std::string line, structTypeName;
        std::unordered_map<std::string, std::vector<int> > structOrder;
        
        while (getline(file, line)) {
          std::istringstream ss {line};
          ss >> structTypeName;
          structOrder[structTypeName] = {};
          int offset;
          while (ss >> offset) {
            structOrder[structTypeName].push_back(offset);
          }   
        }
        
        for (StructType* st : M.getIdentifiedStructTypes()) {
          // TODO get all labels of functions in the struct 
          if (auto iter = structOrder.find(st->getName().str()); iter != structOrder.end()) {
            padStruct(st, M, iter->second);
          }
        }
        return PreservedAnalyses::all();
      }
  };
}



extern "C" ::llvm::PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK llvmGetPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "ReorderPass", "v0.1",
    [](PassBuilder &PB) {
      PB.registerPipelineParsingCallback(
        [](StringRef Name, ModulePassManager &MPM,
        ArrayRef<PassBuilder::PipelineElement>) {
          if (Name == "reorder-pass") {
            MPM.addPass(ReorderPass());
            return true;
          }
          return false;
        }
      );
    }
  };
}
};
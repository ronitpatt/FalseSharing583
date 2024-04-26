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

  void replace_types(Module &M, StructType *oldStructType, StructType *newStructType, std::vector<GlobalVariable*> gvs, std::vector<int> &order) {
    for (auto &F : M) {
      errs() << F.getName() << "\n";
      replaceUsesInFunction(&F, oldStructType, newStructType, order);
      
    }
  }

  void padStruct(StructType* OldStructType, Module& M, std::vector<int> newOrder) {
    std::vector<Type *> FieldTypes;

    
    for (unsigned i = 0; i < OldStructType->getNumElements(); ++i) {
        //errs() << "PADDING STRUCT" << OldStructType->getElement(i) << "\n";
        FieldTypes.push_back(OldStructType->getElementType(newOrder[i]));
    }
    StructType *newStructType = StructType::create(M.getContext(), FieldTypes, OldStructType->getName().str() + "reorder");
    GlobalVariable* globalVar = new GlobalVariable(M, newStructType, false, GlobalValue::ExternalLinkage, nullptr, "myGlobalVar");
    replace_types(M, OldStructType, newStructType, {}, newOrder);
  }

  struct ReorderPass : public PassInfoMixin<ReorderPass> {
      PreservedAnalyses run(Module &M, ModuleAnalysisManager &) {
        errs () << "HI\n"; 
        std::ifstream file ("reorder.txt");
        std::string line, structTypeName;
        std::unordered_map<std::string, std::vector<int> > structOrder;
        
        while (getline(file, line)) {
          errs() << "READING LINE FROM REORDER.TXT\n";
          std::istringstream ss {line};
          ss >> structTypeName;
          structOrder[structTypeName] = {};
          int offset;
          while (ss >> offset) {
            errs() << offset << " ";
            structOrder[structTypeName].push_back(offset);
          }   
          errs() << "\n";       
        }
        
        auto structlist = M.getIdentifiedStructTypes();
        for (StructType* st : structlist) {
          // TODO get all labels of functions in the struct 
          errs() << "STRUCT NAME: " << st->getName().str() << "\n";
          if (auto iter = structOrder.find(st->getName().str()); iter != structOrder.end()) {
            errs() << "FOUND STRUCT TO PAD\n";
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
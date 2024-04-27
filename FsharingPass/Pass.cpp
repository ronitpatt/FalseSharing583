
#include "Pass.h"

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



void replaceUsesInFunction(Function* func, StructType* oldType, StructType* newType) {
    ReplaceTypeVisitor visitor{oldType, newType};
    visitor.visit(func);
}

void replace_types(Module &M, StructType *oldStructType, StructType *newStructType, std::vector<GlobalVariable*> gvs) {
    std::map<Type*, Type*> struct_map;
    for (auto &F : M) {
      errs() << F.getName() << "\n";
      replaceUsesInFunction(&F, oldStructType, newStructType);
      
  }

}

void padStruct(StructType* OldStructType, Module& M, std::vector<int> toPad) {
  std::vector<Type *> FieldTypes;
  // errs() << "PADDING STRUCT" << OldStructType->getName() << "\n";
  for (unsigned i = 0; i < OldStructType->getNumElements(); ++i) {
    FieldTypes.push_back(OldStructType->getElementType(i));
    if (!toPad.size() || i != toPad[0]) {
      continue;
    }
    toPad.erase(toPad.begin());
    Type *elementType = Type::getInt8Ty(M.getContext());
    uint64_t padSize = 64 - OldStructType->getElementType(i)->getPrimitiveSizeInBits()/8;
    
    if (ArrayType* arrtype = dyn_cast<ArrayType>(OldStructType->getElementType(i))) {
      errs() << *OldStructType->getElementType(i) << "\n";
      padSize = 64 - (arrtype->getNumElements() * arrtype->getElementType()->getPrimitiveSizeInBits()/8);
    }
    if (true) {
      ArrayType *arrayType = ArrayType::get(elementType, padSize);
      FieldTypes.push_back(arrayType);
    }
  }
  
  StructType *newStructType = StructType::create(M.getContext(),FieldTypes, OldStructType->getName().str() + "padded");
  GlobalVariable* globalVar = new GlobalVariable(M, newStructType, false, GlobalValue::ExternalLinkage, nullptr, "myGlobalVar");
  replace_types(M, OldStructType, newStructType,{});
}

namespace {
  struct FsharingPass : public PassInfoMixin<FsharingPass> {
      PreservedAnalyses run(Module &M, ModuleAnalysisManager &) {
        auto structlist = M.getIdentifiedStructTypes();

        std::ifstream file ("padding.txt");
        std::string line, structTypeName;
        std::unordered_map<std::string, std::vector<int> > structOrder;
        
        while (getline(file, line)) {
          errs() << "READING LINE FROM PADDING.TXT\n";
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

        for (StructType* st : structlist) {
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
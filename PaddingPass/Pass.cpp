#include "Pass.h"

using namespace llvm;

#include <stdio.h>

size_t cacheLineSize() {
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

void replaceTypes(Module &M, StructType *oldStructType, StructType *newStructType, std::vector<GlobalVariable*> gvs) {
    for (auto &F : M) {
      replaceUsesInFunction(&F, oldStructType, newStructType);
    }
}

void padStruct(StructType* oldStructType, Module& M, std::vector<int> toPad) {
  std::vector<Type *> fieldTypes;
  int running = 0;
  for (unsigned i = 0; i < oldStructType->getNumElements(); ++i) {
    fieldTypes.push_back(oldStructType->getElementType(i));
    running += oldStructType->getElementType(i)->getPrimitiveSizeInBits()/8;
    if (!toPad.size() || i != toPad[0]) {
      continue;
    }
    toPad.erase(toPad.begin());
    Type *elementType = Type::getInt8Ty(M.getContext());
    uint64_t padSize = cacheLineSize() - running;
    running = 0;
    if (ArrayType* arrtype = dyn_cast<ArrayType>(oldStructType->getElementType(i))) {
      errs() << *oldStructType->getElementType(i) << "\n";
      padSize = cacheLineSize() - (arrtype->getNumElements() * arrtype->getElementType()->getPrimitiveSizeInBits()/8);
    }
    if (true) {
      ArrayType *arrayType = ArrayType::get(elementType, padSize);
      fieldTypes.push_back(arrayType);
    }
  }
  
  StructType *newStructType = StructType::create(M.getContext(),fieldTypes, oldStructType->getName().str() + "padded");
  GlobalVariable* globalVar = new GlobalVariable(M, newStructType, false, GlobalValue::ExternalLinkage, nullptr, "myGlobalVar");
  replaceTypes(M, oldStructType, newStructType, {});
}

namespace {
  struct PaddingPass : public PassInfoMixin<PaddingPass> {
      PreservedAnalyses run(Module &M, ModuleAnalysisManager &) {
        auto structList = M.getIdentifiedStructTypes();

        std::ifstream file ("padding.txt");
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

        for (StructType* st : structList) {
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
    LLVM_PLUGIN_API_VERSION, "PaddingPass", "v0.1",
    [](PassBuilder &PB) {
      PB.registerPipelineParsingCallback(
        [](StringRef Name, ModulePassManager &MPM,
        ArrayRef<PassBuilder::PipelineElement>) {
          if (Name == "padding-pass") {
            MPM.addPass(PaddingPass());
            return true;
          }
          return false;
        }
      );
    }
  };
}
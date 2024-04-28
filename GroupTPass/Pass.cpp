
#include "Pass.h"

using namespace llvm;

#include <stdio.h>


void replaceUsesInFunction(Function* func, StructType* oldType, StructType* newType, GlobalVariable* gv, GlobalVariable* old) {
    ReplaceTypeVisitor visitor{oldType, newType, gv, old};
    visitor.visit(func);
}

void replaceTypes(Module &M, StructType *oldStructType, StructType *newStructType, GlobalVariable* gv, GlobalVariable *old) {

    for (auto &F : M) {
      replaceUsesInFunction(&F, oldStructType, newStructType, gv, old);
    }

}

void transposeStruct(StructType* oldStructType, Module& M) {
  std::vector<Type *> FieldTypes;
  GlobalVariable* gv;
  for (llvm::GlobalVariable &globalVar : M.globals()) {
    gv = &globalVar;
    break;
  }

  int length = 0;
  for (unsigned i = 0; i < oldStructType->getNumElements(); ++i) {
    if (ArrayType* arrtype = dyn_cast<ArrayType>(oldStructType->getElementType(i))) {
      length = arrtype->getNumElements();
      FieldTypes.push_back(arrtype->getElementType());
    }
  }
  
  StructType *newStructType = StructType::create(M.getContext(), FieldTypes, oldStructType->getName().str() + "GT");
  ArrayType* newObjType = ArrayType::get(newStructType, length);
  llvm::ConstantAggregateZero *zeroInit = llvm::ConstantAggregateZero::get(newObjType);
  GlobalVariable* globalVar = new GlobalVariable(M, newObjType, false, GlobalValue::InternalLinkage, zeroInit , "transposed");
  globalVar->setAlignment(Align(16));
  gv->replaceAllUsesWith(globalVar);
  replaceTypes(M, oldStructType, newStructType, globalVar, gv);
}

namespace {
  struct GroupTPass : public PassInfoMixin<GroupTPass> {
      PreservedAnalyses run(Module &M, ModuleAnalysisManager &) {
        for (StructType* st : M.getIdentifiedStructTypes()) {
          transposeStruct(st, M);
        }
        return PreservedAnalyses::all();
      }
  };
}



extern "C" ::llvm::PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK llvmGetPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "GroupTPass", "v0.1",
    [](PassBuilder &PB) {
      PB.registerPipelineParsingCallback(
        [](StringRef Name, ModulePassManager &MPM,
        ArrayRef<PassBuilder::PipelineElement>) {
          if (Name == "groupt-pass") {
            MPM.addPass(GroupTPass());
            return true;
          }
          return false;
        }
      );
    }
  };
}

/* Hot and Cold Code Methods: 


PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {
    // These variables contain the results of some analysis passes.
    // Go through the documentation to see how they can be used.
    llvm::BlockFrequencyAnalysis::Result &bfi = FAM.getResult<BlockFrequencyAnalysis>(F);
    llvm::BranchProbabilityAnalysis::Result &bpi = FAM.getResult<BranchProbabilityAnalysis>(F);
    uint64_t DynOpCount = 0;
    for (BasicBlock &bb : F) {
      
      uint64_t BlockProfileCount = 0;

      std::optional<uint64_t> temp_count = bfi.getBlockProfileCount(&bb);

      // Check if the optional has a value
      if (temp_count.has_value()) {
        BlockProfileCount = temp_count.value();
      }
            
      for (Instruction &i : bb) {
        DynOpCount += BlockProfileCount;

        case Instruction::Alloca:
        case Instruction::Load:
        case Instruction::Store:

          // Get Array Count, store in map of element ptr to count

    

    // if hot 
      // do G and T
    // if cold 
      // do nothing

*/



/*
for each struct, if it matches the name you are looking for
get its vector elements
create new struct that has the types of each vector
then create a vector of this struct

then modify accesses to the original struct 
how?
well access to structs will be like 
obj.arr[1]
newobj[]


*/
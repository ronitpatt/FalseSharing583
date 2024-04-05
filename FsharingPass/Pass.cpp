
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
    // for (GlobalVariable * GV : gvs) {
    //   if (GV->hasInitializer()) {
    //     Constant *Init = GV->getInitializer();
    //     if (Init->getType() == oldStructType) {

    //       //GV.setInitializer(ConstantStruct::get(newStructType, {}));
    //       // Constant* newInit = new Constant(*GV.getInitializer());
    //       GlobalVariable *newGlobalVar = new GlobalVariable(
    //       /* Module */ M,
    //       /* Type */ newStructType,
    //       /* isConstant */ GV->isConstant(),
    //       /* Linkage */ GV->getLinkage(),
    //       /* Initializer */ Constant::getNullValue(newStructType),
    //       /* Name */ "new_global_var",
    //       /* InsertBefore */ nullptr,
    //       /* ThreadLocalMode */ GV->getThreadLocalMode(),
    //       /* AddressSpace */ GV->getAddressSpace()
    //       );

    //       // errs() << GV->getInitializer() << "\n";
    //       // newGlobalVar->setInitializer(test);

    //       newGlobalVar->setAlignment(Align(64));
    //       GV->replaceAllUsesWith(newGlobalVar);
    //       struct_map[oldStructType] = newStructType;
    //       // GV.eraseFromParent();
    //   }
    //   }
    // }

    for (auto &F : M) {
      errs() << "Function " << F.getName() << "\n";
      replaceUsesInFunction(&F, oldStructType, newStructType);
      // for (auto &BB : F) {
        
          // for (auto &I : BB) {
          //     if (auto *AI = dyn_cast<AllocaInst>(&I)) {
          //       // errs() << "Found alloca: " << AI->getName() << "\n";
          //       if (AI->getAllocatedType() == oldStructType) {
          //         // errs() << "SWAPPING ALLOCA TYPE" << "\n";
          //         AI->setAllocatedType(newStructType);
          //       }
          //     }
          //     // errs() << "instruction start " << "\n";
          //     errs() << "Instruction " << I.getOpcodeName() << "\n";
          //     for(auto &Op : I.operands()){
                  
          //         Op->print(errs());
          //         errs() << "\n";
          //         // errs() << "\nFound operand: " << Op->getName() << "\n";
          //         if(Op->getType() == oldStructType){
          //             // errs() << "Found operand: " << Op->getName() << "\n";
          //             Op->mutateType(newStructType);
          //         }
          //         // else if (struct_map.find(Op->getType()) != struct_map.end()) {
          //         //     Op->mutateType(struct_map[Op->getType()]);
          //         // }
          //     }

          //     // if (auto *GEP = dyn_cast<GetElementPtrInst>(&I)) {
          //     //   if (GEP->getSourceElementType() == oldStructType) {
          //     //     GEP->setSourceElementType(newStructType);
          //     //   }
          //     // }

          //     errs() << "======\n";
          // }
      // }
  }

}


void padStruct(StructType* OldStructType, Module& M) {
  std::vector<Type *> FieldTypes;

  for (Type* t : OldStructType->elements()) {
    errs() <<OldStructType->getName() << "\n";
    for (unsigned i = 0; i < OldStructType->getNumElements(); ++i) {
      FieldTypes.push_back(OldStructType->getElementType(i));
      Type *elementType = Type::getInt8Ty(M.getContext());
      uint64_t arraySize = 64 - OldStructType->getElementType(i)->getPrimitiveSizeInBits()/8;

      ArrayType *arrayType = ArrayType::get(elementType, arraySize);
      FieldTypes.push_back(arrayType);
    }
  }

  StructType *newStructType = StructType::create(M.getContext(),FieldTypes, OldStructType->getName().str() + "turd");
  
  GlobalVariable* globalVar = new GlobalVariable(M, newStructType, false, GlobalValue::ExternalLinkage, nullptr, "myGlobalVar");
  //std::set<StructType* st, vector<Type*>>
  replace_types(M, OldStructType, newStructType,{});
}

namespace {
  struct FsharingPass : public PassInfoMixin<FsharingPass> {
      PreservedAnalyses run(Module &M, ModuleAnalysisManager &) {
        auto structlist = M.getIdentifiedStructTypes();
        for (StructType* st : structlist) {
        // Do something with the struct type
          //Type->dump(); // For example, dump the type
          errs() <<st->getName() << "\n";
          padStruct(st, M);
        }
          // std::set<StructType*> struct_types;
          // // StructType *NewStructType = StructType::create({}, "turd");

          // size_t cache_line = cache_line_size();
          // std::vector<GlobalVariable*> gvs;
          // for (GlobalVariable &GV : M.globals()) {
          //   gvs.push_back(&GV);
          // }
          
          // for (GlobalVariable * GV : gvs) {
              
          //     if (GV->hasInitializer()) {
          //       errs() << "fond a struct " <<GV->getName() <<"\n";
          //       Constant *Init = GV->getInitializer();
          //       GV->setAlignment(Align(cache_line));
          //       errs() << Init->getType()->isStructTy() << "\n";
          //       if (Init->getType()->isStructTy()) {
          //         StructType *ST = dyn_cast<StructType>(Init->getType());
          //         struct_types.insert(ST);

        //             GlobalVariable *newGlobalVar = new GlobalVariable(
        // /* Module */ *module,
        // /* Type */ newType,
        // /* isConstant */ oldGlobalVar->isConstant(),
        // /* Linkage */ oldGlobalVar->getLinkage(),
        // /* Initializer */ nullptr,
        // /* Name */ oldGlobalVar->getName(),
        // /* InsertBefore */ nullptr,
        // /* ThreadLocalMode */ oldGlobalVar->getThreadLocalMode(),
        // /* AddressSpace */ oldGlobalVar->getAddressSpace());

        //             // Replace all uses of the old global variable with the new one
        //             oldGlobalVar->replaceAllUsesWith(newGlobalVar);

        //             // Optionally, delete the old global variable
        //             oldGlobalVar->eraseFromParent();
                    
        //             StructType *ST = dyn_cast<StructType>(Init->getType());
        //             struct_types.insert(ST);
          //       }
                
          //   }
          //   errs() << "Found global variable: " << GV->getName() << "\n";
          // }
          
          // for (StructType* oldStructType  : struct_types) {
          //       errs() << "Found struct type: " << oldStructType->getName() << "\n";
          //       std::vector<Type *> FieldTypes;
          //       for (Type* t : oldStructType->elements()) {
          //         Type *elementType = Type::getInt8Ty(M.getContext());
          //         ArrayType *arrayType = ArrayType::get(elementType, 64 - t->getPrimitiveSizeInBits()/8);
          //         FieldTypes.push_back(t);
          //         FieldTypes.push_back(arrayType);
          //       }

          //       StructType *newStructType = StructType::create(FieldTypes, oldStructType->getName().str() + "turd");
                
          //       replace_types(M, oldStructType, newStructType, gvs);

          // }
          
          // for (StructType* OldStructType  : struct_types) {
          //   std::vector<Type *> FieldTypes;
          //   for (unsigned i = 0; i < OldStructType->getNumElements(); ++i) {
          //       FieldTypes.push_back(OldStructType->getElementType(i));

          //       Type *elementType = Type::getInt8Ty(context);
          //       uint64_t arraySize = 64 - OldStructType.getTypeAllocSize();
          //       ArrayType *arrayType = ArrayType::get(elementType, arraySize);
          //       FieldTypes.push_back(NewFieldType);
          //   }
            

          //   StructType *NewStructType = StructType::create(FieldTypes, OldStructType->getName() + ".new");
          //   OldStructType->replaceAllUsesWith(NewStructType);

          //   OldStructType->eraseFromParent();
          // }

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
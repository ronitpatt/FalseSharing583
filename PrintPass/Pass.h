#include "llvm/IR/InstVisitor.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Instruction.h"
#include  <iostream>
#include  <set>
#include <map>

namespace llvm {
    class ReplaceTypeVisitor : public InstVisitor<ReplaceTypeVisitor> {    
    public:
        ReplaceTypeVisitor() {}
        
        void visitAllocaInst(AllocaInst &AI) {
            Module* M = AI.getModule();
            LLVMContext& ctx = M->getContext();
            Module *Mod = AI.getModule();
            LLVMContext &Context = Mod->getContext();
            Function* func = nullptr;
            for (auto &f: Mod->getFunctionList()) {
                if (f.getName().find("doPrint") != std::string::npos) {
                    func = &f;
                }
            }
            IRBuilder<> builder(ctx);

            if (StructType* ST = dyn_cast<StructType>(AI.getAllocatedType() )) {
                errs() << *ST << "\n";
                std::string structName = ST->getName().str();
                for (int i = 0; i < ST->getNumElements(); ++i) {
                    std::vector<Value*> gepIndices = { builder.getInt32(0), builder.getInt32(i) };
                    llvm::GetElementPtrInst* gepInst = llvm::GetElementPtrInst::CreateInBounds(ST, &AI, gepIndices, "hi");
                    gepInst->insertAfter(&AI);
                    Value* v = builder.CreateGlobalString(AI.getName().str() + " "+ structName + "." + std::to_string(i), "", 0, Mod);
                    std::vector<Value*> Args = {v, gepInst};
                    errs() << *gepInst << "\n"; 
                    CallInst* printCall = CallInst::Create(func, Args);
                    printCall->insertAfter(gepInst);
                }
            } else {
                std::string typeString;
                raw_string_ostream typeStream(typeString);
                AI.getAllocatedType()->print(typeStream);
                typeStream.flush();

                std::string name = typeString + " " + AI.getName().str();
                Value* v = builder.CreateGlobalString(name, "", 0, Mod);
                std::vector<Value*> Args = {v, &AI};
                CallInst* printCall = CallInst::Create(func, Args);
                printCall->insertAfter(&AI);
            }

        }

    };
}
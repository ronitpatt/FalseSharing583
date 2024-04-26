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
        ReplaceTypeVisitor() {

        }
        
        void visitAllocaInst(AllocaInst &AI) {
            Module* M = AI.getModule();
            LLVMContext& ctx = M->getContext();
            // FunctionType* printfType = FunctionType::get(IntegerType::getInt32Ty(ctx), 
            // PointerType::get(Type::getInt8Ty(ctx), 0), true);
            // Function* func_printf = cast<Function>(M->getOrInsertFunction("printf", printfType));

            // IRBuilder<> builder(&AI);
            // Value* charPointerToString = builder.CreateGlobalStringPtr("Allocated address: %p\n");
            // Type* longType = IntegerType::getInt64Ty(ctx);
            // Value* intValue = builder.CreatePtrToInt(&AI, longType);
            // Value* pointerValue = builder.CreateIntToPtr(intValue, Type::getInt8PtrTy(ctx));
            // Value* args[] = {charPointerToString, pointerValue};
            // CallInst* printfCall = builder.CreateCall(func_printf, args);

            // // Move printfCall just after the alloca instruction
            // printfCall->moveAfter(&AI);

            // if current function is doprint, then don't do shit


            // Access essential objects
            // errs() << "TOP OF FUNC\n";
            Module *Mod = AI.getModule();
            LLVMContext &Context = Mod->getContext();
            // errs() << "HERE\n";
            // IRBuilder<> Builder(&AI);
            // errs() << "HERE 2\n";
        
            Function* func = nullptr;
            for (auto &f: Mod->getFunctionList()) {
                errs() << "Function: " << &f << "\n";
                if (f.getName().find("doPrint") != std::string::npos) {
                    errs() << "found!" << '\n';
                    func = &f;
                }
            }

            IRBuilder<> builder(ctx);
            Value* v = builder.CreateGlobalString(AI.getName(), "", 0, Mod);
            
            // LoadInst* loadInst = builder.CreateLoad(
            //     Type::getInt8Ty(ctx),
            //     v
            // );
            // loadInst->setAlignment(Align(1));
            
            std::vector<Value*> Args = {v, &AI};
            CallInst* printCall = CallInst::Create(func, Args);
            printCall->insertAfter(&AI);
            // errs() << AI.getName()<<"\n";
        }

    };
}
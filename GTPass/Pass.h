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


namespace llvm {
    class ReplaceTypeVisitor : public InstVisitor<ReplaceTypeVisitor> {
        private:
            StructType* oldType;
            StructType* newType;
            Value* globalVar;

        public:
            ReplaceTypeVisitor(StructType* Old, StructType* New, GlobalVariable* gv) : oldType(Old), newType(New), globalVar(gv) {}

            void visitInstruction(Instruction &I) {}
            
            void visitLoadInst(LoadInst &L) {
                errs() << "LOAD " << L << "\n";
                Value* v = dyn_cast<LoadInst>(&L)->getPointerOperand();
                std::vector<Value*> gepIndices;
                bool foundGEP = false;
                for (auto &Op : L.operands()) {
                    if (auto* expr = dyn_cast<ConstantExpr>(Op)){
                        if (expr->getOpcode() == Instruction::GetElementPtr) {
                            errs() << "hi\n";
                            GetElementPtrInst* GEP = dyn_cast<GetElementPtrInst>(expr->getAsInstruction());
                            GEP->insertBefore(&L);
                            errs() << "GEP OPS\n";
                            int count = 0;
                            for (auto &GOp : GEP->operands()) {
                                errs() << *GOp << "\n";
                                if (count) {
                                    gepIndices.push_back(GOp);
                                }
                                count++;
                            }
                            foundGEP = true;
                        }
                    } else {
                        errs ()<<"h\n";
                    }
                
                }
                if (!foundGEP) {
                    return;
                }

                int numIndices = gepIndices.size();
                std::swap(gepIndices[numIndices - 1], gepIndices[numIndices - 2]);

                IRBuilder<> builder(L.getContext());
                // PointerType *pointerType = dyn_cast<PointerType>(globalVar->getType());
                // errs() << *pointerType << "\n";
                ArrayType* gVtype = ArrayType::get(newType, 3);
                llvm::GetElementPtrInst* gepInst = llvm::GetElementPtrInst::CreateInBounds(
                    gVtype, globalVar, gepIndices, "hi");
                errs() << *gepInst << "\n";
                Type *loadType = L.getType();
                errs() << *loadType  << " " <<*L.getPointerOperand()<< "\n";
                LoadInst* newL = (LoadInst*)L.clone();
                
                newL->insertBefore(&L);
                gepInst->insertBefore(newL);
                newL->setOperand(0,gepInst);
                
                errs() << *newL->getOperand(0)<< " OP \n";
                errs() << *L.getOperand(0) << "\n";
            }


            GetElementPtrInst* handleGEP(GetElementPtrInst &GEP){
                std::vector<Value*> gepIndices;
                int count = 0;
                for (auto &GOp : GEP.operands()) {
                    errs() << *GOp << "\n";
                    if (count) {
                        gepIndices.push_back(GOp);
                    }
                    count++;
                }

                int numIndices = gepIndices.size();
                std::swap(gepIndices[numIndices - 1], gepIndices[numIndices - 2]);

                ArrayType* gVtype = ArrayType::get(newType, 4);
                llvm::GetElementPtrInst* gepInst = llvm::GetElementPtrInst::CreateInBounds(
                    gVtype, globalVar, gepIndices, "hi");
                return gepInst;
            }

            void visitStoreInst(StoreInst &L){
                errs() << "STORE " << L << "\n";
                Value* v = dyn_cast<StoreInst>(&L)->getPointerOperand();
                std::vector<Value*> gepIndices;
                bool foundGEP = false;
                for (auto &Op : L.operands()) {
                    if (auto* expr = dyn_cast<ConstantExpr>(Op)){
                        if (expr->getOpcode() == Instruction::GetElementPtr) {
                            errs() << "hi\n";
                            GetElementPtrInst* GEP = dyn_cast<GetElementPtrInst>(expr->getAsInstruction());
                            GEP->insertBefore(&L);
                            errs() << "GEP OPS\n";
                            int count = 0;
                            for (auto &GOp : GEP->operands()) {
                                errs() << *GOp << "\n";
                                if (count) {
                                    gepIndices.push_back(GOp);
                                }
                                count++;
                            }
                            foundGEP = true;
                            GEP->eraseFromParent();
                        }
                    } else {
                        errs ()<<"h\n";
                    }
                
                }

                errs() << "STORE FOUND GEP " << foundGEP << "\n";
                errs() << L << "\n";
                if (!foundGEP) {
                    return;
                }
                errs() << "hi\n"; 
                int numIndices = gepIndices.size();
                errs() << gepIndices[numIndices - 1] << "\n";
                errs() << gepIndices[numIndices - 2] << "\n";
                // std::swap(gepIndices[numIndices - 1], gepIndices[numIndices - 2]);

                IRBuilder<> builder(L.getContext());
                // PointerType *pointerType = dyn_cast<PointerType>(globalVar->getType());
                // errs() << *pointerType << "\n";
                // ArrayType* gVtype = ArrayType::get(newType, 4);
                // llvm::GetElementPtrInst* gepInst = llvm::GetElementPtrInst::CreateInBounds(
                //     gVtype, globalVar, gepIndices, "hi");
                // errs() << *gepInst << "\n";
                // Type *loadType = L.getType();
                // errs() << *loadType  << " " <<*L.getPointerOperand()<< "\n";
                // StoreInst* newL = (StoreInst*)L.clone();
                
                // newL->insertBefore(&L);
                // gepInst->insertBefore(newL);
                // newL->setOperand(1, gepInst);
                
                // errs() << *newL->getOperand(0)<< " OP \n";
                // errs() << *L.getOperand(0) << "\n";
                // L.eraseFromParent();
                //newL->eraseFromParent();
            }

            void visitGetElementPtrInst(GetElementPtrInst &GEP) {
                errs() << "Visit GEP\n";
                GetElementPtrInst* new_instruction = handleGEP(GEP);
                new_instruction->insertBefore(&GEP);
                GEP.replaceAllUsesWith(new_instruction);
                GEP.eraseFromParent();
            }
    };
};
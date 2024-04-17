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
            Value* oldGlobal;
            

        public:
            ReplaceTypeVisitor(StructType* Old, StructType* New, GlobalVariable* gv, GlobalVariable* old) : oldType(Old), newType(New), globalVar(gv), oldGlobal(old) {}

            void visitInstruction(Instruction &I) {}
            
            void visitLoadInst(LoadInst &L) {
                errs() << "LOAD " << L << "\n";
                Value* v = dyn_cast<LoadInst>(&L)->getPointerOperand();
                std::vector<Value*> gepIndices;
                bool foundGEP = false;
                for (auto &Op : L.operands()) {
                    if (auto* expr = dyn_cast<ConstantExpr>(Op)) {
                        if (expr->getOpcode() == Instruction::GetElementPtr) {
                            GetElementPtrInst* GEP = dyn_cast<GetElementPtrInst>(expr->getAsInstruction());
                            if (oldType != GEP->getSourceElementType()) {
                                return;
                            }
                            GEP->insertBefore(&L);
                            int count = 0;
                            for (auto &GOp : GEP->operands()) {
                                if (count) {
                                    gepIndices.push_back(GOp);
                                }
                                count++;
                            }
                            foundGEP = true;
                            GEP->eraseFromParent();
                        }
                    } else {
                    }
                
                }
                if (!foundGEP ) {
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
                Type *loadType = L.getType();
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
                Value* v = dyn_cast<StoreInst>(&L)->getOperand(0);
                if (v == oldGlobal) {
                    L.setOperand(0, globalVar);
                    return;
                }
                std::vector<Value*> gepIndices;
                bool foundGEP = false;
                for (auto &Op : L.operands()) {
                    if (auto* expr = dyn_cast<ConstantExpr>(Op)){
                        if (expr->getOpcode() == Instruction::GetElementPtr) {
                            GetElementPtrInst* GEP = dyn_cast<GetElementPtrInst>(expr->getAsInstruction());
                            GEP->insertBefore(&L);
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
                    }
                
                }

                if (!foundGEP) {
                    return;
                }
                int numIndices = gepIndices.size();
                if (numIndices == 3) {
                    std::swap(gepIndices[numIndices - 1], gepIndices[numIndices - 2]);
                }
                
                //errs() << gepIndices[numIndices - 1] << "1st \n";
                //errs() << gepIndices[numIndices - 2] << "2nd \n";
                

                IRBuilder<> builder(L.getContext());
                PointerType *pointerType = dyn_cast<PointerType>(globalVar->getType());
                ArrayType* gVtype = ArrayType::get(newType, 4);
                Type* GEPSourceType = gVtype;
                if ( numIndices == 2 && gepIndices[0]->getType()->getIntegerBitWidth() == 32 && gepIndices[1]->getType()->getIntegerBitWidth() == 32) {
                    GEPSourceType = newType;
                }
                llvm::GetElementPtrInst* gepInst = llvm::GetElementPtrInst::CreateInBounds(
                    GEPSourceType, globalVar, gepIndices, "hi");
                
                Type *loadType = L.getType();
                StoreInst* newL = (StoreInst*)L.clone();
                
                newL->insertBefore(&L);
                gepInst->insertBefore(newL);
                newL->setOperand(1, gepInst);
                errs() << L << " removed\n";
                errs() << *gepInst << "\n";
                errs() << *newL<< " new \n";
                
                
                L.eraseFromParent();
                //newL->eraseFromParent();
            }

            void visitGetElementPtrInst(GetElementPtrInst &GEP) {
                if (oldType != GEP.getSourceElementType()) {
                    return;
                }
                errs() << "Visit GEP\n";
                GetElementPtrInst* new_instruction = handleGEP(GEP);
                new_instruction->insertBefore(&GEP);
                GEP.replaceAllUsesWith(new_instruction);
                GEP.eraseFromParent();
            }
    };
};
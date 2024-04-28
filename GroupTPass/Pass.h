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
        ArrayType* arrType;

    public:
        ReplaceTypeVisitor(StructType* Old, StructType* New, GlobalVariable* gv, GlobalVariable* old) : oldType(Old), newType(New), globalVar(gv), oldGlobal(old) {
            arrType = ArrayType::get(newType, 4);
        }

        void visitInstruction(Instruction &I) {}
            
        GetElementPtrInst* handleGEP(GetElementPtrInst &GEP, Type* newType, Instruction& original) {
            std::vector<Value*> gepIndices;
            int count = 0;
            for (auto &GOp : GEP.operands()) {
                if (count) {
                    gepIndices.push_back(GOp);
                }
                count++;
            }
            int numIndices = gepIndices.size();
            if (numIndices == 3) {
                std::swap(gepIndices[numIndices - 1], gepIndices[numIndices - 2]);
            }
            Type* GEPSourceType = arrType;
            if ( numIndices == 2 && gepIndices[0]->getType()->getIntegerBitWidth() == 32 && gepIndices[1]->getType()->getIntegerBitWidth() == 32) {
                GEPSourceType = newType;
            }

            llvm::GetElementPtrInst* gepInst = llvm::GetElementPtrInst::CreateInBounds(
                GEPSourceType, globalVar, gepIndices, "hi");

            return gepInst;
        }

        void visitLoadInst(LoadInst &L) {
            
            Value* v = dyn_cast<LoadInst>(&L)->getPointerOperand();
            std::vector<Value*> gepIndices;
            bool foundGEP = false;
            GetElementPtrInst* GEP;
            llvm::GetElementPtrInst* gepInst;
            for (auto &Op : L.operands()) {
                if (auto* expr = dyn_cast<ConstantExpr>(Op)) {
                    if (expr->getOpcode() == Instruction::GetElementPtr) {
                        GEP = dyn_cast<GetElementPtrInst>(expr->getAsInstruction());
                        GEP->insertBefore(&L);
                        
                        int count = 0;
                        for (auto &GOp : GEP->operands()) {
                            if (count) {
                                gepIndices.push_back(GOp);
                            }
                            count++;
                        }
                        gepInst = handleGEP(*GEP, newType, L);
                        foundGEP = true;
                        GEP->eraseFromParent();
                    }
                } else {}
            }
            if (!foundGEP) {
                return;
            }

            gepInst->insertBefore(&L);
            LoadInst* newL = (LoadInst*)L.clone();
            
            newL->insertBefore(&L);
            
            newL->setOperand(0,gepInst);
            
            L.replaceAllUsesWith(newL);
            L.eraseFromParent();
        }

        void visitStoreInst(StoreInst &L){
            Value* v = dyn_cast<StoreInst>(&L)->getOperand(0);
            if (v == oldGlobal) {
                L.setOperand(0, globalVar);
                return;
            }
            std::vector<Value*> gepIndices;
            bool foundGEP = false;
            GetElementPtrInst* newGEP;
            GetElementPtrInst* GEP;
            for (auto &Op : L.operands()) {
                if (auto* expr = dyn_cast<ConstantExpr>(Op)){
                    if (expr->getOpcode() == Instruction::GetElementPtr) {
                        // check if its actually using the global
                        GEP = dyn_cast<GetElementPtrInst>(expr->getAsInstruction());
                        GEP->insertBefore(&L);
                        foundGEP = true;
                        newGEP = handleGEP(*GEP, newType, L);
                        GEP->eraseFromParent();
                    }
                } else {
                }
            }
            if (!foundGEP) { return; }
                            
            StoreInst* newL = (StoreInst*) L.clone();
            
            newL->insertBefore(&L);
            newGEP->insertBefore(newL);
            newL->setOperand(1, newGEP);
            L.replaceAllUsesWith(newL);
            
            L.eraseFromParent();
        }

        void visitGetElementPtrInst(GetElementPtrInst &GEP) {
            if (auto* expr = dyn_cast<ConstantExpr>(GEP.getOperand(0))) {
                if (expr->getOpcode() == Instruction::GetElementPtr) {
                    GetElementPtrInst* nestedGEP = dyn_cast<GetElementPtrInst>(expr->getAsInstruction());
                    nestedGEP->insertBefore(&GEP);
                    GetElementPtrInst* newGEP = handleGEP(*nestedGEP, newType, GEP);
                    nestedGEP->eraseFromParent();
                    
                    GetElementPtrInst* newG = (GetElementPtrInst*) GEP.clone();
                    newG->insertBefore(&GEP);
                    newGEP->insertBefore(newG);
                    newG->setOperand(0, newGEP);
                    GEP.replaceAllUsesWith(newG);
                    GEP.eraseFromParent();
                }
            } else if (oldType == GEP.getSourceElementType()){
                GetElementPtrInst* newInstruction = handleGEP(GEP, newType, GEP);
                newInstruction->insertBefore(&GEP);
                GEP.replaceAllUsesWith(newInstruction);
                GEP.eraseFromParent();
            }
        }
};
};
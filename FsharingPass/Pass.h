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

public:
    ReplaceTypeVisitor(StructType* Old, StructType* New) : oldType(Old), newType(New) {}

    void visitInstruction(Instruction &I) {
        // errs() << I << "\n";
    }
    Type* recur(Type *t) {
        if (t->isArrayTy()) {
            //errs() << "Array\n";
            ArrayType *AT = dyn_cast<ArrayType>(t);
            Type *ET = AT->getElementType();
            //errs() << *ET << "\n";
            Type* ret = recur(ET);
            ArrayType *ArrType = ArrayType::get(newType, AT->getNumElements());
            return ArrType;
        } else {
            if (t == oldType) {
                return newType;
            }
            return t;
        }
        
    }
    
    void visitAllocaInst(AllocaInst &AI) {
        // errs() << AI << "\n";
        errs() << "---------\n";
        errs() << "Before" << "\n";
        errs() << AI << "\n";
        if (AI.getAllocatedType()->isArrayTy()) {
            Type* rettype = recur(AI.getAllocatedType());
            // errs() << "--- array type alloca\n";
            // errs() << AI << "\n";
            // errs() << *AI.getAllocatedType() << " type"<< "\n";
            // errs() << *rettype << " rettype"<< "\n";
            AI.setAllocatedType(rettype);
            //AI.setAlignment(Align(16));???
            
            
            
        }

        if (AI.getAllocatedType() == oldType) {
            AI.setAllocatedType(newType);
        }
        errs() << "After" << "\n";
        errs() << AI << "\n";
    }

    int getOffset(int oldOffset) {
        auto oldelems = oldType->elements();
        Type* oldT = oldelems[oldOffset];
        std::vector<Type*> newelems = newType->elements();
        int paddingAdded = 0;
        int curroffset = 0;
        // old = {int, bool, int}
        // new = {int, padd, bool, padd, int, padd}

        // std::map<Type*, int> old_type_count;
        // std::map<Type*, int> new_type_count;
        // for (int i = 0; i<oldOffset; i++) {
        //     old_type_count[oldelems[i]]++;
        // }

        
        int oldCounter = 0;
        int newcounter = 0;
        for (NULL ; newcounter < newelems.size(); ++newcounter) {
            // if (old_type_count.find(newelems[newcounter]) != old_type_count.end()) {
            //     new_type_count[newelems[newcounter]]++;
            // }
            // bool same = old_type_count[oldelems[oldCounter]] == new_type_count[newelems[newcounter]];

            if (oldelems[oldCounter] != newelems[newcounter]) { // || !same
                paddingAdded++; // padding
            } else {
                oldCounter++;
            }

            if (oldCounter > oldOffset) { // curroffset = 1 means u are looking at new structs 1 index type
                //errs() << newcounter << "RET \n";
                return newcounter;
            }
        }
        
        //errs() << oldOffset + paddingAdded << "RET 1\n";
        return newcounter; //newcounter
        
    }
    
    

    void visitGetElementPtrInst(GetElementPtrInst &GEP) {
        errs() << "---------\n";
        errs() << "Before\n";
        errs() << GEP << "\n";
                
        if (GEP.getSourceElementType()->isArrayTy()) {
            Type* rettype = recur(GEP.getSourceElementType());
            
            std::vector<llvm::Value*> idxList(GEP.idx_begin(), GEP.idx_end());

            llvm::GetElementPtrInst* newGEP = llvm::GetElementPtrInst::CreateInBounds(
                rettype, GEP.getPointerOperand(), idxList,
                GEP.getName(), &GEP);

            // GetElementPtrInst& cloned = *newGEP;
            // cloned.copyMetadata(GEP);
            // cloned.moveBefore(&GEP);

            GEP.replaceAllUsesWith(newGEP);
            GEP.eraseFromParent();

            errs() << "After\n";
            errs() << *newGEP << "\n";
        }
        
        if (oldType == GEP.getSourceElementType()) {
            GEP.setSourceElementType(newType);
            Value *OffsetValue = GEP.getOperand(2);
            int64_t Offset = dyn_cast<ConstantInt>(OffsetValue)->getSExtValue();
            int NewOffsetValue = getOffset(Offset);
            Type *NewOffsetType = IntegerType::get(GEP.getContext(), 32);
            Constant *NewOffsetConstant = ConstantInt::get(NewOffsetType, NewOffsetValue);            
            GEP.setOperand(2, NewOffsetConstant);

            errs() << "After\n";
            errs() << GEP << "\n";
        }
       
        

    }

    
};
};
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
        // for (Use &U : I.operands()) {
        //     if (auto *OpTy = dyn_cast<PointerType>(U->getType())) {
        //         if (OpTy->getElementType() == oldType) {
        //             U.set(PointerType::get(newType, OpTy->getAddressSpace()));
        //         }
        //     }
        // }
    }
    void visitAllocaInst(AllocaInst &AI) {
        if (AI.getAllocatedType() == oldType) {
            AI.setAllocatedType(newType);
        }
    }
    int getOffset(int oldOffset) {
        auto oldelems = oldType->elements();
        Type* oldT = oldelems[oldOffset];
        std::vector<Type*> newelems = newType->elements();
        int paddingAdded = 0;
        int curroffset = -1;
        for (int i = 0; i < oldelems.size(); ++i) {
            if (oldelems[i] != newelems[i]) {
                paddingAdded++;
                errs() << "padding" << "\n";
            } else {
                curroffset++;
            }
            
            if (curroffset == oldOffset) {
                return oldOffset + paddingAdded;
            }
            
        }
        return oldOffset + paddingAdded;
        
    }
    
    void visitGetElementPtrInst(GetElementPtrInst &GEP) {
        if (GEP.getSourceElementType() == oldType) {
            
            GEP.setSourceElementType(newType);
            //errs() << "numIndices " <<  GEP.getNumIndices() << "\n";
            //errs() << "pointerAddressSpace " <<  GEP.getPointerAddressSpace() << "\n";
            //errs() << "addressSpace " <<  GEP.getAddressSpace() << "\n";
             // Example: 32-bit integer type
            Value *OffsetValue = GEP.getOperand(2);
             // Example new offset value
            // Set the new offset value
            int64_t Offset = dyn_cast<ConstantInt>(OffsetValue)->getSExtValue();
            int NewOffsetValue = getOffset(Offset);
            errs() << "Calculated offset " << NewOffsetValue << "\n";
            //NewOffsetValue = 2*Offset;
            Type *NewOffsetType = IntegerType::get(GEP.getContext(), 32);
            Constant *NewOffsetConstant = ConstantInt::get(NewOffsetType, NewOffsetValue);
            GEP.setOperand(2, NewOffsetConstant);
            // Handle updating the types in GEP indices if needed
            // for (Use &U : GEP.indices()) {
            //     if (auto *OpTy = dyn_cast<IntegerType>(U->getType())) {
            //         // Update index types if necessary
            //         // Example: U.set(IntegerType::get(GEP.getContext(), 64));
            //     }
            // }
        }
    }
    
};

}
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
    std::vector<int> newOffsets;
    
public:
    ReplaceTypeVisitor(StructType* Old, StructType* New, std::vector<int> &offsets) : oldType(Old), newType(New), newOffsets(offsets) {}

    void visitInstruction(Instruction &I) {
        // errs() << I << "\n";
    }
        
    void visitAllocaInst(AllocaInst &AI) {
    }    
    
    void visitGetElementPtrInst(GetElementPtrInst &GEP) {
        errs() << "---------\n";
        errs() << "Before\n";
    
        errs() << GEP << "\n";
                
        if (oldType == GEP.getSourceElementType()) {
            GEP.setSourceElementType(newType);

            Value *offset_value = GEP.getOperand(2);
            int64_t offset = dyn_cast<ConstantInt>(offset_value)->getSExtValue();
            errs() << "Offset: " << offset << "\n";
            errs() << "New Offset: " << newOffsets[offset] << "\n";

            Type *new_offset_type = IntegerType::get(GEP.getContext(), 32); // check this
            Constant *new_offset_constant = ConstantInt::get(new_offset_type, newOffsets[offset]); 
        
            GEP.setOperand(2, new_offset_constant);

            errs() << "After\n";
            errs() << GEP << "\n";
        }
    }

    
};
};
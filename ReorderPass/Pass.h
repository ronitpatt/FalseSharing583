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
    ReplaceTypeVisitor(StructType* oldTypeArg, StructType* newTypeArg, std::vector<int> &offsets) : oldType(oldTypeArg), newType(newTypeArg), newOffsets(offsets) {}  
    
    void visitGetElementPtrInst(GetElementPtrInst &GEP) {
                
        if (oldType == GEP.getSourceElementType()) {
            GEP.setSourceElementType(newType);

            Value *offsetValue = GEP.getOperand(2);
            int64_t offset = dyn_cast<ConstantInt>(offsetValue)->getSExtValue();

            Type *newOffsetType = IntegerType::get(GEP.getContext(), 32);
            Constant *newOffsetConstant = ConstantInt::get(newOffsetType, newOffsets[offset]); 
        
            GEP.setOperand(2, newOffsetConstant);
        }
    }

    
};
};
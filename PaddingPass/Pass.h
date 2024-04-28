#include "llvm/IR/InstVisitor.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

namespace llvm {
class ReplaceTypeVisitor : public InstVisitor<ReplaceTypeVisitor> {
private:
  StructType *oldType;
  StructType *newType;

public:
  ReplaceTypeVisitor(StructType *oldTypeArg, StructType *newTypeArg)
      : oldType(oldTypeArg), newType(newTypeArg) {}

  Type *recur(Type *t) {
    if (t->isArrayTy()) {
      ArrayType *AT = dyn_cast<ArrayType>(t);
      Type *ET = AT->getElementType();
      Type *ret = recur(ET);
      ArrayType *arrType = ArrayType::get(newType, AT->getNumElements());
      return arrType;
    } else {
      if (t == oldType) {
        return newType;
      }
      return t;
    }
  }

  void visitAllocaInst(AllocaInst &AI) {
    if (AI.getAllocatedType()->isArrayTy()) {
      Type *rettype = recur(AI.getAllocatedType());
      AI.setAllocatedType(rettype);
    }

    if (AI.getAllocatedType() == oldType) {
      AI.setAllocatedType(newType);
    }
  }

  int getOffset(int oldOffset) {
    auto oldElements = oldType->elements();
    Type *oldT = oldElements[oldOffset];
    std::vector<Type *> newElements = newType->elements();
    int paddingAdded = 0;
    int curroffset = 0;

    int oldCounter = 0;
    int newCounter = 0;
    for (NULL; newCounter < newElements.size(); ++newCounter) {
      if (oldElements[oldCounter] != newElements[newCounter]) {
        paddingAdded++;
      } else {
        oldCounter++;
      }

      if (oldCounter > oldOffset) {
        return newCounter;
      }
    }
    return newCounter;
  }

  void visitGetElementPtrInst(GetElementPtrInst &GEP) {

    if (GEP.getSourceElementType()->isArrayTy()) {
      Type *ret_type = recur(GEP.getSourceElementType());
      std::vector<llvm::Value *> idxList(GEP.idx_begin(), GEP.idx_end());

      llvm::GetElementPtrInst *newGEP = llvm::GetElementPtrInst::CreateInBounds(
          ret_type, GEP.getPointerOperand(), idxList, GEP.getName(), &GEP);
      GEP.replaceAllUsesWith(newGEP);
      GEP.eraseFromParent();
    }

    if (oldType == GEP.getSourceElementType()) {
      GEP.setSourceElementType(newType);
      Value *offsetValue = GEP.getOperand(2);
      int64_t offset = dyn_cast<ConstantInt>(offsetValue)->getSExtValue();
      int newOffsetValue = getOffset(offset);
      Type *newOffsetType = IntegerType::get(GEP.getContext(), 32);
      Constant *newOffsetConstant =
          ConstantInt::get(newOffsetType, newOffsetValue);
      GEP.setOperand(2, newOffsetConstant);
    }
  }
};
}; // namespace llvm
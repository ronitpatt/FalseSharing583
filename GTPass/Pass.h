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

    void visitInstruction(Instruction &I) {
        // errs() << I << "\n";
        // errs() << I << "\n";
        // if (!dyn_cast<GetElementPtrInst>(&I)) {
        //     return;
        // }

        // GetElementPtrInst& gep = *dyn_cast<GetElementPtrInst>(&I);

        // errs() << gep << "\n";
    }
    
    void visitLoadInst(LoadInst &L) {
        errs() << "LOAD " << L << "\n";
        // std::vector<llvm::Value*> idxList(L.idx_begin(), L.idx_end());
        // for (auto i: idxList) {
        //     errs() << *i << "  \n";
        // }

        Value* v = dyn_cast<LoadInst>(&L)->getPointerOperand();
        //if (auto* GEP = dyn_cast<GetElementPtrInst>(v)) {
        //    // Handle GetElementPtrInst
        //} else

        // right now the LoadInst is is obj.a[3] and i want to make it obj[3].a
        // %3 = load i32, ptr getelementptr inbounds ([4 x i32], ptr @obj, i64 0, i64 3), align 4

        // code below:
        // Assuming you have an existing pointer value named "arrPtr"
        //Value *arrPtr = ...; // get the existing pointer value somehow

        IRBuilder<> builder(L.getContext());
        std::vector<Value*> gepIndices;
        gepIndices.push_back(builder.getInt64(0));
        gepIndices.push_back(builder.getInt64(2));
        gepIndices.push_back(builder.getInt32(1));
        //GetElementPtrInst *gepInst = builder.CreateGEP(newType, globalVar, gepIndices, "gep");
        //GetElementPtrInst *gepInst = builder.CreateGEP(globalVar->getType(), globalVar, gepIndices, "gep"); 
        PointerType *pointerType = dyn_cast<PointerType>(globalVar->getType());
        errs() << *pointerType << "\n";
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
        errs() << *newL->getOperand(0)<< "OP \n";
        //errs() << * builder.CreateLoad(L.getType(),(Value*)L.getPointerOperand(),"hi") << "\n";
        //errs() << *newLoadInst << "HELLO \n";
        //newLoadInst->insertBefore(&L);
        
        
        
        // LoadInst* newLoad = LoadInst::Create(
        //     newType, v, L.getName() + "modified", &L, GetElementPtr::CreateInBounds(
        //         newType, v, {ConstantInt::get(Type::getInt64Ty(L.getContext()), 0), ConstantInt::get(Type::getInt64Ty(L.getContext()), 3)}, L.getName() + "modified"
        //     )
        // );
        // L.replaceAllUsesWith(newLoad);
        // if (auto* expr = dyn_cast<ConstantExpr>(v)) {
        //     if (expr->getOpcode() == Instruction::GetElementPtr) {
        //         GetElementPtrInst* GEP = dyn_cast<GetElementPtrInst>(expr->getAsInstruction());
                
        //         // std::vector<llvm::Value*> idxList(GEP->idx_begin(), GEP->idx_end());
        //         // for (auto i: idxList) {
        //         //     errs() << *i << "  \n";
        //         // }
        //     }  
        // }
        // %3 = load i32, ptr getelementptr inbounds ([4 x i32], ptr @obj, i64 0, i64 3), align 4
        // i want the getelementptr instruction
        // i tried this and it doesn't work
        // GetElementPtrInst* GEP = dyn_cast<GetElementPtrInst>(L.getPointerOperand());
        // if (!GEP) {
        //     return;
        // }



        
        // errs() << "GEP " << *GEP << "\n";

        //errs() << dyn_cast<Pointer>(*L.getPointerOperand()) << "\n";
        // if (!dyn_cast<GetElementPtrInst>(L.getPointerOperand())) {
        //     errs() << "RETURNING\n";
        //     return;
        // }

        // GetElementPtrInst& GEP = *dyn_cast<GetElementPtrInst>(L.getPointerOperand());

        // errs() << GEP << "\n";
        
        // errs() << "\n";

    }


    // Type* recur(Type *t) {
        // if (t->isArrayTy()) {
        //     //errs() << "Array\n";
        //     ArrayType *AT = dyn_cast<ArrayType>(t);
        //     Type *ET = AT->getElementType();
        //     //errs() << *ET << "\n";
        //     Type* ret = recur(ET);
        //     ArrayType *ArrType = ArrayType::get(newType, AT->getNumElements());
        //     return ArrType;
        // } else {
        //     if (t == oldType) {
        //         return newType;
        //     }
        //     return t;
        // }
        
    // }
    
    // void visitAllocaInst(AllocaInst &AI) {
    //     errs() << AI << "\n";
    //     // errs() << "---------\n";
    //     // errs() << "Before" << "\n";
    //     // errs() << AI << "\n";
    //     // if (AI.getAllocatedType()->isArrayTy()) {
    //     //     Type* rettype = recur(AI.getAllocatedType());
    //     //     // errs() << "--- array type alloca\n";
    //     //     // errs() << AI << "\n";
    //     //     // errs() << *AI.getAllocatedType() << " type"<< "\n";
    //     //     // errs() << *rettype << " rettype"<< "\n";
    //     //     AI.setAllocatedType(rettype);
    //     //     //AI.setAlignment(Align(16));???
            
            
            
    //     // }

    //     // if (AI.getAllocatedType() == oldType) {
    //     //     AI.setAllocatedType(newType);
    //     // }
    //     // errs() << "After" << "\n";
    //     // errs() << AI << "\n";
    // }

    // int getOffset(int oldOffset) {
    //     auto oldelems = oldType->elements();
    //     Type* oldT = oldelems[oldOffset];
    //     std::vector<Type*> newelems = newType->elements();
    //     int paddingAdded = 0;
    //     int curroffset = 0;
    //     // old = {int, bool, int}
    //     // new = {int, padd, bool, padd, int, padd}

    //     // std::map<Type*, int> old_type_count;
    //     // std::map<Type*, int> new_type_count;
    //     // for (int i = 0; i<oldOffset; i++) {
    //     //     old_type_count[oldelems[i]]++;
    //     // }

        
    //     int oldCounter = 0;
    //     int newcounter = 0;
    //     for (NULL ; newcounter < newelems.size(); ++newcounter) {
    //         // if (old_type_count.find(newelems[newcounter]) != old_type_count.end()) {
    //         //     new_type_count[newelems[newcounter]]++;
    //         // }
    //         // bool same = old_type_count[oldelems[oldCounter]] == new_type_count[newelems[newcounter]];

    //         if (oldelems[oldCounter] != newelems[newcounter]) { // || !same
    //             paddingAdded++; // padding
    //         } else {
    //             oldCounter++;
    //         }

    //         if (oldCounter > oldOffset) { // curroffset = 1 means u are looking at new structs 1 index type
    //             //errs() << newcounter << "RET \n";
    //             return newcounter;
    //         }
    //     }
        
    //     //errs() << oldOffset + paddingAdded << "RET 1\n";
    //     return newcounter; //newcounter
        
    // }
    
    

    // void visitGetElementPtrInst(GetElementPtrInst &GEP) {
    //     errs() << "---------\n";
    //     errs() << "Before\n";
    //     errs() << GEP << "\n";
    //     // if (GEP.getSourceElementType() == oldType) {
    //     //     std::vector<llvm::Value*> idxList(GEP.idx_begin(), GEP.idx_end());
    //     //     llvm::GetElementPtrInst* newGEP = llvm::GetElementPtrInst::CreateInBounds(
    //     //         newType, GEP.getPointerOperand(), idxList,
    //     //         GEP.getName(), &GEP);

            
    //     // }
    //     // errs() << "---------\n";
    //     // errs() << "Before\n";
    //     // errs() << GEP << "\n";
                
    //     // if (GEP.getSourceElementType()->isArrayTy()) {
    //     //     Type* rettype = recur(GEP.getSourceElementType());
            
    //         // std::vector<llvm::Value*> idxList(GEP.idx_begin(), GEP.idx_end());

    //         // llvm::GetElementPtrInst* newGEP = llvm::GetElementPtrInst::CreateInBounds(
    //         //     rettype, GEP.getPointerOperand(), idxList,
    //         //     GEP.getName(), &GEP);

    //     //     // GetElementPtrInst& cloned = *newGEP;
    //     //     // cloned.copyMetadata(GEP);
    //     //     // cloned.moveBefore(&GEP);

    //     //     GEP.replaceAllUsesWith(newGEP);
    //     //     GEP.eraseFromParent();

    //     //     errs() << "After\n";
    //     //     errs() << *newGEP << "\n";
    //     // }
        
    //     // if (oldType == GEP.getSourceElementType()) {
    //     //     GEP.setSourceElementType(newType);
    //     //     Value *OffsetValue = GEP.getOperand(2);
    //     //     int64_t Offset = dyn_cast<ConstantInt>(OffsetValue)->getSExtValue();
    //     //     int NewOffsetValue = getOffset(Offset);
    //     //     Type *NewOffsetType = IntegerType::get(GEP.getContext(), 32);
    //     //     Constant *NewOffsetConstant = ConstantInt::get(NewOffsetType, NewOffsetValue);            
    //     //     GEP.setOperand(2, NewOffsetConstant);

    //     //     errs() << "After\n";
    //     //     errs() << GEP << "\n";
    //     // }
       
        

    // }

    
};
};
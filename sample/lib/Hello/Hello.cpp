//===- Hello.cpp - Example code from "Writing an LLVM Pass" ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements two versions of the LLVM "Hello World" pass described
// in docs/WritingAnLLVMPass.html
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "hello"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/InstIterator.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "vector"

using namespace llvm;



namespace {
struct Hello :  public FunctionPass
{
        /** Constructor. */
	static char ID;
	Hello() : FunctionPass(ID) {}

        //DEFINE_INTPASS_ANALYSIS_ADJUSTMENT(PointerAnalysisPass);
				/*
         * @brief Runs this pass on the given function.
         * @param [in,out] func The function to analyze
         * @return true if the function was modified; false otherwise
        */
        virtual bool runOnFunction(llvm::Function &F){
					errs() <<"In function ";
					errs().write_escaped(F.getName())<<  "\n";
					Function *callerFunc = &F;
					Function *calleeFunc;
					CallInst* callInst;
					bool areArgsConst;
					ConstantInt * constArg;
					Value* V;
					unsigned numArgs;
					std::vector<Value*> actualArgVector;

					//CallBase value;

					for (inst_iterator I = inst_begin(callerFunc), E=inst_end(callerFunc); I!=E; ++I)
					{	errs()<<"Is the problem here????????????????\n";
						callInst = dyn_cast<CallInst>(&*I);
						errs()<<"OR1  Is the problem here????????????????\n";
						if (callInst){
							errs()<<"OR3  Is the problem here????????????????\n";
							areArgsConst= true;
							numArgs=callInst->getNumArgOperands();
							for (unsigned ArgIdx=0; ArgIdx<numArgs; ++ArgIdx){
								V=callInst->getArgOperand(ArgIdx);
								if(!isa<Constant>(V)) areArgsConst= false;
								else actualArgVector.push_back(V);
								}
								//constArg=ConstantInt::get(IntegerType::get(V->getContext(),32), (uint64_t)*V);
								if (areArgsConst){
									calleeFunc=callInst->getCalledFunction();
									//if(!calleeFunc) continue;
									unsigned Idx=0;
									for (Function::arg_iterator ArgPtr = calleeFunc->arg_begin(), ArgEnd= calleeFunc->arg_end(); ArgPtr !=ArgEnd; ++ArgPtr){
										constArg = dyn_cast<ConstantInt>(actualArgVector[Idx++]);
										ArgPtr->replaceAllUsesWith(constArg);
										}
									actualArgVector.clear();
									errs()<<"entering function ";
									errs().write_escaped(calleeFunc->getName())<<  "\n";

									int i=0;
									for(Function::iterator calleeB_I= calleeFunc->begin(), calleeB_E=calleeFunc->end(); calleeB_I!=calleeB_E; ++calleeB_I)
										for(BasicBlock::iterator callee_I=calleeB_I->begin, callee_E=calleeB_I->end(); callee_I!=callee_E)
									//for (inst_iterator callee_I = inst_begin(calleeFunc), callee_E=inst_end(calleeFunc); callee_I!=callee_E; ++callee_I)
											{errs()<<i<<": Current Instruction:"<< *callee_I <<", End :" << *callee_E <<"\n";
												&*I->getParent()->getInstList().insert(&*I,&*callee_I);
											}
									I->eraseFromParent();
								}
						}
					}
					return false;
				}

};
}

char Hello::ID = 0;
static RegisterPass<Hello> X("hello", "Hello World Pass", false, false);

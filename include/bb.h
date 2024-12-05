#ifndef BASICBLOCK_H
#define BASICBLOCK_H

#include <vector>
#include <set>
#include <memory>
#include "instr.h"

class IRGraph;

class BasicBlock {
public:
    BasicBlock(IRGraph* graph);

    // instr handling
    void addInstruction(Instr* instruction);
    void removeInstruction(Instr* instruction);
    Instr* getFirstInstruction() const;
    Instr* getLastInstruction() const;
    Instr* getFirstPhi() const;

    // bb connections handling
    void addPredecessor(BasicBlock* pred);
    void addSuccessor(BasicBlock* succ);
    const std::set<BasicBlock*>& getPredecessors() const;
    const std::vector<BasicBlock*>& getSuccessors() const;

    // 
    IRGraph* getGraph() const;

private:
    IRGraph* graph;                    // BB's graph
    std::set<BasicBlock*> preds;       // 
    std::vector<BasicBlock*> succs;    // <= 2
    Instr* firstPhi;                   // 
    Instr* firstInst;                  // 
    Instr* lastInst;                   //
};

#endif // BASICBLOCK_H

#include "bb.h"
#include "ir_graph.h"

BasicBlock::BasicBlock(IRGraph* graph)
    : graph(graph), firstPhi(nullptr), firstInst(nullptr), lastInst(nullptr) {}

void BasicBlock::addInstruction(Instr* instruction) {
    if (!firstInst) {
        firstInst = instruction;
    } else {
        lastInst->setNext(instruction);
        instruction->setPrev(lastInst);
    }
    lastInst = instruction;

    // Проверяем, является ли инструкция Phi
    if (!firstPhi && instruction->getOpcode() == Opcode::Phi) {
        firstPhi = instruction;
    }
}

void BasicBlock::removeInstruction(Instr* instruction) {
    if (instruction == firstInst) {
        firstInst = instruction->getNext();
    }
    if (instruction == lastInst) {
        lastInst = instruction->getPrev();
    }
    if (instruction->getPrev()) {
        instruction->getPrev()->setNext(instruction->getNext());
    }
    if (instruction->getNext()) {
        instruction->getNext()->setPrev(instruction->getPrev());
    }
    instruction->setPrev(nullptr);
    instruction->setNext(nullptr);
}

Instr* BasicBlock::getFirstInstruction() const {
    return firstInst;
}

Instr* BasicBlock::getLastInstruction() const {
    return lastInst;
}

Instr* BasicBlock::getFirstPhi() const {
    return firstPhi;
}

void BasicBlock::addPredecessor(BasicBlock* pred) {
    preds.insert(pred);
}

void BasicBlock::addSuccessor(BasicBlock* succ) {
    if (succs.size() < 2) {
        succs.push_back(succ);
    }
}

const std::set<BasicBlock*>& BasicBlock::getPredecessors() const {
    return preds;
}

const std::vector<BasicBlock*>& BasicBlock::getSuccessors() const {
    return succs;
}

IRGraph* BasicBlock::getGraph() const {
    return graph;
}

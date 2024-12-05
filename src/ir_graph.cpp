#include "ir_graph.h"
#include <iostream>

IRGraph::IRGraph() : entryBlock(nullptr) {}

BasicBlock* IRGraph::createBasicBlock() {
    auto block = std::make_unique<BasicBlock>(this);
    BasicBlock* blockPtr = block.get();
    basicBlocks.push_back(std::move(block));

    if (!entryBlock) {
        entryBlock = blockPtr;
    }

    return blockPtr;
}

BasicBlock* IRGraph::getEntryBlock() const {
    return entryBlock;
}

const std::vector<std::unique_ptr<BasicBlock>>& IRGraph::getBasicBlocks() const {
    return basicBlocks;
}

void IRGraph::printGraph() const {
    std::cout << "IR Graph Structure:" << std::endl;

    for (const auto& block : basicBlocks) {
        std::cout << "Basic Block " << block.get() << ":" << std::endl;
        std::cout << "  Predecessors: ";
        for (auto pred : block->getPredecessors()) {
            std::cout << pred << " ";
        }
        std::cout << std::endl;

        std::cout << "  Successors: ";
        for (auto succ : block->getSuccessors()) {
            std::cout << succ << " ";
        }
        std::cout << std::endl;

        std::cout << "  Instructions:" << std::endl;
        auto instr = block->getFirstInstruction();
        while (instr) {
            std::cout << "    Instr ID: " << instr->getId()
                      << ", Opcode: " << static_cast<int>(instr->getOpcode())
                      << ", Type: " << instr->getType() << std::endl;
            instr = instr->getNext();
        }
        std::cout << std::endl;
    }
}

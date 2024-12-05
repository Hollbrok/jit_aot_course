#ifndef IRGRAPH_H
#define IRGRAPH_H

#include <vector>
#include <memory>
#include "bb.h"

class IRGraph {
public:
    IRGraph();

    BasicBlock* createBasicBlock();
    BasicBlock* getEntryBlock() const;
    const std::vector<std::unique_ptr<BasicBlock>>& getBasicBlocks() const;

    void printGraph() const;

private:
    BasicBlock* entryBlock;                               // 
    std::vector<std::unique_ptr<BasicBlock>> basicBlocks; // 
};

#endif // IRGRAPH_H

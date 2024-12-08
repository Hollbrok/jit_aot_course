#include "dfo.h"
#include <algorithm>

void DFO::dfs(BasicBlock* block) {
    if (visited.count(block)) {
        return;
    }

    visited.insert(block);
    for (auto* successor : block->getSuccessors()) {
        dfs(successor);
    }

    rpoOrder.push_back(block);
}

DFO::DFO(BasicBlock* entry) {
    dfs(entry);
}

const std::vector<BasicBlock*>& DFO::getRPOOrder() const {
    return rpoOrder;
}
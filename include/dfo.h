#ifndef DFO_H
#define DFO_H

#include <vector>
#include <stack>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <iterator>
#include "bb.h"

class DFO {
private:
    std::vector<BasicBlock*> rpoOrder; // RPO (Reverse Post-Order)
    std::unordered_set<BasicBlock*> visited;

    void dfs(BasicBlock* block);

public:
    explicit DFO(BasicBlock* entry);

    const std::vector<BasicBlock*>& getRPOOrder() const;
};

#endif // DFO_H

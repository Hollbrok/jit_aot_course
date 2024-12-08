#include "dom_tree_builder.h"
#include <limits>
#include <algorithm>

DomTree_Builder::DomTree_Builder(BasicBlock* entry) : entry(entry) {}

void DomTree_Builder::compute() {
    int time = 0;

    // Step 1: Perform DFS to label blocks and set parents
    depthFirstSearch(entry, time);

    // Step 2: Compute semi-dominators
    computeSemiDominators();

    // Step 3: Compute immediate dominators
    computeImmediateDominators();
}

void DomTree_Builder::depthFirstSearch(BasicBlock* block, int& time) {
    label[block] = time++;
    vertex.push_back(block);

    for (BasicBlock* succ : block->getSuccessors()) {
        if (label.find(succ) == label.end()) { // Not yet visited
            parent[succ] = block;
            depthFirstSearch(succ, time);
        }
    }
}

void DomTree_Builder::computeSemiDominators() {
    for (int i = vertex.size() - 1; i > 0; --i) {
        BasicBlock* w = vertex[i];
        semi[w] = i; // Initialize semi-dominator to itself

        for (BasicBlock* pred : w->getPredecessors()) {
            BasicBlock* u = find(pred);
            semi[w] = std::min(semi[w], semi[u]);
        }

        ancestor[w] = parent[w];
    }
}

void DomTree_Builder::computeImmediateDominators() {
    for (size_t i = 1; i < vertex.size(); ++i) {
        BasicBlock* w = vertex[i];
        BasicBlock* p = parent[w];

        BasicBlock* u = find(w);
        if (semi[u] < semi[w]) {
            idom[w] = u;
        } else {
            idom[w] = p;
        }
    }

    // Ensure dominator relationships are resolved
    for (size_t i = 1; i < vertex.size(); ++i) {
        BasicBlock* w = vertex[i];
        if (idom[w] != idom[idom[w]]) {
            idom[w] = idom[idom[w]];
        }
    }
}

BasicBlock* DomTree_Builder::find(BasicBlock* block) {
    if (ancestor[block] == nullptr) {
        return block;
    }

    BasicBlock* a = ancestor[block];
    BasicBlock* b = find(a);

    if (semi[best[a]] < semi[best[block]]) {
        best[block] = best[a];
    }

    ancestor[block] = b; // Path compression
    return best[block];
}

void DomTree_Builder::link(BasicBlock* u, BasicBlock* v) {
    ancestor[v] = u;
    best[v] = v;
}

BasicBlock* DomTree_Builder::getImmediateDominator(BasicBlock* block) const {
    auto it = idom.find(block);
    return it != idom.end() ? it->second : nullptr;
}

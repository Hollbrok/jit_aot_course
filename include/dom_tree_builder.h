#ifndef DOM_TREE_BUILDER_H
#define DOM_TREE_BUILDER_H

#include "bb.h"
#include <unordered_map>
#include <vector>
#include <stack>
#include <set>

class DomTree_Builder {
public:
    DomTree_Builder(BasicBlock* entry);
    
    // сompute the dominance tree
    void compute();

    // get the immediate dominator of a block
    BasicBlock* getImmediateDominator(BasicBlock* block) const;

private:
    BasicBlock* entry; // entry block of the graph

    // maps to store dominance relationships
    std::unordered_map<BasicBlock*, int> semi;     // semi-dominators
    std::unordered_map<BasicBlock*, BasicBlock*> idom; // immediate dominators
    std::unordered_map<BasicBlock*, std::vector<BasicBlock*>> domTree; // dominance tree

    std::vector<BasicBlock*> vertex; // blocks in DFS order
    std::unordered_map<BasicBlock*, BasicBlock*> parent; // DFS parent
    std::unordered_map<BasicBlock*, int> label; // DFS labels

    // DSU-related structures
    std::unordered_map<BasicBlock*, BasicBlock*> ancestor;
    std::unordered_map<BasicBlock*, BasicBlock*> best;

    // DFS and DSU helper methods
    void depthFirstSearch(BasicBlock* block, int& time);
    BasicBlock* find(BasicBlock* block);
    void link(BasicBlock* u, BasicBlock* v);

    // dominance calculation
    void computeSemiDominators();
    void computeImmediateDominators();
};

#endif // DOM_TREE_BUILDER_H

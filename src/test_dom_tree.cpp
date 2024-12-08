#include "dom_tree_builder.h"
#include "bb.h"
#include "ir_graph.h"
#include <cassert>
#include <iostream>

// Helper function to create a graph and its blocks
BasicBlock* createControlFlowGraph(IRGraph& graph, std::vector<BasicBlock*>& blocks) {
    BasicBlock* entry = graph.createBasicBlock();
    BasicBlock* b1 = graph.createBasicBlock();
    BasicBlock* b2 = graph.createBasicBlock();
    BasicBlock* b3 = graph.createBasicBlock();
    BasicBlock* exit = graph.createBasicBlock();

    // Simulate CFG connections
    entry->addSuccessor(b1);
    b1->addPredecessor(entry);

    b1->addSuccessor(b2);
    b2->addPredecessor(b1);

    b2->addSuccessor(b3);
    b3->addPredecessor(b2);

    b3->addSuccessor(exit);
    exit->addPredecessor(b3);

    // Add blocks to the list
    blocks = {entry, b1, b2, b3, exit};
    return entry;
}

void testLinearCFG() {
    std::cout << "Running testLinearCFG...\n";

    IRGraph graph;
    std::vector<BasicBlock*> blocks;
    BasicBlock* entry = createControlFlowGraph(graph, blocks);

    DomTree_Builder builder(entry);
    builder.compute();

    // Validate dominance tree
    assert(builder.getImmediateDominator(blocks[0]) == nullptr); // Entry block has no dominator
    assert(builder.getImmediateDominator(blocks[1]) == blocks[0]);
    assert(builder.getImmediateDominator(blocks[2]) == blocks[1]);
    assert(builder.getImmediateDominator(blocks[3]) == blocks[2]);
    assert(builder.getImmediateDominator(blocks[4]) == blocks[3]);

    std::cout << "[!] testLinearCFG passed.\n";
}

void testBranchingCFG() {
    std::cout << "Running testBranchingCFG...\n";

    IRGraph graph;
    BasicBlock* entry = graph.createBasicBlock();
    BasicBlock* b1 = graph.createBasicBlock();
    BasicBlock* b2 = graph.createBasicBlock();
    BasicBlock* b3 = graph.createBasicBlock();
    BasicBlock* exit = graph.createBasicBlock();

    // Simulate branching
    entry->addSuccessor(b1);
    entry->addSuccessor(b2);
    b1->addPredecessor(entry);
    b2->addPredecessor(entry);

    b1->addSuccessor(b3);
    b2->addSuccessor(b3);
    b3->addPredecessor(b1);
    b3->addPredecessor(b2);

    b3->addSuccessor(exit);
    exit->addPredecessor(b3);

    DomTree_Builder builder(entry);
    builder.compute();

    // Validate dominance tree
    assert(builder.getImmediateDominator(entry) == nullptr); // Entry block has no dominator
    assert(builder.getImmediateDominator(b1) == entry);
    assert(builder.getImmediateDominator(b2) == entry);
    assert(builder.getImmediateDominator(b3) == entry); // Dominated by entry (common parent)
    assert(builder.getImmediateDominator(exit) == b3);

    std::cout << "[!] testBranchingCFG passed.\n";
}

void testLoopCFG() {
    std::cout << "Running testLoopCFG...\n";

    IRGraph graph;
    BasicBlock* entry = graph.createBasicBlock();
    BasicBlock* b1 = graph.createBasicBlock();
    BasicBlock* b2 = graph.createBasicBlock();
    BasicBlock* exit = graph.createBasicBlock();

    // Simulate a loop
    entry->addSuccessor(b1);
    b1->addPredecessor(entry);

    b1->addSuccessor(b2);
    b2->addPredecessor(b1);

    b2->addSuccessor(b1); // Back edge
    b1->addPredecessor(b2);

    b2->addSuccessor(exit);
    exit->addPredecessor(b2);

    DomTree_Builder builder(entry);
    builder.compute();

    // Validate dominance tree
    assert(builder.getImmediateDominator(entry) == nullptr); // Entry block has no dominator
    assert(builder.getImmediateDominator(b1) == entry);
    assert(builder.getImmediateDominator(b2) == b1);
    assert(builder.getImmediateDominator(exit) == b2);

    std::cout << "[!] testLoopCFG passed.\n";
}

void testComplexCFG() {
    std::cout << "Running testComplexCFG...\n";

    IRGraph graph;
    BasicBlock* entry = graph.createBasicBlock();
    BasicBlock* b1 = graph.createBasicBlock();
    BasicBlock* b2 = graph.createBasicBlock();
    BasicBlock* b3 = graph.createBasicBlock();
    BasicBlock* b4 = graph.createBasicBlock();
    BasicBlock* exit = graph.createBasicBlock();

    // Complex CFG
    entry->addSuccessor(b1);
    b1->addPredecessor(entry);

    b1->addSuccessor(b2);
    b1->addSuccessor(b3);
    b2->addPredecessor(b1);
    b3->addPredecessor(b1);

    b2->addSuccessor(b4);
    b3->addSuccessor(b4);
    b4->addPredecessor(b2);
    b4->addPredecessor(b3);

    b4->addSuccessor(exit);
    exit->addPredecessor(b4);

    DomTree_Builder builder(entry);
    builder.compute();

    // Validate dominance tree
    assert(builder.getImmediateDominator(entry) == nullptr);
    assert(builder.getImmediateDominator(b1) == entry);
    assert(builder.getImmediateDominator(b2) == b1);
    assert(builder.getImmediateDominator(b3) == b1);
    assert(builder.getImmediateDominator(b4) == b1); // Dominated by b1 (common parent)
    assert(builder.getImmediateDominator(exit) == b4);

    std::cout << "[!] testComplexCFG passed.\n";
}

int main() {
    testLinearCFG();
    testBranchingCFG();
    testLoopCFG();
    testComplexCFG();
    std::cout << "All tests passed.\n";
    return 0;
}

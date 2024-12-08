#include "dfo.h"
#include "bb.h"
#include "ir_graph.h"
#include <iostream>
#include <cassert>

// BasicBlock* createTestGraph(IRGraph* graph) {
//     auto* blockA = new BasicBlock(graph);
//     auto* blockB = new BasicBlock(graph);
//     auto* blockC = new BasicBlock(graph);
//     auto* blockD = new BasicBlock(graph);

//     // Graph :
//     // A -> B -> C -> D
//     //      \-------^
//     blockA->addSuccessor(blockB);
//     blockB->addSuccessor(blockC);
//     blockC->addSuccessor(blockD);
//     blockB->addSuccessor(blockD);

//     return blockA;
// }

void testDFO() {
    IRGraph* graph = new IRGraph();

    auto* blockA = new BasicBlock(graph);
    auto* blockB = new BasicBlock(graph);
    auto* blockC = new BasicBlock(graph);
    auto* blockD = new BasicBlock(graph);

    // Graph :
    // A -> B -> C -> D
    //      \-------^
    blockA->addSuccessor(blockB);
    blockB->addSuccessor(blockC);
    blockC->addSuccessor(blockD);
    blockB->addSuccessor(blockD);

    std::cout << "Initial Order:\n" << blockA << " " << blockB << " " << blockC << " " << blockD << std::endl;

    BasicBlock* entry = blockA;

    // Calculate RPO
    DFO dfo(entry);
    const auto& order = dfo.getRPOOrder();

    // Expected: D, C, B, A
    std::cout << "RPO Order:" << std::endl;
    for (const auto* block : order) {
        std::cout << block << " ";
    }

    std::cout << std::endl;

    // Check number of blocks
    assert(order.size() == 4);
    std::cout << "[!] Test #1 passed (size check)" << std::endl;


    assert(order[3] == blockA);
    assert(order[2] == blockB);
    assert(order[1] == blockC);
    assert(order[0] == blockD);
    std::cout << "[!] Test #2 passed (RPO order check)" << std::endl;


    // Ensure all blocks are in the RPO order
    std::unordered_map<const BasicBlock*, int> blockIndices;
    for (size_t i = 0; i < order.size(); ++i) {
        blockIndices[order[i]] = static_cast<int>(i);
    }

    // Check that every block in the graph is in the RPO
    assert(blockIndices.size() == 4); // Graph has 4 blocks

    std::cout << "[!] Test #3 passed (every block in the graph is in the RPO)" << std::endl;

    // Validate RPO correctness: predecessors appear later than successors
    for (const auto* block : order) {
        for (const auto* successor : block->getSuccessors()) {
            assert(blockIndices[block] > blockIndices[successor]);
        }
    }

    std::cout << "[!] Test #4 passed (RPO Order is valid and contains all blocks.)" << std::endl;

    assert(order[0] == entry->getSuccessors()[0]->getSuccessors()[1]); // Last block (D)
    assert(order[1] == entry->getSuccessors()[0]->getSuccessors()[0]); // C
    assert(order[2] == entry->getSuccessors()[0]); // B
    assert(order[3] == entry); // A

    std::cout << "[!] Test #5 passed" << std::endl;

    std::cout << "[!] All DFO tests passed successfully." << std::endl;

    delete graph;
}

int main() {
    testDFO();
    return 0;
}

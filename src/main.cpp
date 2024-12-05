#include <iostream>
#include "ir_graph.h"
#include "instr.h"

#include <memory>

// Factorial IR graph 
IRGraph buildFactorialGraph() {
    IRGraph graph;

    BasicBlock* entryBlock = graph.createBasicBlock();  // Входной блок
    BasicBlock* returnOneBlock = graph.createBasicBlock(); // Возврат 1
    BasicBlock* recursionBlock = graph.createBasicBlock(); // Рекурсия
    BasicBlock* mergeBlock = graph.createBasicBlock();  // Завершение

    // === Входной базовый блок ===
    // Проверяем условие: n <= 1
    auto paramN = new Instr(1, Opcode::Cmp, "s32", entryBlock);
    auto condition = new Instr(2, Opcode::Branch, "void", entryBlock);

    entryBlock->addInstruction(paramN);
    entryBlock->addInstruction(condition);

    // Связываем базовые блоки
    entryBlock->addSuccessor(returnOneBlock);  // Если n <= 1
    entryBlock->addSuccessor(recursionBlock); // Если n > 1
    returnOneBlock->addPredecessor(entryBlock);
    recursionBlock->addPredecessor(entryBlock);

    // === Блок возврата 1 ===
    auto returnOne = new Instr(3, Opcode::Return, "s32", returnOneBlock);
    returnOneBlock->addInstruction(returnOne);

    returnOneBlock->addSuccessor(mergeBlock);
    mergeBlock->addPredecessor(returnOneBlock);

    // === Блок рекурсии ===
    // factorial(n - 1)
    auto nMinusOne = new Instr(4, Opcode::Sub, "s32", recursionBlock);
    auto recursiveCall = new Instr(5, Opcode::Phi, "s32", recursionBlock);
    auto multiply = new Instr(6, Opcode::Mul, "s32", recursionBlock);
    auto returnResult = new Instr(7, Opcode::Return, "s32", recursionBlock);

    recursionBlock->addInstruction(nMinusOne);
    recursionBlock->addInstruction(recursiveCall);
    recursionBlock->addInstruction(multiply);
    recursionBlock->addInstruction(returnResult);


    recursionBlock->addSuccessor(mergeBlock);
    mergeBlock->addPredecessor(recursionBlock);

    return graph;
}


int main() {
    IRGraph factorialGraph = buildFactorialGraph();
    factorialGraph.printGraph();

    return 0;
}

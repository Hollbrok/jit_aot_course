#include "instr.h"
#include "bb.h"

Instr::Instr(int id, Opcode opcode, const std::string& type, BasicBlock* parent)
    : id(id), opcode(opcode), type(type), parentBlock(parent), prev(nullptr), next(nullptr) {}

void Instr::setPrev(Instr* instruction) {
    prev = instruction;
}

void Instr::setNext(Instr* instruction) {
    next = instruction;
}

Instr* Instr::getPrev() const {
    return prev;
}

Instr* Instr::getNext() const {
    return next;
}

void Instr::addUser(Instr* user) {
    users.push_back(user);
}

const std::vector<Instr*>& Instr::getUsers() const {
    return users;
}

int Instr::getId() const {
    return id;
}

Opcode Instr::getOpcode() const {
    return opcode;
}

const std::string& Instr::getType() const {
    return type;
}

BasicBlock* Instr::getParentBlock() const {
    return parentBlock;
}

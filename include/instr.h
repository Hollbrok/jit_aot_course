#ifndef INSTR_H
#define INSTR_H

#include <vector>
#include <memory>
#include <string>
#include "value.h"

class BasicBlock;

enum class Opcode {
    Add,
    Mul,
    Sub,
    Div,
    Cmp,
    Branch,
    Return,
    Phi,
    // ...
};

class Instr {
public:
    Instr(int id, Opcode opcode, const std::string& type, BasicBlock* parent);

    void setPrev(Instr* instruction);
    void setNext(Instr* instruction);
    Instr* getPrev() const;
    Instr* getNext() const;

    void addUser(Instr* user);
    const std::vector<Instr*>& getUsers() const;

    int getId() const;
    Opcode getOpcode() const;
    const std::string& getType() const;
    BasicBlock* getParentBlock() const;

private:
    int id;                                         // 
    Opcode opcode;                                  // 
    std::string type;                               // 
    BasicBlock* parentBlock;                        // 
    Instr* prev;                                    // 
    Instr* next;                                    // 
    std::vector<std::shared_ptr<Value>> inputs;     // 
    std::vector<Instr*> users;                      // 
};

#endif // INSTR_H

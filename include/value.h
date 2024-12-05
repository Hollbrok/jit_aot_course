#ifndef VALUE_H
#define VALUE_H

#include <string>
#include <memory>
#include <vector>

enum class ValueType {
    Constant,   // 
    Variable,   // 
    Instruction // instr result
};

//
class Value {
protected:
    int id;                                                 // 
    std::string type;                                       //
    std::vector<std::shared_ptr<Value>> users;              //

public:
    Value(int id, const std::string& type)
        : id(id), type(type) {}

    int getId() const { return id; }
    std::string getType() const { return type; }

    void addUser(std::shared_ptr<Value> user) {
        users.push_back(user);
    }

    const std::vector<std::shared_ptr<Value>>& getUsers() const {
        return users;
    }
};

#endif // VALUE_H

#pragma once

#include <memory>
#include <vector>
#include <cassert>
#include "nodes.h"

struct ExpressionFactory {

    Constant* constant(int value) {
        auto pos = std::find_if(constants.begin(), constants.end(), [value] (auto& c) {
            return c->value == value;
        });
        if (pos != constants.end()) {
            return pos->get();
        }
        return constants.insert(constants.end(), std::make_unique<Constant>(value))->get();
    }

    Variable* variable(std::string name) {
        auto pos = std::find_if(variables.begin(), variables.end(), [&name] (auto& var) {
            return var->name == name;
        });
        if (pos != variables.end()) {
            return pos->get();
        }
        return variables.insert(variables.end(), std::make_unique<Variable>(name))->get();
    }

    BinOp* binOp(Node* left, std::string op, Node* right) {
        std::unique_ptr<BinOp> binOp;
        if (op == "+") {
            binOp = std::make_unique<AddOp>();
        } else if (op == "-") {
            binOp = std::make_unique<SubOp>();
        } else if (op == "*") {
            binOp = std::make_unique<MultOp>();
        } else if (op == "/") {
            binOp = std::make_unique<DivOp>();
        } else {
            assert(false);
        }
        binOp->left = left;
        binOp->right = right;
        auto* binOpPtr = binOp.get();
        nodes.push_back(std::move(binOp));
        return binOpPtr;
    }

    std::vector<std::unique_ptr<Constant>> constants;
    std::vector<std::unique_ptr<Variable>> variables;
    std::vector<std::unique_ptr<BinOp>> nodes;
};

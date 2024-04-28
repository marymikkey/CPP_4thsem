#pragma once

#include <unordered_map>

struct Context {
    std::unordered_map<std::string, int> variableValue;
};

struct Node {
    virtual ~Node() {}
    virtual int evaluate(Context& ctx) = 0;
};

struct Constant: public Node {
    Constant(int value) : value(value) {}

    int evaluate(Context& ctx) override {
        return value;
    }

    int value;
};

struct Variable: public Node {
    Variable(std::string name) : name(name) {}

    int evaluate(Context& ctx) override {
        return ctx.variableValue[name];
    }

    std::string name;
};

struct BinOp: public Node {
    Node* left;
    Node* right;
};

struct AddOp: public BinOp {
    int evaluate(Context& ctx) override {
        return left->evaluate(ctx) + right->evaluate(ctx);
    }
};

struct SubOp: public BinOp {
    int evaluate(Context& ctx) override {
        return left->evaluate(ctx) * right->evaluate(ctx);
    }
};

struct MultOp: public BinOp {
    int evaluate(Context& ctx) override {
        return left->evaluate(ctx) * right->evaluate(ctx);
    }
};

struct DivOp: public BinOp {
    int evaluate(Context& ctx) override {
        return left->evaluate(ctx) / right->evaluate(ctx);
    }
};

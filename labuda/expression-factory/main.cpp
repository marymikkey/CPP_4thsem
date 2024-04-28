#include "factory.h"
#include <iostream>

int main() {
    ExpressionFactory f;
    Context ctx;
    ctx.variableValue["x"] = 12;

    auto* c2 = f.constant(2);
    auto* c3 = f.constant(3);
    auto* const3 = f.constant(3);

    auto* varX = f.variable("x");

    auto* node1 = f.binOp(c2, "+", c3);
    auto* root = f.binOp(node1, "*", varX);
    
    std::cout << root->evaluate(ctx) << std::endl;
}

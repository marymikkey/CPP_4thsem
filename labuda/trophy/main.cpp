#include "check_point.h"
#include "visitors.h"

#include <vector>
#include <memory>


int main() {
    std::vector<std::unique_ptr<CheckPoint>> checkPoints;

    checkPoints.push_back(std::make_unique<CheckPoint>("cp1", 0.1, 0.1));
    checkPoints.push_back(std::make_unique<OptionalCheckPoint>("cp2", 0.2, 0.2, 2.2));
    checkPoints.push_back(std::make_unique<OptionalCheckPoint>("cp3", 0.3, 0.3, 3.3));

    PrintVisitor printer;
    PenaltyVisitor penalty;
    for (auto& cp: checkPoints) {
        cp->accept(printer);
        cp->accept(penalty);
    }

    std::cout << "Total penalty: " << penalty.penalty << std::endl;
}

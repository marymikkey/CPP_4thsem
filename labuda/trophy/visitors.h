#pragma once

#include "check_point.h"

#include <iostream>


struct PrintVisitor : public Visitor {
    size_t seq = 0;

    void visit(CheckPoint& cp) override {
        std::cout << "\t" << ++seq << "\t" << cp.name << "\t" << cp.lat << "\t" << cp.lon << "\t" << "незачёт СУ" << std::endl;
    }

    void visit(OptionalCheckPoint& ocp) override {
        std::cout << "\t" << ++seq << "\t" << ocp.name << "\t" << ocp.lat << "\t" << ocp.lon << "\t" << ocp.penalty << std::endl;
    }
};

struct PenaltyVisitor : public Visitor {
    double penalty = 0.0;

    void visit(CheckPoint& cp) override {}

    void visit(OptionalCheckPoint& ocp) override {
        penalty += ocp.penalty;
    }
};


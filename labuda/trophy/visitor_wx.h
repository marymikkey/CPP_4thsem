#pragma once

#include <wx/grid.h>
#include <string>

struct GridVisitor : public Visitor {
    size_t row = 0;
    wxGrid* grid;

    void visit(CheckPoint& cp) override {
        grid->AppendRows();
        grid->SetCellValue(row, 0, cp.name);
        grid->SetCellValue(row, 1, std::to_string(cp.lat));
        grid->SetCellValue(row, 2, std::to_string(cp.lon));
        ++row;
    }

    void visit(OptionalCheckPoint& ocp) override {
        visit(static_cast<CheckPoint&>(ocp));
        grid->SetCellValue(row - 1, 3, std::to_string(ocp.penalty));
    }
};

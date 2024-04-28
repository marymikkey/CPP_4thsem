#include "check_point.h"
#include "visitor_wx.h"

#include <wx/wx.h>
#include <wx/grid.h>
#include <vector>
#include <memory>

class Frame: public wxFrame {
public:
    Frame() : wxFrame(nullptr, wxID_ANY, "Trophy") {
        wxGrid* grid = new wxGrid(this,
                -1,
                wxPoint( 0, 0 ),
                wxSize( 400, 300 ) );

        grid->CreateGrid(0, 4);

        grid->SetColFormatFloat(1, 6, 2);
        grid->SetColFormatFloat(2, 6, 2);
        grid->SetColFormatFloat(3, 6, 2);

        GridVisitor visitor;
        visitor.grid = grid;

        std::vector<std::unique_ptr<CheckPoint>> checkPoints;
        checkPoints.push_back(std::make_unique<CheckPoint>("cp1", 0.1, 0.1));
        checkPoints.push_back(std::make_unique<OptionalCheckPoint>("cp2", 0.2, 0.2, 2.2));
        checkPoints.push_back(std::make_unique<OptionalCheckPoint>("cp3", 0.3, 0.3, 3.3));

        for (auto& cp: checkPoints) {
            cp->accept(visitor);
        }

        grid->Fit();
        SetClientSize(grid->GetSize());
    }
};

class App : public wxApp {
public:
    bool OnInit() override {
        Frame *frame = new Frame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(App);

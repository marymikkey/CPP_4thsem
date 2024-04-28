#pragma once

#include <iostream>

class CheckPoint;
class OptionalCheckPoint;

struct Visitor {
    virtual void visit(CheckPoint& cp) = 0;
    virtual void visit(OptionalCheckPoint& ocp) = 0;
};

struct CheckPoint {
    std::string name;
    double lat;
    double lon;

    CheckPoint(std::string name, double lat, double lon) : name(name), lat(lat), lon(lon) {}

    virtual void accept(Visitor& v) { v.visit(*this); }

};

struct OptionalCheckPoint: public CheckPoint {
    double penalty;

    OptionalCheckPoint(std::string name, double lat, double lon, double penalty) : CheckPoint(name, lat, lon), penalty(penalty) {}

    void accept(Visitor& v) override { v.visit(*this); }
};

#pragma once

#include "device.hpp"
#include "../math/mna.hpp"

class CurrentSource: public Device{
public: 
    CurrentSource(std::string name, std::vector<std::string> nodes, double I):
                Device(name, nodes, DeviceType::CurrentSource), i(I) {}

    ~CurrentSource() = default;

    void pattern(MNA& mna) override{}

    void bindMatrix(MNA& mna) override {
        const int p = nodeIds[0];
        const int n = nodeIds[1];

        if(p >= 0){
            pos = &mna.rhs(p);
        }
        if(n >= 0){
            neg = &mna.rhs(n);
        }
    }

    void stamp() override {
        if(pos) *pos -= i;
        if(neg) *neg += i;
    }

private:
    double i;

    double* pos = nullptr;
    double* neg = nullptr;
};

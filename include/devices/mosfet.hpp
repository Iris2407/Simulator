#pragma once

#include "device.hpp"
#include "../math/mna.hpp"
#include "../models/model.hpp"

class MOSFET: public Device{
public:
    MOSFET(std::string name, std::vector<std::string> nodes, const Model* model, double w = 1.0, double l = 1.0):
            Device(name, nodes, DeviceType::MOSFET), model_(model), w_(w), l_(l) {}

    const Model* model() const { return model_; }

    void pattern(MNA& mna) override{
        const int d = nodeIds[0];
        const int s = nodeIds[2];

        if(d >= 0) mna.addPattern(d, d);
        if(s >= 0) mna.addPattern(s, s);
        if(d >= 0 && s >= 0){
            mna.addPattern(d, s);
            mna.addPattern(s, d);
        }
    }

    void bindMatrix(MNA& mna) override{
        const int d = nodeIds[0];
        const int s = nodeIds[2];

        if(d >= 0) A11 = mna.ptr(d, d);
        if(s >= 0) A22 = mna.ptr(s, s);
        if(d >= 0 && s >= 0){
            A12 = mna.ptr(d, s);
            A21 = mna.ptr(s, d);
        }
    }

    void stamp() override{
        const double g = model_ ? model_->mosDrainSourceConductance(w_, l_) : 0.0;

        if(A11) *A11 += g;
        if(A12) *A12 -= g;
        if(A21) *A21 -= g;
        if(A22) *A22 += g;
    }

private:
    const Model* model_;
    double w_;
    double l_;

    double* A11 = nullptr;
    double* A12 = nullptr;
    double* A21 = nullptr;
    double* A22 = nullptr;
};

#pragma once

#include "device.hpp"
#include "../math/mna.hpp"
#include "../models/model.hpp"

class Diode: public Device{
public:
    Diode(std::string name, std::vector<std::string> nodes, const Model* model, double area = 1.0):
            Device(name, nodes, DeviceType::Diode), model_(model), area_(area) {}

    const Model* model() const { return model_; }

    void pattern(MNA& mna) override{
        const int p = nodeIds[0];
        const int n = nodeIds[1];

        if(p >= 0) mna.addPattern(p, p);
        if(n >= 0) mna.addPattern(n, n);
        if(p >= 0 && n >= 0){
            mna.addPattern(p, n);
            mna.addPattern(n, p);
        }
    }

    void bindMatrix(MNA& mna) override{
        const int p = nodeIds[0];
        const int n = nodeIds[1];

        if(p >= 0) A11 = mna.ptr(p, p);
        if(n >= 0) A22 = mna.ptr(n, n);
        if(p >= 0 && n >= 0){
            A12 = mna.ptr(p, n);
            A21 = mna.ptr(n, p);
        }
    }

    void stamp() override{
        const double g = model_ ? model_->diodeConductance(area_) : 0.0;

        if(A11) *A11 += g;
        if(A12) *A12 -= g;
        if(A21) *A21 -= g;
        if(A22) *A22 += g;
    }

private:
    const Model* model_;
    double area_;

    double* A11 = nullptr;
    double* A12 = nullptr;
    double* A21 = nullptr;
    double* A22 = nullptr;
};

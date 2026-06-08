#pragma once

#include "device.hpp"
#include "../math/mna.hpp"
#include "../models/model.hpp"

class BJT: public Device{
public:
    BJT(std::string name, std::vector<std::string> nodes, const Model* model, double area = 1.0):
            Device(name, nodes, DeviceType::BJT), model_(model), area_(area) {}

    const Model* model() const { return model_; }

    void pattern(MNA& mna) override{
        addPairPattern(mna, 0, 2);
        addPairPattern(mna, 1, 2);
    }

    void bindMatrix(MNA& mna) override{
        bindPair(mna, 0, 2, c_e_);
        bindPair(mna, 1, 2, b_e_);
    }

    void stamp() override{
        const double gbe = model_ ? model_->bjtBaseEmitterConductance(area_) : 0.0;
        const double gce = model_ ? model_->bjtCollectorEmitterConductance(area_) : 0.0;

        stampPair(c_e_, gce);
        stampPair(b_e_, gbe);
    }

private:
    struct PairPtrs {
        double* A11 = nullptr;
        double* A12 = nullptr;
        double* A21 = nullptr;
        double* A22 = nullptr;
    };

    void addPairPattern(MNA& mna, int a, int b){
        const int p = nodeIds[a];
        const int n = nodeIds[b];

        if(p >= 0) mna.addPattern(p, p);
        if(n >= 0) mna.addPattern(n, n);
        if(p >= 0 && n >= 0){
            mna.addPattern(p, n);
            mna.addPattern(n, p);
        }
    }

    void bindPair(MNA& mna, int a, int b, PairPtrs& ptrs){
        const int p = nodeIds[a];
        const int n = nodeIds[b];

        if(p >= 0) ptrs.A11 = mna.ptr(p, p);
        if(n >= 0) ptrs.A22 = mna.ptr(n, n);
        if(p >= 0 && n >= 0){
            ptrs.A12 = mna.ptr(p, n);
            ptrs.A21 = mna.ptr(n, p);
        }
    }

    void stampPair(PairPtrs& ptrs, double g){
        if(ptrs.A11) *ptrs.A11 += g;
        if(ptrs.A12) *ptrs.A12 -= g;
        if(ptrs.A21) *ptrs.A21 -= g;
        if(ptrs.A22) *ptrs.A22 += g;
    }

    const Model* model_;
    double area_;
    PairPtrs c_e_;
    PairPtrs b_e_;
};

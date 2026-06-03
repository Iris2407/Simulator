#pragma once
#include "device.hpp"

class Resistor: public Device{
    public:
    Resistor(std::string name, std::vector<std::string> nodes): 
            Device(name, nodes, DeviceType::Resistor){}
            
    ~Resistor() = default;

    void stamp() override {
        double g = 1.0/r;

        *A11 += g;
        *A22 += g;
        *A12 -= g;
        *A22 -= g; 
    }

private:
    double r;

    double* A11;
    double* A12;
    double* A21;
    double* A22;
};
#pragma once

#include "device.hpp"

class Capacitor: public Device{
public:
    Capacitor(std::string name, std::vector<std::string> nodes, double C):
            Device(name, nodes, DeviceType::Capacitor), c(C){}

    /** The capacitor is considered as open,
     * so it does not contribute to the mna matrix
     */
    void pattern(MNA& mna) override{}
    void bindMatrix(MNA& mna) override{}
    void stamp() override{}

private:
    double c;
};
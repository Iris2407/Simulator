#pragma once

#include "device.hpp"

class CurrentSource: public Device{
public: 
    CurrentSource(std::string name, std::vector<std::string> nodes):
                Device(name, nodes, DeviceType::CurrentSource) {}

    ~CurrentSource() = default;

    void stamp() override {
        *pos -= i;
        *neg += i;
    }

private:
    double i;

    double* pos;
    double* neg;
};
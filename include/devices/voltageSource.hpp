#pragma once

#include "device.hpp"

class VoltageSource: public Device{
public:
    VoltageSource(std::string name, std::vector<std::string> nodes):
                Device(name, nodes, DeviceType::VoltageSource) {}

    void stamp() override {}

private:
    double v;

    double * posBranch;
    double * negBranch;
    double * branchPos;
    double * branchNeg;

    int rhsIdx;
};
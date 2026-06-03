#pragma once
#include <memory>

#include "../math/matrix.h"
#include "../core/nodeMap.h"

class Device;

class Circuit{
public:
    Circuit() = default;
    ~Circuit() = default;

    bool build();

    void addDevice(std::string name, std::vector<std::string> nodes);

private:
    Matrix MNA;
    std::vector<double> rhs;
    std::vector<double> solution;

    std::vector<std::unique_ptr<Device>> devices;

    NodeMap nodeMap;
};
#pragma once
#include <memory>

#include "../math/mna.hpp"
#include "../core/nodeMap.h"

class Device;

class Circuit{
public:
    Circuit() = default;
    ~Circuit() = default;

    template<class T, class... Args>
    void addDevice(Args&&... args);

    bool build();

    int allocateUnknown();

    bool solve();

private:
    MNA mna;

    std::vector<std::unique_ptr<Device>> devices;

    int nextUnknown = 0;

    NodeMap nodeMap;
};
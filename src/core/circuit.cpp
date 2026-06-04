#include "../include/core/circuit.h"

#include "../include/devices/device.hpp"

template<class T, class... Args>
void Circuit::addDevice(Args&&... args){
    devices.emplace_back(
        std::make_unique<T>(
            std::forward<Args>(args)...
        )
    )
}

int Circuit::allocateUnknown(){
    return nextUnknown++;
}

bool Circuit::build(){
    nodeMap.build(devices);

    for(auto& d: devices){
        d->bindNodes(nodeMap);
    }

    nextUnknown = nodeMap.nodeCount();

    for(auto& d: devices){
        d->allocateUnknown(*this);
    }

    mna.resize(nextUnknown);

    for(auto& d: devices){
        d->pattern(mna);
    }

    mna.build();

    for(auto&d: devices){
        d->bindMatrix(mna);
    }

    return true;
}

bool Circuit::solve(){
    mna.clear();

    for(auto& d: devices){
        d->stamp();
    }

    return mna.solve();
}

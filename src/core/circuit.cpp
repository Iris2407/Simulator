#include "../include/core/circuit.h"

#include "../include/devices/device.hpp"
#include "../include/models/model.hpp"

const Model* Circuit::addModel(std::unique_ptr<Model> model){
    const std::string name = model->name();
    auto& slot = models[name];
    slot = std::move(model);
    return slot.get();
}

const Model* Circuit::findModel(const std::string& name) const{
    auto it = models.find(name);
    return it == models.end() ? nullptr : it->second.get();
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

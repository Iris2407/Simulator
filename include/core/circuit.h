#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../core/nodeMap.h"
#include "../devices/device.hpp"
#include "../math/mna.hpp"
#include "../models/model.hpp"

class Circuit{
public:
    Circuit() = default;
    ~Circuit() = default;

    template<class T, class... Args>
    void addDevice(Args&&... args){
        devices.emplace_back(
            std::make_unique<T>(
                std::forward<Args>(args)...
            )
        );
    }

    const Model* addModel(std::unique_ptr<Model> model);

    const Model* findModel(const std::string& name) const;

    bool build();

    int allocateUnknown();

    bool solve();

private:
    MNA mna;

    std::vector<std::unique_ptr<Device>> devices;

    std::unordered_map<std::string, std::unique_ptr<Model>> models;

    int nextUnknown = 0;

    NodeMap nodeMap;
};

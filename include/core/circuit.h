#pragma once
#include <memory>
#include <iosfwd>
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

    void printOperatingPoint(std::ostream& os) const;

private:
    struct SolveStats {
        bool converged = false;
        int iterations = 0;
        int maxIterations = 0;
        int dampedSteps = 0;
        double finalDelta = 0.0;
        double tolerance = 0.0;
        double cpuSeconds = 0.0;
    };

    MNA mna;

    std::vector<std::unique_ptr<Device>> devices;

    std::unordered_map<std::string, std::unique_ptr<Model>> models;

    int nextUnknown = 0;

    NodeMap nodeMap;

    SolveStats solveStats;
};

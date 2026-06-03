#include "../include/core/nodeMap.h"
#include "../include/devices/device.hpp"

void NodeMap::build(std::vector<std::unique_ptr<Device>> devices){
    for(auto& device : devices){
        std::vector<std::string> nodes = device->getNodes();
        for(auto& node : nodes){
            if(node == "0" || node == "GND"){
                continue;
            }
            auto it = name_to_idx.find(node);
            if(it != name_to_idx.end()){
                continue;
            }
            name_to_idx[node] = name_to_idx.size();
            idx_to_name.push_back(node);
        }
    }
}

int NodeMap::idxOf(std::string name) const {
    if(name == "0" || name == "GND"){
        return -1;
    }
    
    auto it = name_to_idx.find(name);
    if(it == name_to_idx.end()){
        throw std::runtime_error("Unknown node: " + name);
    }

    return it->second;
}

const std::vector<std::string>& NodeMap::nodeNameByIdx() const {
    return idx_to_name;
}

int NodeMap::nodeCount(){
    return name_to_idx.size();
}
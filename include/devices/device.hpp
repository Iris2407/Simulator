#include <string>
#include <vector>

enum class DeviceType{
    Resistor,
    Inductor,
    Capacitor,
    VoltageSource,
    CurrentSource,
    Diode,
    BJT,
    MOSFET
};

const char* deviceTypeName(DeviceType type){
    switch (type)
    {
        case DeviceType::Resistor:{
            return "Resistor";
        }
        case DeviceType::Inductor:{
            return "Inductor";
        }
        case DeviceType::Capacitor:{
            return "Capacitor";
        }
        case DeviceType::VoltageSource:{
            return "Voltage Source";
        }
        case DeviceType::CurrentSource:{
            return "Current Source";
        }
        case DeviceType::Diode:{
            return "Diode";
        }
        case DeviceType::BJT:{
            return "BJT";
        }
        case DeviceType::MOSFET:{
            return "MOSFET";
        }
        default:{
            return "Unknown";
        }
    }
}

class Device{
    public:
    Device(std::string n, std::vector<std::string> ns): name(n), nodes(ns){}
    virtual ~Device() = default;
private:
    std::string name;
    std::vector<std::string> nodes;
};
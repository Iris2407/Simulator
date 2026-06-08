#pragma once

#include <cassert>

#include "device.hpp"

/** The value of the Capacitor is not used in the dc op analysis
 *  So we just check the value of it satisfies C > 0
 */

class Capacitor: public Device{
public:
    Capacitor(std::string name, std::vector<std::string> nodes, double C):
            Device(name, nodes, DeviceType::Capacitor){
        assert(C > 0.0);
    }

    /** The capacitor is considered as open,
     * so it does not contribute to the mna matrix
     */
    void pattern(MNA&) override{}
    void bindMatrix(MNA&) override{}
    void stamp() override{}
};

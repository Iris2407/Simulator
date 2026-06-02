#pragma once
#include <string>
#include <fstream>

#include "circuit.h"
#include "device.hpp"

class Parser{
public:
    Parser(std::string f, Circuit& c): file(f), filename(f), circuit(c){}
    ~Parser() = default;

    bool parse();

private:
    std::ifstream file;
    std::string filename;
    Circuit circuit;
};
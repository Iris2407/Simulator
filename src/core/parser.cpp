#include <iostream>
#include <sstream>

#include "../include/core/parser.h"
#include "../include/core/circuit.h"

#include "../../utils/string_utils.hpp"

bool Parser::parse(Circuit& circuit){
    if (!file.is_open()) {
        std::cerr << "Can not open file <" << filename << ">!" << std::endl;
        return false;
    }
    std::string line;
    
    file >> line;
    while(std::getline(file, line)){
        line = trim(line);
        if(line.at(0) == '*'){
            continue;
        }
    }
}
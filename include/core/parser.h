#pragma once
#include <string>
#include <fstream>

class Circuit;
class Device;

class Parser{
public:
    Parser(std::string f): file(f), filename(f){}
    ~Parser() = default;

    bool parse(Circuit& circuit);

private:
    std::ifstream file;
    std::string filename;
};
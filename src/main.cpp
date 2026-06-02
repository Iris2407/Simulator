#include <iostream>
#include <fstream>

int main(int argc, char* argv[]){
    if(argc != 2 && argc != 3){
        std::cerr << "Usage: " << argv[0] << " <inputfile> " <<
            " <outputfile>[optional] " << std::endl;
        return 1;
    }

    std::ofstream ofs;
    std::ostream* os = &std::cout;
    if(argc == 3){
        ofs.open(argv[2], std::ios::out | std::ios::trunc);
        if(!ofs){
            std::cerr << "Fail to open/create " << argv[2] << std::endl;
            return 1;
        }
        os = &ofs;
    }

    return 0;
}
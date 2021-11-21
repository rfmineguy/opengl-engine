#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

//
//  File functions
//
inline void readFile(std::string path, std::string& contents) {
    std::ifstream ifs;
    ifs.open(path, std::ios::in);
    if (ifs.fail()) {
        std::cerr << std::strerror(errno) << std::endl;
    }
    if (ifs.is_open()) {
        std::string s;
        std::stringstream ss;
        while(std::getline(ifs, s)) {
            ss << s << "\n";
        }
        contents = ss.str();
        ifs.close();
    }
}



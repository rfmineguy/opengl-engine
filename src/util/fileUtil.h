#pragma once
#include "../corepch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <filesystem>

//
//  File functions
//
namespace Firefly {
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

class FileUtil {
public:
    static std::string ReadFile(const char* path) {
        std::fstream fs(path, std::ios::in);
        std::stringstream ss;
        if (fs.fail()) {
            LOG_CRITICAL("Failed to open file");
        }
        else {
            std::string s;
            while (std::getline(fs, s)) {
                ss << s;
            }
        }

        return ss.str();
    }

    static bool CreateFile(const std::string& path) {
        std::fstream fs(path, std::ios::out);
        if (fs.is_open()) {
            fs.close();
        }
        fs.open(path, std::ios::out);
        if (fs.fail()) {
            LOG_CRITICAL("Failed to create file");
            return false;
        }
        return true;
    }

    /*
     *  Initialize the project directory with the essential files/folders
     *    - projectDir
     *      - assets
     *        - atlas
     *        - textures
     *        - shaders
     *        - scripts
     *        - scenes
     *      - .project  (contains user preferences for the engine)
     *
     */
    static bool CreateProjectDirectory(const std::string& path) {
        bool status = false;
        status = std::filesystem::create_directory(path + "/assets");
        status = std::filesystem::create_directory(path + "/textures");
        status = std::filesystem::create_directory(path + "/shaders");
        status = std::filesystem::create_directory(path + "/scripts");
        status = std::filesystem::create_directory(path + "/scenes");
        return status;
    }
};
}

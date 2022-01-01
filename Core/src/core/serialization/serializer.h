/*
 *  Serialize to various file formats
 *    - binary  (primary)
 *    - text
 */

#pragma once
#include <iostream>
#include <fstream>
#include "../corepch.h"

namespace Firefly {
class Serializer {
public:
    /*
     *  Serializes any struct to a binary file
     */
    template <typename T>
    static void SerializeBin(const std::string& location, T type) {
        std::fstream fs(location, std::ios::out | std::ios::binary);
        if (fs.fail() || !fs.is_open()) {
            LOG_CRITICAL("Failed to open/create file {}", location);
            return;
        }
        
        fs.write(reinterpret_cast<char*>(&type), sizeof(T));
        fs.close();
    }

    /*
     *  Deserializes a bin file based on the type supplied.
     *    - No error checking based on if the right type was supplied.
     */
    template <typename T>
    static T DeSerializeBin(const std::string& location) {
        std::fstream fs(location, std::ios::in | std::ios::binary);
        T type;
        if (fs.fail()) {
            LOG_CRITICAL("Failed to open file {}", location);
        }
        else {
            fs.read(reinterpret_cast<char*>(&type), sizeof(T));
        }
        return type;
    }

    template <typename T>
    static void DeSerializeBin(const std::string& location, T& type) {
        type = DeSerializeBin<T>(location);
    }
};
}

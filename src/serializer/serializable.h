#pragma once
#include <string>
#include "serializer.h"

template <typename T>
struct Serializable {
public:
    virtual void Serialize(const std::string& location) = 0;
    virtual T& Deserialize(const std::string& location) = 0;
};

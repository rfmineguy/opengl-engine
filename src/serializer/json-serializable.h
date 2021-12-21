#pragma once
#include <nlohmann/json.hpp>

using nlohmann::json;

struct JsonSerializable {
public:
    virtual void Serialize(json& jValue) = 0;
    virtual void Deserialize(json& jValue) = 0;
};

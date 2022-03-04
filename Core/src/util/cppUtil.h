#pragma once

#include <type_traits>
namespace Firefly {
    template <typename Base, typename T>
    inline bool instanceOf(const T*) {
        return std::is_base_of_v<Base, T>;
    }
}

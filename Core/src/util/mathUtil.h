#pragma once
#include <random>
#include <typeinfo>

namespace Firefly {
class Random {
public:
    static int RandIntRange(int lower, int upper) {
        static std::random_device rd;
        static std::default_random_engine engine(rd());
        static std::uniform_int_distribution<int> distr(lower, upper);
        return distr(engine);
    }

    static float RandFloatRange(float lower, float upper) {
        static std::random_device rd;
        static std::default_random_engine engine(rd());
        static std::uniform_real_distribution<float> distr(lower, upper);
        return distr(engine);
    }
};

inline float map(float value, float istart, float istop, float ostart, float ostop) {
    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}
}

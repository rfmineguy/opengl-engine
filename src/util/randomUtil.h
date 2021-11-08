#include <random>
#include <typeinfo>

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

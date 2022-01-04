#include <random>

namespace Firefly {
class Random {
public:
    //return a random floating point value between 0 and 1
    static double RandDouble() {
        return RandDoubleRange(0.0, 1.0);
    }

    static double RandDoubleRange(double min, double max) {
        static std::random_device randDevice;
        static std::default_random_engine engine(randDevice());
        static std::uniform_real_distribution<double> distr(min, max);
        return distr(engine);
    }

    //return a random integer between 0 and 1 (effectively 0 or 1)
    static int RandInt() {
        return RandIntRange(0, 1);
    }

    static int RandIntRange(int min, int max) {
        static std::random_device randDevice;
        static std::default_random_engine engine(randDevice());
        static std::uniform_int_distribution<int> distr(min, max);
        return distr(engine);
    }

private:
};
}

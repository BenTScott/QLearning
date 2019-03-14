#define _USE_MATH_DEFINES

#include <cmath>
#include <algorithm>
#include "utilities.h"


double Random::Uniform(double min, double max)
{
    std::uniform_real_distribution<> distribution(min, max);
    return distribution(factory.generator);
}

std::vector<double> Random::Uniform(double min, double max, unsigned count)
{
    std::uniform_real_distribution<> distribution(min, max);
    std::vector<double> v(count);
    std::generate(v.begin(), v.end(), [&]() { return distribution(factory.generator); });
    return v;
};

MerseneTwisterFactory Random::factory = MerseneTwisterFactory();
#ifndef _INCLUDE_UTILITIES_H_
#define _INCLUDE_UTILITIES_H_

#define _USE_MATH_DEFINES

#include <cmath>
#include <random>
#include <ctime>

class MerseneTwisterFactory
{
  public:
    MerseneTwisterFactory()
    {
        seed = 48469438;
        generator = std::mt19937(seed);
    }

    unsigned seed;
    std::mt19937 generator;

  private:
    //std::random_device rd;
};

class Random
{
  public:
    static std::mt19937 &Generator()
    {
        return factory.generator;
    };

    static double Uniform(double min = 0.0, double max = 1.0);

    template <class T = int>
    static T Uniform(T min, T max)
    {
        std::uniform_int_distribution<T> distribution(min, max);
        return distribution(factory.generator);
    };

    std::vector<double> Uniform(double min, double max, unsigned count);

    static unsigned Seed()
    {
        return factory.seed;
    }

  private:
    static MerseneTwisterFactory factory;
};

// Adapted from https://stackoverflow.com/a/6943003
template <typename I>
I RandomElement(I begin, I end)
{
    const unsigned long n = std::distance(begin, end);
    unsigned long k = Random::Uniform<unsigned long>(0, n-1);
    std::advance(begin, k);
    return begin;
};


#endif
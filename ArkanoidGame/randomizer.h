#pragma once

#include <random>

template <bool is_integral, typename T>
struct uniform_distribution_selector;

template <typename T>
struct uniform_distribution_selector<true, T> {
    using type = typename std::uniform_int_distribution<T>;
};

template <typename T>
struct uniform_distribution_selector<false, T> {
    using type = typename std::uniform_real_distribution<T>;
};

template <typename T>
T random(T lower = T(0), T higher = T(99)) {
    if (lower == higher) {
        return lower;
    }
    if (lower > higher) {
        return lower;
    }

    using uniform_distribution_type = typename uniform_distribution_selector<std::is_integral<T>::value, T>::type;

    uniform_distribution_type distribution(lower, higher);
    static std::mt19937 engine;

    return distribution(engine);
}


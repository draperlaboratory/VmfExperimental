#pragma once

// C++ Includes
#include <random>
#include <algorithm>
#include <iostream>

namespace vmf::radamsa::mutations
{
class MutationBase
{
public:
    MutationBase() = delete;
    virtual ~MutationBase() = default;

    MutationBase(const MutationBase&) = delete;
    MutationBase(MutationBase&&) = delete;

    MutationBase& operator=(const MutationBase&) = delete;
    MutationBase& operator=(MutationBase&&) = delete;

protected:
    MutationBase(std::default_random_engine& randomNumberGenerator) : RANDOM_NUMBER_GENERATOR_{randomNumberGenerator} {}

    size_t GetRandomValueWithinBounds(const size_t lower, const size_t upper) noexcept
    {
        std::uniform_int_distribution<size_t> distribution(lower, upper);

        return distribution(RANDOM_NUMBER_GENERATOR_);
    }

    size_t GetRandomByteRepetitionLength() noexcept
    {
        constexpr size_t MINIMUM_UPPER_LIMIT{0x2u};
        constexpr size_t MAXIMUM_UPPER_LIMIT{0x20000u};

        size_t randomStop{GetRandomValueWithinBounds(0u, MINIMUM_UPPER_LIMIT)};
        size_t randomUpperLimit{MINIMUM_UPPER_LIMIT};

        while(randomStop != 0u)
        {
            if(randomUpperLimit == MAXIMUM_UPPER_LIMIT)
                break;

            randomUpperLimit <<= 1u;
            randomStop = GetRandomValueWithinBounds(0u, MINIMUM_UPPER_LIMIT);
        }

        return GetRandomValueWithinBounds(0u, randomUpperLimit) + 1u; // We add one to the return value in order to account for the case where the random upper value is zero.
    }

    std::default_random_engine& RANDOM_NUMBER_GENERATOR_;

private:
};
}
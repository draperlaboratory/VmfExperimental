#pragma once

// C++ Includes
#include <random>
#include <algorithm>
#include <iostream>
#include "VmfRand.hpp"

namespace vmf
{
class MutationBase
{
public:

    static size_t GetRandomByteRepetitionLength(VmfRand& rand) noexcept
    {
        constexpr size_t MINIMUM_UPPER_LIMIT{0x2u};
        constexpr size_t MAXIMUM_UPPER_LIMIT{0x20000u};

        size_t randomStop{rand.randBetween(0u, MINIMUM_UPPER_LIMIT)};
        size_t randomUpperLimit{MINIMUM_UPPER_LIMIT};

        while(randomStop != 0u)
        {
            if(randomUpperLimit == MAXIMUM_UPPER_LIMIT)
                break;

            randomUpperLimit <<= 1u;
            randomStop = rand.randBetween(0u, MINIMUM_UPPER_LIMIT);
        }

        return rand.randBetween(0u, randomUpperLimit) + 1u; // We add one to the return value in order to account for the case where the random upper value is zero.
    }

};
}
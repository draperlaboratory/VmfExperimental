/* =============================================================================
 * Vader Modular Fuzzer
 * Copyright (c) 2021-2024 The Charles Stark Draper Laboratory, Inc.
 * <vmf@draper.com>
 *
 * Effort sponsored by the U.S. Government under Other Transaction number
 * W9124P-19-9-0001 between AMTC and the Government. The U.S. Government
 * is authorized to reproduce and distribute reprints for Governmental purposes
 * notwithstanding any copyright notation thereon.
 *
 * The views and conclusions contained herein are those of the authors and
 * should not be interpreted as necessarily representing the official policies
 * or endorsements, either expressed or implied, of the U.S. Government.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 (only) as 
 * published by the Free Software Foundation.
 *  
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *  
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *  
 * @license GPL-2.0-only <https://spdx.org/licenses/GPL-2.0-only.html>
 * ===========================================================================*/
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

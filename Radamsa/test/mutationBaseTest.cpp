/* =============================================================================
* Vader Modular Fuzzer
* Copyright (c) 2021-2023 The Charles Stark Draper Laboratory, Inc.
* <vader@draper.com>
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
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
* @license GPL-3.0-or-later <https://spdx.org/licenses/GPL-3.0-or-later>
* ===========================================================================*/

// VMF Includes
#include "mutationBaseTest.h"

namespace vader::test::modules::radamsa::mutations
{
TEST_F(MutationBaseTest, TestDefaultConstructor)
{
    ASSERT_EQ(RANDOM_NUMBER_GENERATOR_, std::default_random_engine{});
}

TEST_F(MutationBaseTest, TestGetRandomValueWithinBounds)
{
    constexpr size_t maximumSize{5u};
    constexpr std::array<size_t, maximumSize> lowerValues{0u, 1u, 2u, 3u, 4u};

    // The expected output data was gathered during a previous run using the default random seed.
    // If the random seed is changed, the output data will also change and the unit tests will fail.

    const std::map<std::pair<size_t, size_t>, const std::array<size_t, maximumSize>> expectedOutput{
                                                                                            {{0u, 4u}, {0u, 0u, 3u, 2u, 2u}},
                                                                                            {{1u, 4u}, {1u, 1u, 3u, 3u, 4u}},
                                                                                            {{2u, 4u}, {3u, 3u, 4u, 2u, 2u}},
                                                                                            {{3u, 4u}, {4u, 4u, 3u, 3u, 3u}},
                                                                                            {{4u, 4u}, {4u, 4u, 4u, 4u, 4u}}};

    for (const auto& lower : lowerValues)
    {
        constexpr size_t numberOfRandomDraws{5u};

        for (size_t it{0u}; it < numberOfRandomDraws; ++it)
        {
            constexpr size_t upper{maximumSize - 1u};

            const std::array<size_t, maximumSize>& expectedData{expectedOutput.at(std::make_pair(lower, upper))};

            const size_t randomValue{GetRandomValueWithinBounds(lower, upper)};

            ASSERT_GE(randomValue, lower);
            ASSERT_LE(randomValue, upper);
            ASSERT_EQ(randomValue, expectedData[it]);
        }
    }

    ASSERT_EQ(GetRandomValueWithinBounds(std::numeric_limits<size_t>::min(), std::numeric_limits<size_t>::min()), std::numeric_limits<size_t>::min());
    ASSERT_EQ(GetRandomValueWithinBounds(std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max()), std::numeric_limits<size_t>::max());
}

TEST_F(MutationBaseTest, TestGetRandomByteRepetitionLength)
{
    // The expected output data was gathered during a previous run using the default random seed.
    // If the random seed is changed, the output data will also change and the unit tests will fail.

    constexpr size_t maximumSize{25u};

    const std::array<size_t, maximumSize> expectedOutput{
                                                    1u, 1u, 7u, 4u, 2u,
                                                    43u, 2u, 4u, 17u, 11u,
                                                    3u, 3u, 3u, 9u, 9u, 
                                                    1u, 3u, 5u, 13u, 1u, 
                                                    79u, 54u, 2u, 2u, 3u};

    for (const auto& it : expectedOutput)
    {
        constexpr size_t MINIMUM_LENGTH{0x01};
        constexpr size_t MAXIMUM_LENGTH{0x20000u + MINIMUM_LENGTH};

        const size_t randomValue{GetRandomByteRepetitionLength()};

        ASSERT_GE(randomValue, MINIMUM_LENGTH);
        ASSERT_LE(randomValue, MAXIMUM_LENGTH);
        ASSERT_EQ(randomValue, it);
    }
}
}
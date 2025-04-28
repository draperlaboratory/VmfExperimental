/* =============================================================================
 * Vader Modular Fuzzer (VMF)
 * Copyright (c) 2021-2025 The Charles Stark Draper Laboratory, Inc.
 * <vmf@draper.com>
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

// VMF Includes
#include "byteMutationTest.h"

namespace vmf::test::modules::radamsa::mutations
{
TEST_F(ByteMutationTest, TestDefaultConstructor)
{
    ASSERT_EQ(RANDOM_NUMBER_GENERATOR_, std::default_random_engine{});
}

TEST_F(ByteMutationTest, TestDropByte)
{
    // Test the DropByte() method in the ByteMutation class.
    // The method accepts a character buffer, size, and a minimum seed index.
    // The internal algorithm selects a random byte from the original character buffer,
    // removes it, and copies the contents to a null-terminated character buffer.

    // The expected output data was gathered during a previous run using the default random seed.
    // If the random seed is changed, the output data will also change and the unit tests will fail.

    constexpr size_t expectedSize{inputBufferSize_};

    const std::map<std::pair<size_t, size_t>, const std::array<char, expectedSize>> expectedOutput{
                                                                                            {{0u, 0u}, {0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{0u, 1u}, {0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{0u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{0u, 3u}, {0x01, 0x02, 0x04, 0x05, 0x00}},
                                                                                            {{0u, 4u}, {0x01, 0x02, 0x03, 0x05, 0x00}},
                                                                                            {{0u, 5u}, {0x01, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{0u, 6u}, {0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{0u, 7u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{0u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{0u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x00}},

                                                                                            {{1u, 0u}, {0x01, 0x02, 0x04, 0x05, 0x00}},
                                                                                            {{1u, 1u}, {0x01, 0x02, 0x03, 0x05, 0x00}},
                                                                                            {{1u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{1u, 3u}, {0x01, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{1u, 4u}, {0x01, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{1u, 5u}, {0x01, 0x02, 0x03, 0x05, 0x00}},
                                                                                            {{1u, 6u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{1u, 7u}, {0x01, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{1u, 8u}, {0x01, 0x02, 0x04, 0x05, 0x00}},
                                                                                            {{1u, 9u}, {0x01, 0x03, 0x04, 0x05, 0x00}},

                                                                                            {{2u, 0u}, {0x01, 0x02, 0x03, 0x05, 0x00}},
                                                                                            {{2u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{2u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{2u, 3u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{2u, 4u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{2u, 5u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{2u, 6u}, {0x01, 0x02, 0x04, 0x05, 0x00}},
                                                                                            {{2u, 7u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{2u, 8u}, {0x01, 0x02, 0x03, 0x05, 0x00}},
                                                                                            {{2u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x00}},

                                                                                            {{3u, 0u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{3u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{3u, 2u}, {0x01, 0x02, 0x03, 0x05, 0x00}},
                                                                                            {{3u, 3u}, {0x01, 0x02, 0x03, 0x05, 0x00}},
                                                                                            {{3u, 4u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{3u, 5u}, {0x01, 0x02, 0x03, 0x05, 0x00}},
                                                                                            {{3u, 6u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{3u, 7u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{3u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{3u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x00}},

                                                                                            {{4u, 0u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{4u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{4u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{4u, 3u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{4u, 4u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{4u, 5u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{4u, 6u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{4u, 7u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{4u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x00}},
                                                                                            {{4u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x00}}};

    using namespace std::placeholders;

    RunSubtest(expectedOutput, std::bind(&ByteMutations::DropByte, this, _1, _2, _3, _4, _5));
}

TEST_F(ByteMutationTest, TestFlipByte)
{
    // Test the FlipByte() method in the ByteMutation class.
    // The method accepts a character buffer, size, and a minimum seed index.
    // The internal algorithm selects a random byte from the original character buffer,
    // flips it, and copies the contents to a null-terminated character buffer.


    // The expected output data was gathered during a previous run using the default random seed.
    // If the random seed is changed, the output data will also change and the unit tests will fail.

    constexpr size_t expectedSize_{inputBufferSize_ + 1u};

    const std::map<std::pair<size_t, size_t>, const std::array<char, expectedSize_>> expectedOutput{
                                                                                            {{0u, 0u}, {0x03, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{0u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x15, 0x00}},
                                                                                            {{0u, 2u}, {0x01, 0x02, 0x03, 0x06, 0x05, 0x00}},
                                                                                            {{0u, 3u}, {0x41, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{0u, 4u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{0u, 5u}, {0x01, 0x02, 0x13, 0x04, 0x05, 0x00}},
                                                                                            {{0u, 6u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                            {{0u, 7u}, {0x11, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{0u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                            {{0u, 9u}, {0x01, 0x02, 0x02, 0x04, 0x05, 0x00}},

                                                                                            {{1u, 0u}, {0x01, 0x02, 0x03, 0x44, 0x05, 0x00}},
                                                                                            {{1u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{1u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x15, 0x00}},
                                                                                            {{1u, 3u}, {0x01, 0x22, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{1u, 4u}, {0x01, 0x02, 0x03, 0x44, 0x05, 0x00}},
                                                                                            {{1u, 5u}, {0x01, 0x02, 0x03, 0x04, 0x45, 0x00}},
                                                                                            {{1u, 6u}, {0x01, 0x02, 0x02, 0x04, 0x05, 0x00}},
                                                                                            {{1u, 7u}, {0x01, 0x02, 0x03, 0x04, 0x01, 0x00}},
                                                                                            {{1u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x45, 0x00}},
                                                                                            {{1u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x0d, 0x00}},

                                                                                            {{2u, 0u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{2u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x45, 0x00}},
                                                                                            {{2u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                            {{2u, 3u}, {0x01, 0x02, 0x03, 0x04, -0x7b, 0x00}},
                                                                                            {{2u, 4u}, {0x01, 0x02, 0x03, 0x0c, 0x05, 0x00}},
                                                                                            {{2u, 5u}, {0x01, 0x02, 0x03, 0x04, 0x15, 0x00}},
                                                                                            {{2u, 6u}, {0x01, 0x02, 0x07, 0x04, 0x05, 0x00}},
                                                                                            {{2u, 7u}, {0x01, 0x02, 0x03, 0x06, 0x05, 0x00}},
                                                                                            {{2u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{2u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},

                                                                                            {{3u, 0u}, {0x01, 0x02, 0x03, 0x04, 0x15, 0x00}},
                                                                                            {{3u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x01, 0x00}},
                                                                                            {{3u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x15, 0x00}},
                                                                                            {{3u, 3u}, {0x01, 0x02, 0x03, 0x05, 0x05, 0x00}},
                                                                                            {{3u, 4u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                            {{3u, 5u}, {0x01, 0x02, 0x03, 0x04, 0x0d, 0x00}},
                                                                                            {{3u, 6u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{3u, 7u}, {0x01, 0x02, 0x03, 0x04, 0x15, 0x00}},
                                                                                            {{3u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                            {{3u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x45, 0x00}},

                                                                                            {{4u, 0u}, {0x01, 0x02, 0x03, 0x04, 0x07, 0x00}},
                                                                                            {{4u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x45, 0x00}},
                                                                                            {{4u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x25, 0x00}},
                                                                                            {{4u, 3u}, {0x01, 0x02, 0x03, 0x04, 0x45, 0x00}},
                                                                                            {{4u, 4u}, {0x01, 0x02, 0x03, 0x04, -0x7b, 0x00}},
                                                                                            {{4u, 5u}, {0x01, 0x02, 0x03, 0x04, 0x01, 0x00}},
                                                                                            {{4u, 6u}, {0x01, 0x02, 0x03, 0x04, 0x15, 0x00}},
                                                                                            {{4u, 7u}, {0x01, 0x02, 0x03, 0x04, -0x7b, 0x00}},
                                                                                            {{4u, 8u}, {0x01, 0x02, 0x03, 0x04, -0x7b, 0x00}},
                                                                                            {{4u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x0d, 0x00}}};

    using namespace std::placeholders;

    RunSubtest(expectedOutput, std::bind(&ByteMutations::FlipByte, this, _1, _2, _3, _4, _5));
}

TEST_F(ByteMutationTest, TestInsertByte)
{
    // Test the InsertByte() method in the ByteMutation class.
    // The method accepts a character buffer, size, and a minimum seed index.
    // The internal algorithm selects a random byte from the original character buffer,
    // inserts a random byte after it, and copies the contents to a null-terminated character buffer.

    // The expected output data was gathered during a previous run using the default random seed.
    // If the random seed is changed, the output data will also change and the unit tests will fail.

    constexpr size_t expectedSize{inputBufferSize_ + 2u};

    const std::map<std::pair<size_t, size_t>, const std::array<char, expectedSize>> expectedOutput{
                                                                                            {{0u, 0u}, {0x01, 0x10, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{0u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x3a, 0x00}},
                                                                                            {{0u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x1c, 0x05, 0x00}},
                                                                                            {{0u, 3u}, {0x01, 0x56, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{0u, 4u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x77, 0x00}},
                                                                                            {{0u, 5u}, {0x01, 0x02, 0x03, 0x42, 0x04, 0x05, 0x00}},
                                                                                            {{0u, 6u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x04, 0x00}},
                                                                                            {{0u, 7u}, {0x01, 0x43, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{0u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x00}},
                                                                                            {{0u, 9u}, {0x01, 0x02, 0x03, 0x08, 0x04, 0x05, 0x00}},

                                                                                            {{1u, 0u}, {0x01, 0x02, 0x03, 0x04, 0x57, 0x05, 0x00}},
                                                                                            {{1u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x77, 0x05, 0x00}},
                                                                                            {{1u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x43, 0x00}},
                                                                                            {{1u, 3u}, {0x01, 0x02, 0x53, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{1u, 4u}, {0x01, 0x02, 0x03, 0x04, 0x59, 0x05, 0x00}},
                                                                                            {{1u, 5u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x61, 0x00}},
                                                                                            {{1u, 6u}, {0x01, 0x02, 0x03, 0x06, 0x04, 0x05, 0x00}},
                                                                                            {{1u, 7u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x2a, 0x00}},
                                                                                            {{1u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x60, 0x00}},
                                                                                            {{1u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x2e, 0x00}},

                                                                                            {{2u, 0u}, {0x01, 0x02, 0x03, 0x7d, 0x04, 0x05, 0x00}},
                                                                                            {{2u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x60, 0x00}},
                                                                                            {{2u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x09, 0x00}},
                                                                                            {{2u, 3u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x71, 0x00}},
                                                                                            {{2u, 4u}, {0x01, 0x02, 0x03, 0x04, 0x37, 0x05, 0x00}},
                                                                                            {{2u, 5u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x3d, 0x00}},
                                                                                            {{2u, 6u}, {0x01, 0x02, 0x03, 0x23, 0x04, 0x05, 0x00}},
                                                                                            {{2u, 7u}, {0x01, 0x02, 0x03, 0x04, 0x15, 0x05, 0x00}},
                                                                                            {{2u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x72, 0x05, 0x00}},
                                                                                            {{2u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x07, 0x00}},

                                                                                            {{3u, 0u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x40, 0x00}},
                                                                                            {{3u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x28, 0x00}},
                                                                                            {{3u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x3f, 0x00}},
                                                                                            {{3u, 3u}, {0x01, 0x02, 0x03, 0x04, 0x0b, 0x05, 0x00}},
                                                                                            {{3u, 4u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x09, 0x00}},
                                                                                            {{3u, 5u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x31, 0x00}},
                                                                                            {{3u, 6u}, {0x01, 0x02, 0x03, 0x04, 0x74, 0x05, 0x00}},
                                                                                            {{3u, 7u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x3b, 0x00}},
                                                                                            {{3u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x00}},
                                                                                            {{3u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x62, 0x00}},

                                                                                            {{4u, 0u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x10, 0x00}},
                                                                                            {{4u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x58, 0x00}},
                                                                                            {{4u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x50, 0x00}},
                                                                                            {{4u, 3u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x5c, 0x00}},
                                                                                            {{4u, 4u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x71, 0x00}},
                                                                                            {{4u, 5u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x27, 0x00}},
                                                                                            {{4u, 6u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x41, 0x00}},
                                                                                            {{4u, 7u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x6c, 0x00}},
                                                                                            {{4u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x6b, 0x00}},
                                                                                            {{4u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x35, 0x00}}};

    using namespace std::placeholders;

    RunSubtest(expectedOutput, std::bind(&ByteMutations::InsertByte, this, _1, _2, _3, _4, _5));
}

TEST_F(ByteMutationTest, TestIncrementByte)
{
    // Test the IncrementByte() method in the ByteMutation class.
    // The method accepts a character buffer, size, and a minimum seed index.
    // The internal algorithm selects a random byte from the original character buffer,
    // increments it circularly, and copies the contents to a null-terminated character buffer.

    // The expected output data was gathered during a previous run using the default random seed.
    // If the random seed is changed, the output data will also change and the unit tests will fail.

    constexpr size_t expectedSize{inputBufferSize_ + 1u};

    const std::map<std::pair<size_t, size_t>, const std::array<char, expectedSize>> expectedOutput{
                                                                                            {{0u, 0u}, {0x02, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{0u, 1u}, {0x02, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{0u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{0u, 3u}, {0x01, 0x02, 0x04, 0x04, 0x05, 0x00}},
                                                                                            {{0u, 4u}, {0x01, 0x02, 0x03, 0x05, 0x05, 0x00}},
                                                                                            {{0u, 5u}, {0x01, 0x03, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{0u, 6u}, {0x02, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{0u, 7u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{0u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{0u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},

                                                                                            {{1u, 0u}, {0x01, 0x02, 0x04, 0x04, 0x05, 0x00}},
                                                                                            {{1u, 1u}, {0x01, 0x02, 0x03, 0x05, 0x05, 0x00}},
                                                                                            {{1u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{1u, 3u}, {0x01, 0x03, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{1u, 4u}, {0x01, 0x03, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{1u, 5u}, {0x01, 0x02, 0x03, 0x05, 0x05, 0x00}},
                                                                                            {{1u, 6u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{1u, 7u}, {0x01, 0x03, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{1u, 8u}, {0x01, 0x02, 0x04, 0x04, 0x05, 0x00}},
                                                                                            {{1u, 9u}, {0x01, 0x03, 0x03, 0x04, 0x05, 0x00}},

                                                                                            {{2u, 0u}, {0x01, 0x02, 0x03, 0x05, 0x05, 0x00}},
                                                                                            {{2u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{2u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{2u, 3u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{2u, 4u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{2u, 5u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{2u, 6u}, {0x01, 0x02, 0x04, 0x04, 0x05, 0x00}},
                                                                                            {{2u, 7u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{2u, 8u}, {0x01, 0x02, 0x03, 0x05, 0x05, 0x00}},
                                                                                            {{2u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},

                                                                                            {{3u, 0u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{3u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{3u, 2u}, {0x01, 0x02, 0x03, 0x05, 0x05, 0x00}},
                                                                                            {{3u, 3u}, {0x01, 0x02, 0x03, 0x05, 0x05, 0x00}},
                                                                                            {{3u, 4u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{3u, 5u}, {0x01, 0x02, 0x03, 0x05, 0x05, 0x00}},
                                                                                            {{3u, 6u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{3u, 7u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{3u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{3u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},

                                                                                            {{4u, 0u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{4u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{4u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{4u, 3u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{4u, 4u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{4u, 5u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{4u, 6u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{4u, 7u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{4u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                            {{4u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}}};

    using namespace std::placeholders;

    RunSubtest(expectedOutput, std::bind(&ByteMutations::IncrementByte, this, _1, _2, _3, _4, _5));
}

TEST_F(ByteMutationTest, TestDecrementByte)
{
    // Test the DecrementByte() method in the ByteMutation class.
    // The method accepts a character buffer, size, and a minimum seed index.
    // The internal algorithm selects a random byte from the original character buffer,
    // decrements it circularly, and copies the contents to a null-terminated character buffer.

        // The expected output data was gathered during a previous run using the default random seed.
        // If the random seed is changed, the output data will also change and the unit tests will fail.

        constexpr size_t expectedSize{inputBufferSize_ + 1u};

        const std::map<std::pair<size_t, size_t>, const std::array<char, expectedSize>> expectedOutput{
                                                                                                {{0u, 0u}, {0x00, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                                {{0u, 1u}, {0x00, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                                {{0u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{0u, 3u}, {0x01, 0x02, 0x02, 0x04, 0x05, 0x00}},
                                                                                                {{0u, 4u}, {0x01, 0x02, 0x03, 0x03, 0x05, 0x00}},
                                                                                                {{0u, 5u}, {0x01, 0x01, 0x03, 0x04, 0x05, 0x00}},
                                                                                                {{0u, 6u}, {0x00, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                                {{0u, 7u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{0u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{0u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},

                                                                                                {{1u, 0u}, {0x01, 0x02, 0x02, 0x04, 0x05, 0x00}},
                                                                                                {{1u, 1u}, {0x01, 0x02, 0x03, 0x03, 0x05, 0x00}},
                                                                                                {{1u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{1u, 3u}, {0x01, 0x01, 0x03, 0x04, 0x05, 0x00}},
                                                                                                {{1u, 4u}, {0x01, 0x01, 0x03, 0x04, 0x05, 0x00}},
                                                                                                {{1u, 5u}, {0x01, 0x02, 0x03, 0x03, 0x05, 0x00}},
                                                                                                {{1u, 6u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{1u, 7u}, {0x01, 0x01, 0x03, 0x04, 0x05, 0x00}},
                                                                                                {{1u, 8u}, {0x01, 0x02, 0x02, 0x04, 0x05, 0x00}},
                                                                                                {{1u, 9u}, {0x01, 0x01, 0x03, 0x04, 0x05, 0x00}},

                                                                                                {{2u, 0u}, {0x01, 0x02, 0x03, 0x03, 0x05, 0x00}},
                                                                                                {{2u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{2u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{2u, 3u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{2u, 4u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{2u, 5u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{2u, 6u}, {0x01, 0x02, 0x02, 0x04, 0x05, 0x00}},
                                                                                                {{2u, 7u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{2u, 8u}, {0x01, 0x02, 0x03, 0x03, 0x05, 0x00}},
                                                                                                {{2u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},

                                                                                                {{3u, 0u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{3u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{3u, 2u}, {0x01, 0x02, 0x03, 0x03, 0x05, 0x00}},
                                                                                                {{3u, 3u}, {0x01, 0x02, 0x03, 0x03, 0x05, 0x00}},
                                                                                                {{3u, 4u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{3u, 5u}, {0x01, 0x02, 0x03, 0x03, 0x05, 0x00}},
                                                                                                {{3u, 6u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{3u, 7u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{3u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{3u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},

                                                                                                {{4u, 0u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{4u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{4u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{4u, 3u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{4u, 4u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{4u, 5u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{4u, 6u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{4u, 7u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{4u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{4u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}}};

    using namespace std::placeholders;

    RunSubtest(expectedOutput, std::bind(&ByteMutations::DecrementByte, this, _1, _2, _3, _4, _5));
}

TEST_F(ByteMutationTest, TestRandomizeByte)
{
    // Test the RandomizeByte() method in the ByteMutation class.
    // The method accepts a character buffer, size, and a minimum seed index.
    // The internal algorithm selects a random byte from the original character buffer,
    // randomizes it, and copies the contents to a null-terminated character buffer.

        // The expected output data was gathered during a previous run using the default random seed.
        // If the random seed is changed, the output data will also change and the unit tests will fail.

        constexpr size_t expectedSize{inputBufferSize_ + 1u};

        const std::map<std::pair<size_t, size_t>, const std::array<char, expectedSize>> expectedOutput{
                                                                                                {{0u, 0u}, {0x10, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                                {{0u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x3a, 0x00}},
                                                                                                {{0u, 2u}, {0x01, 0x02, 0x03, 0x1c, 0x05, 0x00}},
                                                                                                {{0u, 3u}, {0x56, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                                {{0u, 4u}, {0x01, 0x02, 0x03, 0x04, 0x77, 0x00}},
                                                                                                {{0u, 5u}, {0x01, 0x02, 0x42, 0x04, 0x05, 0x00}},
                                                                                                {{0u, 6u}, {0x01, 0x02, 0x03, 0x04, 0x04, 0x00}},
                                                                                                {{0u, 7u}, {0x43, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                                {{0u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x00, 0x00}},
                                                                                                {{0u, 9u}, {0x01, 0x02, 0x08, 0x04, 0x05, 0x00}},

                                                                                                {{1u, 0u}, {0x01, 0x02, 0x03, 0x57, 0x05, 0x00}},
                                                                                                {{1u, 1u}, {0x01, 0x02, 0x03, 0x77, 0x05, 0x00}},
                                                                                                {{1u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x43, 0x00}},
                                                                                                {{1u, 3u}, {0x01, 0x53, 0x03, 0x04, 0x05, 0x00}},
                                                                                                {{1u, 4u}, {0x01, 0x02, 0x03, 0x59, 0x05, 0x00}},
                                                                                                {{1u, 5u}, {0x01, 0x02, 0x03, 0x04, 0x61, 0x00}},
                                                                                                {{1u, 6u}, {0x01, 0x02, 0x06, 0x04, 0x05, 0x00}},
                                                                                                {{1u, 7u}, {0x01, 0x02, 0x03, 0x04, 0x2a, 0x00}},
                                                                                                {{1u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x60, 0x00}},
                                                                                                {{1u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x2e, 0x00}},

                                                                                                {{2u, 0u}, {0x01, 0x02, 0x7d, 0x04, 0x05, 0x00}},
                                                                                                {{2u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x60, 0x00}},
                                                                                                {{2u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x09, 0x00}},
                                                                                                {{2u, 3u}, {0x01, 0x02, 0x03, 0x04, 0x71, 0x00}},
                                                                                                {{2u, 4u}, {0x01, 0x02, 0x03, 0x37, 0x05, 0x00}},
                                                                                                {{2u, 5u}, {0x01, 0x02, 0x03, 0x04, 0x3d, 0x00}},
                                                                                                {{2u, 6u}, {0x01, 0x02, 0x23, 0x04, 0x05, 0x00}},
                                                                                                {{2u, 7u}, {0x01, 0x02, 0x03, 0x15, 0x05, 0x00}},
                                                                                                {{2u, 8u}, {0x01, 0x02, 0x03, 0x72, 0x05, 0x00}},
                                                                                                {{2u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x07, 0x00}},

                                                                                                {{3u, 0u}, {0x01, 0x02, 0x03, 0x04, 0x40, 0x00}},
                                                                                                {{3u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x28, 0x00}},
                                                                                                {{3u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x3f, 0x00}},
                                                                                                {{3u, 3u}, {0x01, 0x02, 0x03, 0x0b, 0x05, 0x00}},
                                                                                                {{3u, 4u}, {0x01, 0x02, 0x03, 0x04, 0x09, 0x00}},
                                                                                                {{3u, 5u}, {0x01, 0x02, 0x03, 0x04, 0x31, 0x00}},
                                                                                                {{3u, 6u}, {0x01, 0x02, 0x03, 0x74, 0x05, 0x00}},
                                                                                                {{3u, 7u}, {0x01, 0x02, 0x03, 0x04, 0x3b, 0x00}},
                                                                                                {{3u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x06, 0x00}},
                                                                                                {{3u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x62, 0x00}},

                                                                                                {{4u, 0u}, {0x01, 0x02, 0x03, 0x04, 0x10, 0x00}},
                                                                                                {{4u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x58, 0x00}},
                                                                                                {{4u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x50, 0x00}},
                                                                                                {{4u, 3u}, {0x01, 0x02, 0x03, 0x04, 0x5c, 0x00}},
                                                                                                {{4u, 4u}, {0x01, 0x02, 0x03, 0x04, 0x71, 0x00}},
                                                                                                {{4u, 5u}, {0x01, 0x02, 0x03, 0x04, 0x27, 0x00}},
                                                                                                {{4u, 6u}, {0x01, 0x02, 0x03, 0x04, 0x41, 0x00}},
                                                                                                {{4u, 7u}, {0x01, 0x02, 0x03, 0x04, 0x6c, 0x00}},
                                                                                                {{4u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x6b, 0x00}},
                                                                                                {{4u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x35, 0x00}}};

    using namespace std::placeholders;

    RunSubtest(expectedOutput, std::bind(&ByteMutations::RandomizeByte, this, _1, _2, _3, _4, _5));
}

TEST_F(ByteMutationTest, TestRepeatByte)
{
    // Test the RepeatByte() method in the ByteMutation class.
    // The method accepts a character buffer, size, and a minimum seed index.
    // The internal algorithm selects a random byte from the original character buffer,
    // repeats it a random number of times, and copies the contents to a null-terminated character buffer.

    try
    {
        using namespace std::placeholders;

        Byte_Mutation_Callback callback{std::bind(&ByteMutations::RepeatByte, this, _1, _2, _3, _4, _5)};

        // Execute the callback 10 times per valid minimum seed index.

        constexpr size_t inputBufferSize{5u};

        constexpr std::array<size_t, inputBufferSize> minimumSeedIndices{0u, 1u, 2u, 3u, 4u};
        constexpr std::array<char, inputBufferSize> inputBuffer{0x01u, 0x02u, 0x03u, 0x04u, 0x05u};

        // The expected output data was gathered during a previous run using the default random seed.
        // If the random seed is changed, the output data will also change and the unit tests will fail.

        std::map<std::pair<size_t, size_t>, std::tuple<size_t, size_t, size_t>> expectedOutput{
                                                                                {{0u, 0u}, {0x05, 0x02, inputBufferSize + 0x02}},
                                                                                {{0u, 1u}, {0x05, 0x02, inputBufferSize + 0x02}},
                                                                                {{0u, 2u}, {0x04, 0x05, inputBufferSize + 0x05}},
                                                                                {{0u, 3u}, {0x01, 0x03, inputBufferSize + 0x03}},
                                                                                {{0u, 4u}, {0x03, 0x56, inputBufferSize + 0x56}},
                                                                                {{0u, 5u}, {0x05, 0x02, inputBufferSize + 0x02}},
                                                                                {{0u, 6u}, {0x05, 0x03, inputBufferSize + 0x03}},
                                                                                {{0u, 7u}, {0x05, 0x0a, inputBufferSize + 0x0a}},
                                                                                {{0u, 8u}, {0x05, 0x07, inputBufferSize + 0x07}},
                                                                                {{0u, 9u}, {0x05, 0x03, inputBufferSize + 0x03}},

                                                                                {{1u, 0u}, {0x03, 0x03, inputBufferSize + 0x03}},
                                                                                {{1u, 1u}, {0x05, 0x03, inputBufferSize + 0x03}},
                                                                                {{1u, 2u}, {0x04, 0x06, inputBufferSize + 0x06}},
                                                                                {{1u, 3u}, {0x04, 0x06, inputBufferSize + 0x06}},
                                                                                {{1u, 4u}, {0x05, 0x02, inputBufferSize + 0x02}},
                                                                                {{1u, 5u}, {0x03, 0x03, inputBufferSize + 0x03}},
                                                                                {{1u, 6u}, {0x04, 0x04, inputBufferSize + 0x04}},
                                                                                {{1u, 7u}, {0x05, 0x08, inputBufferSize + 0x08}},
                                                                                {{1u, 8u}, {0x05, 0x02, inputBufferSize + 0x02}},
                                                                                {{1u, 9u}, {0x03, 0x29, inputBufferSize + 0x29}},

                                                                                {{2u, 0u}, {0x05, 0x1d, inputBufferSize + 0x1d}},
                                                                                {{2u, 1u}, {0x03, 0x02, inputBufferSize + 0x02}},
                                                                                {{2u, 2u}, {0x04, 0x06, inputBufferSize + 0x06}},
                                                                                {{2u, 3u}, {0x05, 0x1d, inputBufferSize + 0x1d}},
                                                                                {{2u, 4u}, {0x04, 0x02, inputBufferSize + 0x02}},
                                                                                {{2u, 5u}, {0x03, 0x03, inputBufferSize + 0x03}},
                                                                                {{2u, 6u}, {0x04, 0x03, inputBufferSize + 0x03}},
                                                                                {{2u, 7u}, {0x04, 0x08, inputBufferSize + 0x08}},
                                                                                {{2u, 8u}, {0x05, 0x07, inputBufferSize + 0x07}},
                                                                                {{2u, 9u}, {0x04, 0x12, inputBufferSize + 0x12}},

                                                                                {{3u, 0u}, {0x04, 0x03, inputBufferSize + 0x03}},
                                                                                {{3u, 1u}, {0x04, 0x05, inputBufferSize + 0x05}},
                                                                                {{3u, 2u}, {0x05, 0x05, inputBufferSize + 0x05}},
                                                                                {{3u, 3u}, {0x05, 0x04, inputBufferSize + 0x04}},
                                                                                {{3u, 4u}, {0x05, 0x02, inputBufferSize + 0x02}},
                                                                                {{3u, 5u}, {0x05, 0x06, inputBufferSize + 0x06}},
                                                                                {{3u, 6u}, {0x04, 0x04, inputBufferSize + 0x04}},
                                                                                {{3u, 7u}, {0x05, 0x02, inputBufferSize + 0x02}},
                                                                                {{3u, 8u}, {0x05, 0x02, inputBufferSize + 0x02}},
                                                                                {{3u, 9u}, {0x05, 0x59, inputBufferSize + 0x59}},

                                                                                {{4u, 0u}, {0x05, 0x0004, inputBufferSize + 0x0004}},
                                                                                {{4u, 1u}, {0x05, 0x44cd, inputBufferSize + 0x44cd}},
                                                                                {{4u, 2u}, {0x05, 0x0003, inputBufferSize + 0x0003}},
                                                                                {{4u, 3u}, {0x05, 0x01c8, inputBufferSize + 0x01c8}},
                                                                                {{4u, 4u}, {0x05, 0x0005, inputBufferSize + 0x0005}},
                                                                                {{4u, 5u}, {0x05, 0x000a, inputBufferSize + 0x000a}},
                                                                                {{4u, 6u}, {0x05, 0x0006, inputBufferSize + 0x0006}},
                                                                                {{4u, 7u}, {0x05, 0x0003, inputBufferSize + 0x0003}},
                                                                                {{4u, 8u}, {0x05, 0x0082, inputBufferSize + 0x0082}},
                                                                                {{4u, 9u}, {0x05, 0x0002, inputBufferSize + 0x0002}}};

        for (const auto& minimumSeedIndex : minimumSeedIndices)
        {
            constexpr size_t numberOfRandomDraws{10u};

            for (size_t it{0u}; it < numberOfRandomDraws; ++it)
            {
                std::tuple<int, std::unique_ptr<SimpleStorage>, unsigned long> testCaseStorageTuple{
                                                                                                RunByteMutationCallback(
                                                                                                                inputBuffer.data(),
                                                                                                                inputBuffer.size(),
                                                                                                                minimumSeedIndex,
                                                                                                                callback)};

                const int testCaseKey{std::get<0u>(testCaseStorageTuple)};
                const unsigned long entryId{std::get<2u>(testCaseStorageTuple)};
                StorageEntry* storageEntryPtr{std::get<1u>(testCaseStorageTuple)->getEntryByID(entryId)};

                const int outputBufferSize{storageEntryPtr->getBufferSize(testCaseKey)};
                const char* const outputBuffer{storageEntryPtr->getBufferPointer(testCaseKey)};

                const std::tuple<size_t, size_t, size_t>& expectedData{expectedOutput[std::make_pair(minimumSeedIndex, it)]};

                const size_t expectedByteValue{std::get<0u>(expectedData)};
                const size_t numberOfExpectedByteRepetitions{std::get<1u>(expectedData)};
                const size_t expectedSize{std::get<2u>(expectedData)};

                const char* const byteRepetitionIndex{std::adjacent_find(outputBuffer, outputBuffer + outputBufferSize)};
                const std::ptrdiff_t numberOfByteRepetitions{std::count(byteRepetitionIndex, outputBuffer + outputBufferSize, *byteRepetitionIndex)};

                ASSERT_EQ(outputBufferSize, expectedSize);
                EXPECT_EQ(outputBuffer[outputBufferSize - 1u], 0u);
                EXPECT_EQ(expectedByteValue, *byteRepetitionIndex);
                EXPECT_EQ(numberOfExpectedByteRepetitions, numberOfByteRepetitions);
            }
        }

        {
            // Execute callback with an invalid minimum seed index.

            EXPECT_THROW(
                    RunByteMutationCallback(
                                    inputBuffer.data(),
                                    inputBuffer.size(),
                                    inputBuffer.size(), // This minimum seed index is invalid
                                    callback),
                    RuntimeException);
        }

        {
            // Execute callback with an invalid buffer size.

            constexpr int minimumSeedIndex{0u};

            EXPECT_THROW(
                    RunByteMutationCallback(
                                    inputBuffer.data(),
                                    0u, // This size is invalid
                                    minimumSeedIndex,
                                    callback),
                    RuntimeException);
        }

        {
            // Execute callback with an invalid buffer.

            constexpr int minimumSeedIndex{0u};

            EXPECT_THROW(
                    RunByteMutationCallback(
                                    nullptr, // This pointer is invalid
                                    inputBuffer.size(),
                                    minimumSeedIndex,
                                    callback),
                    RuntimeException);
        }
    }
    catch(...)
    {
        GTEST_DECORATOR << "Unknown Error occurred" << std::endl;

        EXPECT_TRUE(false);
    }
}

TEST_F(ByteMutationTest, TestPermuteByte)
{
    // Test the PermuteByte() method in the ByteMutation class.
    // The method accepts a character buffer, size, and a minimum seed index.
    // The internal algorithm randomizes bytes from the original character buffer
    // and copies the contents to a null-terminated character buffer.

    // The expected output data was gathered during a previous run using the default random seed.
    // If the random seed is changed, the output data will also change and the unit tests will fail.

    constexpr size_t expectedSize{inputBufferSize_ + 1u};

    const std::map<std::pair<size_t, size_t>, const std::array<char, expectedSize>> expectedOutput{
                                                                                            {{0u, 0u}, {0x02, 0x01, 0x04, 0x03, 0x05, 0x00}},
                                                                                            {{0u, 1u}, {0x01, 0x02, 0x05, 0x03, 0x04, 0x00}},
                                                                                            {{0u, 2u}, {0x01, 0x04, 0x05, 0x03, 0x02, 0x00}},
                                                                                            {{0u, 3u}, {0x02, 0x05, 0x01, 0x04, 0x03, 0x00}},
                                                                                            {{0u, 4u}, {0x03, 0x05, 0x04, 0x02, 0x01, 0x00}},
                                                                                            {{0u, 5u}, {0x02, 0x04, 0x03, 0x01, 0x05, 0x00}},
                                                                                            {{0u, 6u}, {0x04, 0x03, 0x01, 0x05, 0x02, 0x00}},
                                                                                            {{0u, 7u}, {0x02, 0x04, 0x01, 0x03, 0x05, 0x00}},
                                                                                            {{0u, 8u}, {0x02, 0x05, 0x01, 0x04, 0x03, 0x00}},
                                                                                            {{0u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x00}},

                                                                                            {{1u, 0u}, {0x01, 0x05, 0x02, 0x04, 0x03, 0x00}},
                                                                                            {{1u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{1u, 2u}, {0x01, 0x03, 0x05, 0x04, 0x02, 0x00}},
                                                                                            {{1u, 3u}, {0x01, 0x04, 0x03, 0x02, 0x05, 0x00}},
                                                                                            {{1u, 4u}, {0x01, 0x04, 0x03, 0x05, 0x02, 0x00}},
                                                                                            {{1u, 5u}, {0x01, 0x04, 0x02, 0x03, 0x05, 0x00}},
                                                                                            {{1u, 6u}, {0x01, 0x03, 0x02, 0x05, 0x04, 0x00}},
                                                                                            {{1u, 7u}, {0x01, 0x04, 0x02, 0x03, 0x05, 0x00}},
                                                                                            {{1u, 8u}, {0x01, 0x02, 0x05, 0x03, 0x04, 0x00}},
                                                                                            {{1u, 9u}, {0x01, 0x05, 0x02, 0x03, 0x04, 0x00}},

                                                                                            {{2u, 0u}, {0x01, 0x02, 0x03, 0x05, 0x04, 0x00}},
                                                                                            {{2u, 1u}, {0x01, 0x02, 0x05, 0x03, 0x04, 0x00}},
                                                                                            {{2u, 2u}, {0x01, 0x02, 0x04, 0x03, 0x05, 0x00}},
                                                                                            {{2u, 3u}, {0x01, 0x02, 0x04, 0x03, 0x05, 0x00}},
                                                                                            {{2u, 4u}, {0x01, 0x02, 0x05, 0x04, 0x03, 0x00}},
                                                                                            {{2u, 5u}, {0x01, 0x02, 0x04, 0x03, 0x05, 0x00}},
                                                                                            {{2u, 6u}, {0x01, 0x02, 0x05, 0x04, 0x03, 0x00}},
                                                                                            {{2u, 7u}, {0x01, 0x02, 0x05, 0x03, 0x04, 0x00}},
                                                                                            {{2u, 8u}, {0x01, 0x02, 0x04, 0x03, 0x05, 0x00}},
                                                                                            {{2u, 9u}, {0x01, 0x02, 0x04, 0x05, 0x03, 0x00}},

                                                                                            {{3u, 0u}, {0x01, 0x02, 0x03, 0x05, 0x04, 0x00}},
                                                                                            {{3u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{3u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{3u, 3u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{3u, 4u}, {0x01, 0x02, 0x03, 0x05, 0x04, 0x00}},
                                                                                            {{3u, 5u}, {0x01, 0x02, 0x03, 0x05, 0x04, 0x00}},
                                                                                            {{3u, 6u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{3u, 7u}, {0x01, 0x02, 0x03, 0x05, 0x04, 0x00}},
                                                                                            {{3u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{3u, 9u}, {0x01, 0x02, 0x03, 0x05, 0x04, 0x00}},

                                                                                            {{4u, 0u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{4u, 1u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{4u, 2u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{4u, 3u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{4u, 4u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{4u, 5u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{4u, 6u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{4u, 7u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{4u, 8u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x00}},
                                                                                            {{4u, 9u}, {0x01, 0x02, 0x03, 0x04, 0x05, 0x00}}};

    using namespace std::placeholders;

    RunSubtest(expectedOutput, std::bind(&ByteMutations::PermuteByte, this, _1, _2, _3, _4, _5));
}
}

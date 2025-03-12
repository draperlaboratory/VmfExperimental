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

// VMF Includes
#include "lineMutationTest.h"

namespace vmf::test::modules::radamsa::mutations
{
TEST_F(LineMutationTest, TestDefaultConstructor)
{
    ASSERT_EQ(RANDOM_NUMBER_GENERATOR_, std::default_random_engine{});
}

TEST_F(LineMutationTest, TestGetNumberOfLinesAfterIndex)
{
    // Test the GetNumberOfLinesAfterIndex() method in the LineMutations class.
    // The method accepts a character buffer, size, and a character index.
    // The total number of lines in the character buffer should be returned.

    const std::map<size_t, size_t> expectedOutput{
                                            {0u, 5u}, {1u, 5u},
                                            {2u, 5u}, {3u, 5u},
                                            {4u, 5u}, {5u, 5u},
                                            
                                            {6u, 4u}, {7u, 4u},
                                            {8u, 4u}, {9u, 4u},
                                            {10u, 4u}, {11u, 4u},

                                            {12u, 3u}, {13u, 3u},
                                            {14u, 3u}, {15u, 3u},
                                            {16u, 3u}, {17u, 3u},

                                            {18u, 2u}, {19u, 2u},
                                            {20u, 2u}, {21u, 2u},
                                            {22u, 2u}, {23u, 2u},

                                            {24u, 1u}, {25u, 1u},
                                            {26u, 1u}, {27u, 1u},
                                            {28u, 1u}, {29u, 1u},
                                            {30u, 1u}};

    {
        // Valid Input - This subtest should count the number of lines in the buffer and execute successfuly.

        for (const auto& it : expectedOutput)
        {
            const size_t index{it.first};
            const size_t expectedNumberOfLines{it.second};
            
            ASSERT_EQ(GetNumberOfLinesAfterIndex(asciiInputBuffer_, sizeof(asciiInputBuffer_), index), expectedNumberOfLines);
        }
    }

    {
        // Valid Input - This subtest should count the number of lines in the null buffer of size 1 and execute successfuly.

        constexpr char validBuffer[]{'\0'};
        constexpr int validBufferSize{sizeof(validBuffer)};
        constexpr int validIndex{0};
        constexpr int expectedNumberOfLines{1};

        ASSERT_EQ(GetNumberOfLinesAfterIndex(validBuffer, validBufferSize, validIndex), expectedNumberOfLines);
    }

    {
        // Valid Input - This subtest should count the number of lines in the null buffer of size 2 and execute successfuly.

        constexpr char validBuffer[]{"\0"};
        constexpr int validBufferSize{sizeof(validBuffer)};
        constexpr int validIndex{1};
        constexpr int expectedNumberOfLines{1};

        ASSERT_EQ(GetNumberOfLinesAfterIndex(validBuffer, validBufferSize, validIndex), expectedNumberOfLines);
    }

    {
        // Valid Input - This subtest should count the number of lines in the newline buffer of size 1 and execute successfuly.

        constexpr char validBuffer[]{'\n'};
        constexpr int validBufferSize{sizeof(validBuffer)};
        constexpr int validIndex{0u};
        constexpr int expectedNumberOfLines{2};

        ASSERT_EQ(GetNumberOfLinesAfterIndex(validBuffer, validBufferSize, validIndex), expectedNumberOfLines);
    }

    {
        // Valid Input - This subtest should count the number of lines in the newline buffer of size 2 and execute successfuly.

        constexpr char validBuffer[]{"\n"};
        constexpr int validBufferSize{sizeof(validBuffer)};
        constexpr int validIndex{0u};
        constexpr int expectedNumberOfLines{2};

        ASSERT_EQ(GetNumberOfLinesAfterIndex(validBuffer, validBufferSize, validIndex), expectedNumberOfLines);
    }

    {
        // Valid Input - This subtest should count the number of lines in the buffer and execute successfuly.

        constexpr char validBuffer[]{"line1\nline2\0\nline3"};
        constexpr int validBufferSize{sizeof(validBuffer)};
        constexpr int validIndex{0u};
        constexpr int expectedNumberOfLines{3};

        ASSERT_EQ(GetNumberOfLinesAfterIndex(validBuffer, validBufferSize, validIndex), expectedNumberOfLines);
    }

    {
        // Valid Input - This subtest should count the number of lines in the buffer, but ignore all newlines after the null terminator.

        constexpr char validBuffer[]{"line1\nline2\0\nline3"};
        const int validBufferSize{static_cast<int>(strlen(validBuffer))};
        constexpr int validIndex{0u};
        constexpr int expectedNumberOfLines{2};

        ASSERT_EQ(GetNumberOfLinesAfterIndex(validBuffer, validBufferSize, validIndex), expectedNumberOfLines);
    }

    {
        // Erroneous Input - This subtest should trigger a runtime exception since the buffer size is 0.

        constexpr int invalidBufferSize{0};
        constexpr int validIndex{0};

        EXPECT_THROW(GetNumberOfLinesAfterIndex(asciiInputBuffer_, invalidBufferSize, validIndex), RuntimeException);
    }
    
    {
        // Erroneous Input - This subtest should trigger a runtime exception since the index is greater than the buffer size.

        constexpr int validBufferSize{sizeof(asciiInputBuffer_)};
        constexpr int invalidIndex{sizeof(asciiInputBuffer_)};

        EXPECT_THROW(GetNumberOfLinesAfterIndex(asciiInputBuffer_, validBufferSize, invalidIndex), RuntimeException);
    }

    {
        // Erroneous Input - This subtest should trigger a runtime exception since the buffer is null.

        constexpr int validBufferSize{sizeof(asciiInputBuffer_)};
        constexpr int validIndex{0u};

        EXPECT_THROW(GetNumberOfLinesAfterIndex(nullptr, validBufferSize, validIndex), RuntimeException);
    }
}

TEST_F(LineMutationTest, TestGetLineData)
{
    // Test the GetLineData() method in the LineMutations class.
    // The method accepts a character buffer, size, line index, and number of lines after index.
    // A structure containing information about the line in the character buffer should be returned.

    typedef size_t character_index, line_index;

    auto runGetNumberOfLinesAfterIndexMethod{
                                        [&](const std::map<std::pair<character_index, line_index>, Line>& expectedOutputData)
                                        {
                                            for (const auto& it : expectedOutputData)
                                            {
                                                const character_index characterIndex{it.first.first};
                                                const line_index lineIndex{it.first.second};

                                                const size_t numberOfLinesAfterIndex{
                                                                                GetNumberOfLinesAfterIndex(
                                                                                                    asciiInputBuffer_,
                                                                                                    sizeof(asciiInputBuffer_),
                                                                                                    characterIndex)};

                                                ASSERT_EQ(
                                                    it.second,
                                                    GetLineData(
                                                            asciiInputBuffer_,
                                                            sizeof(asciiInputBuffer_),
                                                            lineIndex,
                                                            numberOfLinesAfterIndex));
                                            }}};

    {
        // Valid Input - This subtest should return the line data information associated with the buffer and execute successfuly.
        //               The character indices and line indices are within the expected bounds.

        const std::map<std::pair<character_index, line_index>, Line> expectedOutput{
                                                                            {{0u, 0u}, Line{true, 0u, 6u}}, {{1u, 0u}, Line{true, 0u, 6u}},
                                                                            {{2u, 0u}, Line{true, 0u, 6u}}, {{3u, 0u}, Line{true, 0u, 6u}},
                                                                            {{4u, 0u}, Line{true, 0u, 6u}}, {{5u, 0u}, Line{true, 0u, 6u}},
                                                                            {{6u, 0u}, Line{true, 6u, 6u}}, {{7u, 0u}, Line{true, 6u, 6u}},
                                                                            {{8u, 0u}, Line{true, 6u, 6u}}, {{9u, 0u}, Line{true, 6u, 6u}},
                                                                            {{10u, 0u}, Line{true, 6u, 6u}}, {{11u, 0u}, Line{true, 6u, 6u}},
                                                                            {{12u, 0u}, Line{true, 12u, 6u}}, {{13u, 0u}, Line{true, 12u, 6u}},
                                                                            {{14u, 0u}, Line{true, 12u, 6u}}, {{15u, 0u}, Line{true, 12u, 6u}},
                                                                            {{16u, 0u}, Line{true, 12u, 6u}}, {{17u, 0u}, Line{true, 12u, 6u}},
                                                                            {{18u, 0u}, Line{true, 18u, 6u}}, {{19u, 0u}, Line{true, 18u, 6u}},
                                                                            {{20u, 0u}, Line{true, 18u, 6u}}, {{21u, 0u}, Line{true, 18u, 6u}},
                                                                            {{22u, 0u}, Line{true, 18u, 6u}}, {{23u, 0u}, Line{true, 18u, 6u}},
                                                                            {{24u, 0u}, Line{true, 24u, 7u}}, {{25u, 0u}, Line{true, 24u, 7u}},
                                                                            {{26u, 0u}, Line{true, 24u, 7u}}, {{27u, 0u}, Line{true, 24u, 7u}},
                                                                            {{28u, 0u}, Line{true, 24u, 7u}}, {{29u, 0u}, Line{true, 24u, 7u}},
                                                                            {{30u, 0u}, Line{true, 24u, 7u}},

                                                                            {{0u, 1u}, Line{true, 6u, 6u}}, {{1u, 1u}, Line{true, 6u, 6u}},
                                                                            {{2u, 1u}, Line{true, 6u, 6u}}, {{3u, 1u}, Line{true, 6u, 6u}},
                                                                            {{4u, 1u}, Line{true, 6u, 6u}}, {{5u, 1u}, Line{true, 6u, 6u}},
                                                                            {{6u, 1u}, Line{true, 12u, 6u}}, {{7u, 1u}, Line{true, 12u, 6u}},
                                                                            {{8u, 1u}, Line{true, 12u, 6u}}, {{9u, 1u}, Line{true, 12u, 6u}},
                                                                            {{10u, 1u}, Line{true, 12u, 6u}}, {{11u, 1u}, Line{true, 12u, 6u}},
                                                                            {{12u, 1u}, Line{true, 18u, 6u}}, {{13u, 1u}, Line{true, 18u, 6u}},
                                                                            {{14u, 1u}, Line{true, 18u, 6u}}, {{15u, 1u}, Line{true, 18u, 6u}},
                                                                            {{16u, 1u}, Line{true, 18u, 6u}}, {{17u, 1u}, Line{true, 18u, 6u}},
                                                                            {{18u, 1u}, Line{true, 24u, 7u}}, {{19u, 1u}, Line{true, 24u, 7u}},
                                                                            {{20u, 1u}, Line{true, 24u, 7u}}, {{21u, 1u}, Line{true, 24u, 7u}},
                                                                            {{22u, 1u}, Line{true, 24u, 7u}}, {{23u, 1u}, Line{true, 24u, 7u}},
                                                                            {{24u, 1u}, Line{true, 24u, 7u}}, {{25u, 1u}, Line{true, 24u, 7u}},
                                                                            {{26u, 1u}, Line{true, 24u, 7u}}, {{27u, 1u}, Line{true, 24u, 7u}},
                                                                            {{28u, 1u}, Line{true, 24u, 7u}}, {{29u, 1u}, Line{true, 24u, 7u}},
                                                                            {{30u, 1u}, Line{true, 24u, 7u}},

                                                                            {{0u, 2u}, Line{true, 12u, 6u}}, {{1u, 2u}, Line{true, 12u, 6u}},
                                                                            {{2u, 2u}, Line{true, 12u, 6u}}, {{3u, 2u}, Line{true, 12u, 6u}},
                                                                            {{4u, 2u}, Line{true, 12u, 6u}}, {{5u, 2u}, Line{true, 12u, 6u}},
                                                                            {{6u, 2u}, Line{true, 18u, 6u}}, {{7u, 2u}, Line{true, 18u, 6u}},
                                                                            {{8u, 2u}, Line{true, 18u, 6u}}, {{9u, 2u}, Line{true, 18u, 6u}},
                                                                            {{10u, 2u}, Line{true, 18u, 6u}}, {{11u, 2u}, Line{true, 18u, 6u}},
                                                                            {{12u, 2u}, Line{true, 24u, 7u}}, {{13u, 2u}, Line{true, 24u, 7u}},
                                                                            {{14u, 2u}, Line{true, 24u, 7u}}, {{15u, 2u}, Line{true, 24u, 7u}},
                                                                            {{16u, 2u}, Line{true, 24u, 7u}}, {{17u, 2u}, Line{true, 24u, 7u}},
                                                                            {{18u, 2u}, Line{true, 24u, 7u}}, {{19u, 2u}, Line{true, 24u, 7u}},
                                                                            {{20u, 2u}, Line{true, 24u, 7u}}, {{21u, 2u}, Line{true, 24u, 7u}},
                                                                            {{22u, 2u}, Line{true, 24u, 7u}}, {{23u, 2u}, Line{true, 24u, 7u}},
                                                                            {{24u, 2u}, Line{true, 24u, 7u}}, {{25u, 2u}, Line{true, 24u, 7u}},
                                                                            {{26u, 2u}, Line{true, 24u, 7u}}, {{27u, 2u}, Line{true, 24u, 7u}},
                                                                            {{28u, 2u}, Line{true, 24u, 7u}}, {{29u, 2u}, Line{true, 24u, 7u}},
                                                                            {{30u, 2u}, Line{true, 24u, 7u}},

                                                                            {{0u, 3u}, Line{true, 18u, 6u}}, {{1u, 3u}, Line{true, 18u, 6u}},
                                                                            {{2u, 3u}, Line{true, 18u, 6u}}, {{3u, 3u}, Line{true, 18u, 6u}},
                                                                            {{4u, 3u}, Line{true, 18u, 6u}}, {{5u, 3u}, Line{true, 18u, 6u}},
                                                                            {{6u, 3u}, Line{true, 24u, 7u}}, {{7u, 3u}, Line{true, 24u, 7u}},
                                                                            {{8u, 3u}, Line{true, 24u, 7u}}, {{9u, 3u}, Line{true, 24u, 7u}},
                                                                            {{10u, 3u}, Line{true, 24u, 7u}}, {{11u, 3u}, Line{true, 24u, 7u}},
                                                                            {{12u, 3u}, Line{true, 24u, 7u}}, {{13u, 3u}, Line{true, 24u, 7u}},
                                                                            {{14u, 3u}, Line{true, 24u, 7u}}, {{15u, 3u}, Line{true, 24u, 7u}},
                                                                            {{16u, 3u}, Line{true, 24u, 7u}}, {{17u, 3u}, Line{true, 24u, 7u}},
                                                                            {{18u, 3u}, Line{true, 24u, 7u}}, {{19u, 3u}, Line{true, 24u, 7u}},
                                                                            {{20u, 3u}, Line{true, 24u, 7u}}, {{21u, 3u}, Line{true, 24u, 7u}},
                                                                            {{22u, 3u}, Line{true, 24u, 7u}}, {{23u, 3u}, Line{true, 24u, 7u}},
                                                                            {{24u, 3u}, Line{true, 24u, 7u}}, {{25u, 3u}, Line{true, 24u, 7u}},
                                                                            {{26u, 3u}, Line{true, 24u, 7u}}, {{27u, 3u}, Line{true, 24u, 7u}},
                                                                            {{28u, 3u}, Line{true, 24u, 7u}}, {{29u, 3u}, Line{true, 24u, 7u}},
                                                                            {{30u, 3u}, Line{true, 24u, 7u}},

                                                                            {{0u, 4u}, Line{true, 24u, 7u}}, {{1u, 4u}, Line{true, 24u, 7u}},
                                                                            {{2u, 4u}, Line{true, 24u, 7u}}, {{3u, 4u}, Line{true, 24u, 7u}},
                                                                            {{4u, 4u}, Line{true, 24u, 7u}}, {{5u, 4u}, Line{true, 24u, 7u}},
                                                                            {{6u, 4u}, Line{true, 24u, 7u}}, {{7u, 4u}, Line{true, 24u, 7u}},
                                                                            {{8u, 4u}, Line{true, 24u, 7u}}, {{9u, 4u}, Line{true, 24u, 7u}},
                                                                            {{10u, 4u}, Line{true, 24u, 7u}}, {{11u, 4u}, Line{true, 24u, 7u}},
                                                                            {{12u, 4u}, Line{true, 24u, 7u}}, {{13u, 4u}, Line{true, 24u, 7u}},
                                                                            {{14u, 4u}, Line{true, 24u, 7u}}, {{15u, 4u}, Line{true, 24u, 7u}},
                                                                            {{16u, 4u}, Line{true, 24u, 7u}}, {{17u, 4u}, Line{true, 24u, 7u}},
                                                                            {{18u, 4u}, Line{true, 24u, 7u}}, {{19u, 4u}, Line{true, 24u, 7u}},
                                                                            {{20u, 4u}, Line{true, 24u, 7u}}, {{21u, 4u}, Line{true, 24u, 7u}},
                                                                            {{22u, 4u}, Line{true, 24u, 7u}}, {{23u, 4u}, Line{true, 24u, 7u}},
                                                                            {{24u, 4u}, Line{true, 24u, 7u}}, {{25u, 4u}, Line{true, 24u, 7u}},
                                                                            {{26u, 4u}, Line{true, 24u, 7u}}, {{27u, 4u}, Line{true, 24u, 7u}},
                                                                            {{28u, 4u}, Line{true, 24u, 7u}}, {{29u, 4u}, Line{true, 24u, 7u}},
                                                                            {{30u, 4u}, Line{true, 24u, 7u}}};

        runGetNumberOfLinesAfterIndexMethod(expectedOutput);
    }

    {
        // Erroneous Input - This subtest should throw an exception since the line index exceeds the maximum allowable limit.

        const character_index characterIndex{0u};

        const size_t numberOfLinesAfterIndex{
                                        GetNumberOfLinesAfterIndex(
                                                            asciiInputBuffer_,
                                                            sizeof(asciiInputBuffer_),
                                                            characterIndex)};

        const size_t invalidLineIndex{numberOfLinesAfterIndex};

        ASSERT_THROW(
            GetLineData(
                asciiInputBuffer_,
                sizeof(asciiInputBuffer_),
                invalidLineIndex,
                numberOfLinesAfterIndex), 
            RuntimeException);
    }

    {
        // Erroneous Input - This subtest should throw an exception since the number of lines after index exceeds the maximum allowable limit.

        const character_index characterIndex{0u};

        const size_t invalidNumberOfLinesAfterIndex{
                                                GetNumberOfLinesAfterIndex(
                                                                    asciiInputBuffer_,
                                                                    sizeof(asciiInputBuffer_),
                                                                    characterIndex) + 1u};

        const size_t lineIndex{0u};

        ASSERT_THROW(
            GetLineData(
                asciiInputBuffer_,
                sizeof(asciiInputBuffer_),
                lineIndex,
                invalidNumberOfLinesAfterIndex);, 
            RuntimeException);
    }
}

TEST_F(LineMutationTest, TestDeleteLine)
{
    // Test the DeleteLine() method in the LineMutations class.
    // The method accepts a character buffer, size, and character index.
    // If the original character buffer is ASCII, the internal algorithm selects a selects a random line
    // removes it, and copies the contents to a null-terminated character buffer.
    // If the original character buffer is UTF-8, no line is removed and the
    // original contents are copied to a null-terminated character buffer.

    // The expected output data was gathered during a previous run using the default random seed.
    // If the random seed is changed, the output data will also change and the unit tests will fail.

    const std::map<std::pair<character_index, random_draw_index>, std::pair<const char* const, expected_buffer_size>> asciiOutput{
                                                                                            {{0u, 0u}, {"Line1\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{0u, 1u}, {"Line1\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{0u, 2u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{0u, 3u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{0u, 4u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{0u, 5u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{0u, 6u}, {"Line1\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{0u, 7u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{0u, 8u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{0u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            
                                                                                            {{1u, 0u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{1u, 1u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{1u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{1u, 3u}, {"Line1\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{1u, 4u}, {"Line1\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{1u, 5u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{1u, 6u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{1u, 7u}, {"Line1\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{1u, 8u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{1u, 9u}, {"Line1\nLine2\nLine3\nLine4\0\0", 26}},

                                                                                            {{2u, 0u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{2u, 1u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{2u, 2u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{2u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{2u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{2u, 5u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{2u, 6u}, {"Line1\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{2u, 7u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{2u, 8u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{2u, 9u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            
                                                                                            {{3u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{3u, 1u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{3u, 2u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{3u, 3u}, {"Line1\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{3u, 4u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{3u, 5u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{3u, 6u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{3u, 7u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{3u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{3u, 9u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},

                                                                                            {{4u, 0u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{4u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{4u, 2u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{4u, 3u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{4u, 4u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{4u, 5u}, {"Line1\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{4u, 6u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{4u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{4u, 8u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{4u, 9u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},

                                                                                            {{5u, 0u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{5u, 1u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{5u, 2u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{5u, 3u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{5u, 4u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{5u, 5u}, {"Line1\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{5u, 6u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{5u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{5u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{5u, 9u}, {"Line1\nLine2\nLine3\nLine4\0\0", 26}},

                                                                                            {{6u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{6u, 1u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{6u, 2u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{6u, 3u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{6u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{6u, 5u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{6u, 6u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{6u, 7u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{6u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{6u, 9u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},

                                                                                            {{7u, 0u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{7u, 1u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{7u, 2u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{7u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{7u, 4u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{7u, 5u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{7u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{7u, 7u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{7u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{7u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},

                                                                                            {{8u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{8u, 1u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{8u, 2u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{8u, 3u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{8u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{8u, 5u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{8u, 6u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{8u, 7u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{8u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{8u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},                                                                                            
                                                                                            
                                                                                            {{9u, 0u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{9u, 1u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{9u, 2u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{9u, 3u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{9u, 4u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{9u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{9u, 6u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{9u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},  
                                                                                            {{9u, 8u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{9u, 9u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},

                                                                                            {{10u, 0u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{10u, 1u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{10u, 2u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{10u, 3u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{10u, 4u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{10u, 5u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{10u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},  
                                                                                            {{10u, 7u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{10u, 8u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{10u, 9u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},

                                                                                            {{11u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{11u, 1u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{11u, 2u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{11u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{11u, 4u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{11u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{11u, 6u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{11u, 7u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{11u, 8u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{11u, 9u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},

                                                                                            {{12u, 0u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{12u, 1u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{12u, 2u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{12u, 3u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{12u, 4u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{12u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{12u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{12u, 7u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{12u, 8u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{12u, 9u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},

                                                                                            {{13u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{13u, 1u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{13u, 2u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{13u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{13u, 4u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{13u, 5u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{13u, 6u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{13u, 7u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{13u, 8u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{13u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},

                                                                                            {{14u, 0u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{14u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{14u, 2u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{14u, 3u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{14u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{14u, 5u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{14u, 6u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{14u, 7u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{14u, 8u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{14u, 9u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},

                                                                                            {{15u, 0u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{15u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{15u, 2u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{15u, 3u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{15u, 4u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{15u, 5u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{15u, 6u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{15u, 7u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{15u, 8u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{15u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},

                                                                                            {{16u, 0u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{16u, 1u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{16u, 2u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{16u, 3u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{16u, 4u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{16u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{16u, 6u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{16u, 7u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{16u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{16u, 9u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},

                                                                                            {{17u, 0u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{17u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{17u, 2u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{17u, 3u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{17u, 4u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{17u, 5u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{17u, 6u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{17u, 7u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{17u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{17u, 9u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},

                                                                                            {{18u, 0u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{18u, 1u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{18u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{18u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{18u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{18u, 5u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{18u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{18u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{18u, 8u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{18u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},

                                                                                            {{19u, 0u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{19u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{19u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{19u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{19u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{19u, 5u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{19u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{19u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{19u, 8u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{19u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},

                                                                                            {{20u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{20u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{20u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{20u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{20u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{20u, 5u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{20u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{20u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{20u, 8u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{20u, 9u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},

                                                                                            {{21u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{21u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{21u, 2u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{21u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{21u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{21u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{21u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{21u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{21u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{21u, 9u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},

                                                                                            {{22u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{22u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{22u, 2u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{22u, 3u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{22u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{22u, 5u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{22u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{22u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{22u, 8u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{22u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},

                                                                                            {{23u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{23u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{23u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{23u, 3u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{23u, 4u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{23u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{23u, 6u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{23u, 7u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{23u, 8u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{23u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},

                                                                                            {{24u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{24u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{24u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{24u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{24u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{24u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{24u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{24u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{24u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{24u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},

                                                                                            {{25u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{25u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{25u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{25u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{25u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{25u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{25u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{25u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{25u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{25u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},


                                                                                            {{26u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{26u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{26u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{26u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{26u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{26u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{26u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{26u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{26u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{26u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},

                                                                                            {{27u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{27u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{27u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{27u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{27u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{27u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{27u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{27u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{27u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{27u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},

                                                                                            {{28u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{28u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{28u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{28u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{28u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{28u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{28u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{28u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{28u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{28u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},

                                                                                            {{29u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{29u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{29u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{29u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{29u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{29u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{29u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{29u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{29u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{29u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},

                                                                                            {{30u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{30u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{30u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{30u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{30u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{30u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{30u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{30u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{30u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{30u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}}};

    const std::map<std::pair<character_index, random_draw_index>, std::pair<const char* const, expected_buffer_size>> utf8Output{
                                                                                            {{0u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            
                                                                                            {{1u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{2u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            
                                                                                            {{3u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{4u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{5u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{6u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{7u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{8u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},                                                                                            
                                                                                            
                                                                                            {{9u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},  
                                                                                            {{9u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{10u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},  
                                                                                            {{10u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{11u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{12u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{13u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{14u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{15u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{16u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{17u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{18u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{19u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{20u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{21u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{22u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{23u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{24u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{25u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{26u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{27u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{28u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{29u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{30u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}}};

    using namespace std::placeholders;

    RunSubtest(
        asciiInputBuffer_,
        sizeof(asciiInputBuffer_),
        asciiOutput,
        std::bind(&LineMutations::DeleteLine, this, _1, _2, _3, _4, _5));

    RunSubtest(
        utf8InputBuffer_,
        sizeof(utf8InputBuffer_),
        utf8Output,
        std::bind(&LineMutations::DeleteLine, this, _1, _2, _3, _4, _5));
}

TEST_F(LineMutationTest, TestIsBinarish)
{
    // Test the IsBinarish() method in the LineMutations class.
    // The method accepts a character buffer and size.
    // A boolean flag indicating whether or not the input buffer contains UTF-8 encoding is returned.

    {
        // Valid Input - This subtest should indicate that the input does not contain UTF-8 encoding.

        ASSERT_FALSE(IsBinarish(asciiInputBuffer_, sizeof(asciiInputBuffer_)));
    }

    {
        // Valid Input - This subtest should indicate that the input contains UTF-8 encoding.

        ASSERT_TRUE(IsBinarish(utf8InputBuffer_, sizeof(utf8InputBuffer_)));
    }

    {
        // Valid Input - This subtest should indicate that the input does not contain UTF-8 encoding.

        constexpr char validBuffer[]{'a'};
        constexpr int validBufferSize{sizeof(validBuffer)};

        ASSERT_FALSE(IsBinarish(validBuffer, validBufferSize));
    }

    {
        // Valid Input - This subtest should indicate that the input contains null.

        constexpr char validBuffer[]{"\0"};
        constexpr int validBufferSize{sizeof(validBuffer)};

        ASSERT_TRUE(IsBinarish(validBuffer, validBufferSize));
    }

    {
        // Erroneous Input - This subtest should trigger a runtime exception since the buffer size is 0.

        constexpr char validBuffer[]{'a'};
        constexpr int invalidBufferSize{0};

        EXPECT_THROW(IsBinarish(validBuffer, invalidBufferSize), RuntimeException);
    }
    
    {
        // Erroneous Input - This subtest should trigger a runtime exception since the buffer is null.

        constexpr int validBufferSize{sizeof(asciiInputBuffer_)};

        EXPECT_THROW(IsBinarish(nullptr, validBufferSize), RuntimeException);
    }
}

TEST_F(LineMutationTest, TestDeleteSequentialLines)
{
    // Test the DeleteSequentialLines() method in the LineMutations class.
    // The method accepts a character buffer, size, and character index.
    // If the original character buffer is ASCII, the internal algorithm selects a selects sequential random lines, 
    // removes them, and copies the contents to a null-terminated character buffer.
    // If the original character buffer is UTF-8, no lines are removed and the
    // original contents are copied to a null-terminated character buffer.

    // The expected output data was gathered during a previous run using the default random seed.
    // If the random seed is changed, the output data will also change and the unit tests will fail.

    const std::map<std::pair<character_index, random_draw_index>, std::pair<const char* const, expected_buffer_size>> asciiOutput{
                                                                                            {{0u, 0u}, {"Line1\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{0u, 1u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{0u, 2u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{0u, 3u}, {"Line4\0\0", 8}},
                                                                                            {{0u, 4u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{0u, 5u}, {"Line0\nLine4\0\0", 14}},
                                                                                            {{0u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{0u, 7u}, {"Line3\nLine4\0\0", 14}},
                                                                                            {{0u, 8u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{0u, 9u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            
                                                                                            {{1u, 0u}, {"Line0\nLine1\n", 13}},
                                                                                            {{1u, 1u}, {"Line0\nLine1\n", 13}},
                                                                                            {{1u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{1u, 3u}, {"Line4\0\0", 8}},
                                                                                            {{1u, 4u}, {"Line0\nLine1\n", 13}},
                                                                                            {{1u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{1u, 6u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{1u, 7u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{1u, 8u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{1u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},

                                                                                            {{2u, 0u}, {"Line0\n", 7}},
                                                                                            {{2u, 1u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{2u, 2u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{2u, 3u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{2u, 4u}, {"Line0\nLine3\nLine4\0\0", 20}},
                                                                                            {{2u, 5u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{2u, 6u}, {"Line0\nLine3\nLine4\0\0", 20}},
                                                                                            {{2u, 7u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{2u, 8u}, {"Line0\nLine1\n", 13}},
                                                                                            {{2u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},

                                                                                            {{3u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{3u, 1u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{3u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{3u, 3u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{3u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{3u, 5u}, {"Line0\nLine1\nLine4\0\0", 20}},
                                                                                            {{3u, 6u}, {"Line0\n", 7}},
                                                                                            {{3u, 7u}, {"Line0\nLine1\nLine4\0\0", 20}},
                                                                                            {{3u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{3u, 9u}, {"Line0\nLine1\nLine2\n", 19}},

                                                                                            {{4u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{4u, 1u}, {"Line4\0\0", 8}},
                                                                                            {{4u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{4u, 3u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{4u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{4u, 5u}, {"Line0\nLine3\nLine4\0\0", 20}},
                                                                                            {{4u, 6u}, {"Line0\nLine4\0\0", 14}},
                                                                                            {{4u, 7u}, {"Line0\nLine1\n", 13}},
                                                                                            {{4u, 8u}, {"Line0\nLine1\n", 13}},
                                                                                            {{4u, 9u}, {"Line0\nLine3\nLine4\0\0", 20}},

                                                                                            {{5u, 0u}, {"Line0\nLine1\nLine4\0\0", 20}},
                                                                                            {{5u, 1u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{5u, 2u}, {"Line3\nLine4\0\0", 14}},
                                                                                            {{5u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{5u, 4u}, {"Line0\nLine1\nLine4\0\0", 20}},
                                                                                            {{5u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{5u, 6u}, {"Line0\nLine1\n", 13}},
                                                                                            {{5u, 7u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{5u, 8u}, {"Line2\nLine3\nLine4\0\0", 20}},
                                                                                            {{5u, 9u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},

                                                                                            {{6u, 0u}, {"Line0\nLine3\nLine4\0\0", 20}},
                                                                                            {{6u, 1u}, {"Line0\nLine3\nLine4\0\0", 20}},
                                                                                            {{6u, 2u}, {"Line0\nLine4\0\0", 14}},
                                                                                            {{6u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{6u, 4u}, {"Line0\nLine3\nLine4\0\0", 20}},
                                                                                            {{6u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{6u, 6u}, {"Line0\nLine4\0\0", 14}},
                                                                                            {{6u, 7u}, {"Line0\nLine1\nLine4\0\0", 20}},
                                                                                            {{6u, 8u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{6u, 9u}, {"Line0\nLine1\nLine2\n", 19}},

                                                                                            {{7u, 0u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{7u, 1u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{7u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{7u, 3u}, {"Line0\nLine4\0\0", 14}},
                                                                                            {{7u, 4u}, {"Line0\nLine1\nLine4\0\0", 20}},
                                                                                            {{7u, 5u}, {"Line0\nLine1\n", 13}},
                                                                                            {{7u, 6u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{7u, 7u}, {"Line0\nLine1\nLine4\0\0", 20}},
                                                                                            {{7u, 8u}, {"Line0\nLine4\0\0", 14}},
                                                                                            {{7u, 9u}, {"Line0\nLine1\nLine2\n", 19}},

                                                                                            {{8u, 0u}, {"Line0\nLine3\nLine4\0\0", 20}},
                                                                                            {{8u, 1u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{8u, 2u}, {"Line0\n", 7}},
                                                                                            {{8u, 3u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{8u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{8u, 5u}, {"Line0\n", 7}},
                                                                                            {{8u, 6u}, {"Line0\nLine2\nLine3\nLine4\0\0", 26}},
                                                                                            {{8u, 7u}, {"Line0\nLine3\nLine4\0\0", 20}},
                                                                                            {{8u, 8u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{8u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},                                                                                            

                                                                                            {{9u, 0u}, {"Line0\nLine1\nLine4\0\0", 20}},
                                                                                            {{9u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{9u, 2u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{9u, 3u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{9u, 4u}, {"Line0\nLine1\n", 13}},
                                                                                            {{9u, 5u}, {"Line0\nLine1\nLine4\0\0", 20}},
                                                                                            {{9u, 6u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{9u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},  
                                                                                            {{9u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},  
                                                                                            {{9u, 9u}, {"Line0\nLine1\n", 13}},

                                                                                            {{10u, 0u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{10u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},  
                                                                                            {{10u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},  
                                                                                            {{10u, 3u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{10u, 4u}, {"Line0\nLine3\nLine4\0\0", 20}},
                                                                                            {{10u, 5u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{10u, 6u}, {"Line0\nLine1\n", 13}},
                                                                                            {{10u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},  
                                                                                            {{10u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},  
                                                                                            {{10u, 9u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},

                                                                                            {{11u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{11u, 1u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{11u, 2u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{11u, 3u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{11u, 4u}, {"Line0\n", 7}},
                                                                                            {{11u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{11u, 6u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{11u, 7u}, {"Line0\nLine1\n", 13}},
                                                                                            {{11u, 8u}, {"Line0\nLine3\nLine4\0\0", 20}},
                                                                                            {{11u, 9u}, {"Line0\nLine1\nLine4\0\0", 20}},

                                                                                            {{12u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{12u, 1u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{12u, 2u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{12u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{12u, 4u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{12u, 5u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{12u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{12u, 7u}, {"Line0\nLine1\nLine4\0\0", 20}},
                                                                                            {{12u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{12u, 9u}, {"Line0\nLine1\n", 13}},

                                                                                            {{13u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{13u, 1u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{13u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{13u, 3u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{13u, 4u}, {"Line0\nLine1\nLine4\0\0", 20}},
                                                                                            {{13u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{13u, 6u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{13u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{13u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{13u, 9u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},

                                                                                            {{14u, 0u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{14u, 1u}, {"Line0\nLine1\n", 13}},
                                                                                            {{14u, 2u}, {"Line0\nLine1\n", 13}},
                                                                                            {{14u, 3u}, {"Line0\nLine1\nLine4\0\0", 20}},
                                                                                            {{14u, 4u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{14u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{14u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{14u, 7u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{14u, 8u}, {"Line0\nLine1\nLine4\0\0", 20}},
                                                                                            {{14u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},

                                                                                            {{15u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{15u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{15u, 2u}, {"Line0\nLine1\nLine4\0\0", 20}},
                                                                                            {{15u, 3u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{15u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{15u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{15u, 6u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{15u, 7u}, {"Line0\nLine1\n", 13}},
                                                                                            {{15u, 8u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{15u, 9u}, {"Line0\nLine1\nLine2\n", 19}},

                                                                                            {{16u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{16u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{16u, 2u}, {"Line0\nLine1\nLine4\0\0", 20}},
                                                                                            {{16u, 3u}, {"Line0\nLine1\nLine4\0\0", 20}},
                                                                                            {{16u, 4u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{16u, 5u}, {"Line0\nLine1\nLine4\0\0", 20}},
                                                                                            {{16u, 6u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{16u, 7u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{16u, 8u}, {"Line0\nLine1\nLine3\nLine4\0\0", 26}},
                                                                                            {{16u, 9u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},

                                                                                            {{17u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{17u, 1u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{17u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{17u, 3u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{17u, 4u}, {"Line0\nLine1\nLine4\0\0", 20}},
                                                                                            {{17u, 5u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{17u, 6u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{17u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{17u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{17u, 9u}, {"Line0\nLine1\nLine2\n", 19}},

                                                                                            {{18u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{18u, 1u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{18u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{18u, 3u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{18u, 4u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{18u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{18u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{18u, 7u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{18u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{18u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},

                                                                                            {{19u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{19u, 1u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{19u, 2u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{19u, 3u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{19u, 4u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{19u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{19u, 6u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{19u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{19u, 8u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{19u, 9u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},

                                                                                            {{20u, 0u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{20u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{20u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{20u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{20u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{20u, 5u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{20u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{20u, 7u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{20u, 8u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{20u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},

                                                                                            {{21u, 0u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{21u, 1u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{21u, 2u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{21u, 3u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{21u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{21u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{21u, 6u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{21u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{21u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{21u, 9u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},

                                                                                            {{22u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{22u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{22u, 2u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{22u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{22u, 4u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{22u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{22u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{22u, 7u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{22u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{22u, 9u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},

                                                                                            {{23u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{23u, 1u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{23u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{23u, 3u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{23u, 4u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{23u, 5u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{23u, 6u}, {"Line0\nLine1\nLine2\nLine4\0\0", 26}},
                                                                                            {{23u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{23u, 8u}, {"Line0\nLine1\nLine2\n", 19}},
                                                                                            {{23u, 9u}, {"Line0\nLine1\nLine2\n", 19}},

                                                                                            {{24u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{24u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{24u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{24u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{24u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{24u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{24u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{24u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{24u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{24u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},

                                                                                            {{25u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{25u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{25u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{25u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{25u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{25u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{25u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{25u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{25u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{25u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},

                                                                                            {{26u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{26u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{26u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{26u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{26u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{26u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{26u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{26u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{26u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{26u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},

                                                                                            {{27u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{27u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{27u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{27u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{27u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{27u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{27u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{27u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{27u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{27u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},

                                                                                            {{28u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{28u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{28u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{28u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{28u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{28u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{28u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{28u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{28u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{28u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},

                                                                                            {{29u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{29u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{29u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{29u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{29u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{29u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{29u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{29u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{29u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{29u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},

                                                                                            {{30u, 0u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{30u, 1u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{30u, 2u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{30u, 3u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{30u, 4u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{30u, 5u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{30u, 6u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{30u, 7u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{30u, 8u}, {"Line0\nLine1\nLine2\nLine3\n", 25}},
                                                                                            {{30u, 9u}, {"Line0\nLine1\nLine2\nLine3\n", 25}}};

    const std::map<std::pair<character_index, random_draw_index>, std::pair<const char* const, expected_buffer_size>> utf8Output{
                                                                                            {{0u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            
                                                                                            {{1u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{2u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            
                                                                                            {{3u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{4u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{5u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{6u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{7u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{8u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},                                                                                            
                                                                                            
                                                                                            {{9u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},  
                                                                                            {{9u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{10u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},  
                                                                                            {{10u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{11u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{12u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{13u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{14u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{15u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{16u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{17u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{18u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{19u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{20u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{21u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{22u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{23u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{24u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{25u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{26u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{27u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{28u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{29u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{30u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}}};

    using namespace std::placeholders;

    RunSubtest(
        asciiInputBuffer_,
        sizeof(asciiInputBuffer_),
        asciiOutput,
        std::bind(&LineMutations::DeleteSequentialLines, this, _1, _2, _3, _4, _5));

    RunSubtest(
        utf8InputBuffer_,
        sizeof(utf8InputBuffer_),
        utf8Output,
        std::bind(&LineMutations::DeleteSequentialLines, this, _1, _2, _3, _4, _5));
}

TEST_F(LineMutationTest, TestDuplicateLine)
{
    // Test the DuplicateLine() method in the LineMutations class.
    // The method accepts a character buffer, size, and character index.
    // If the original character buffer is UTF-8, the internal algorithm selects a selects a random line, 
    // duplicates it, and copies the contents to a null-terminated character buffer.
    // If the original character buffer is ASCII, no lines are removed and the
    // original contents are copied to a null-terminated character buffer.

    // The expected output data was gathered during a previous run using the default random seed.
    // If the random seed is changed, the output data will also change and the unit tests will fail.

    const std::map<std::pair<character_index, random_draw_index>, std::pair<const char* const, expected_buffer_size>> asciiOutput{
                                                                                            {{0u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{1u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{2u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{3u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{4u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{5u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{6u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{7u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{8u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{9u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{10u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{11u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{12u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{13u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{14u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{15u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{16u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{17u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{18u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{19u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{20u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{21u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{22u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{23u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{24u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{25u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{26u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{27u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{28u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{29u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{30u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}}};

    const std::map<std::pair<character_index, random_draw_index>, std::pair<const char* const, expected_buffer_size>> utf8Output{
                                                                                            {{0u, 0u}, {u8"🤣0\n🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{0u, 1u}, {u8"🤣0\n🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{0u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{0u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{0u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{0u, 5u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{0u, 6u}, {u8"🤣0\n🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{0u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{0u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{0u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            
                                                                                            {{1u, 0u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{1u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{1u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{1u, 3u}, {u8"🤣0\n🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{1u, 4u}, {u8"🤣0\n🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{1u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{1u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{1u, 7u}, {u8"🤣0\n🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{1u, 8u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{1u, 9u}, {u8"🤣0\n🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{2u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{2u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{2u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{2u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{2u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{2u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{2u, 6u}, {u8"🤣0\n🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{2u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{2u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{2u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            
                                                                                            {{3u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{3u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{3u, 2u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{3u, 3u}, {u8"🤣0\n🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{3u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{3u, 5u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{3u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{3u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{3u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{3u, 9u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{4u, 0u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{4u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{4u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{4u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{4u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{4u, 5u}, {u8"🤣0\n🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{4u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{4u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{4u, 8u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{4u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{5u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{5u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{5u, 2u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{5u, 3u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{5u, 4u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{5u, 5u}, {u8"🤣0\n🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{5u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{5u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{5u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{5u, 9u}, {u8"🤣0\n🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{6u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{6u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{6u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{6u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{6u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{6u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{6u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{6u, 7u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{6u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{6u, 9u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{7u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{7u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{7u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{7u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{7u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{7u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{7u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{7u, 7u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{7u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{7u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},

                                                                                            {{8u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{8u, 1u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{8u, 2u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{8u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{8u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{8u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{8u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{8u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{8u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{8u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            
                                                                                            {{9u, 0u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{9u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{9u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{9u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{9u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{9u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{9u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{9u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{9u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{9u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{10u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{10u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{10u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{10u, 3u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{10u, 4u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{10u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{10u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{10u, 7u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{10u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{10u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{11u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{11u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{11u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{11u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{11u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{11u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{11u, 6u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{11u, 7u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{11u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{11u, 9u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{12u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{12u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{12u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{12u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{12u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{12u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{12u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{12u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{12u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{12u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{13u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{13u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{13u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{13u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{13u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{13u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{13u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{13u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{13u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{13u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},

                                                                                            {{14u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{14u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{14u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{14u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{14u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{14u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{14u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{14u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{14u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{14u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{15u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{15u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{15u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{15u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{15u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{15u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{15u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{15u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{15u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{15u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},

                                                                                            {{16u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{16u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{16u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{16u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{16u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{16u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{16u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{16u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{16u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{16u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{17u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{17u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{17u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{17u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{17u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{17u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{17u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{17u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{17u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{17u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{18u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{18u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{18u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{18u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{18u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{18u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{18u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{18u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{18u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{18u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},

                                                                                            {{19u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{19u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{19u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{19u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{19u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{19u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{19u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{19u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{19u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{19u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},

                                                                                            {{20u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{20u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{20u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{20u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{20u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{20u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{20u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{20u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{20u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{20u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{21u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{21u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{21u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{21u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{21u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{21u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{21u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{21u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{21u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{21u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{22u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{22u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{22u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{22u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{22u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{22u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{22u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{22u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{22u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{22u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},

                                                                                            {{23u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{23u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{23u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{23u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{23u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{23u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{23u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{23u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{23u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{23u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},

                                                                                            {{24u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{24u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{24u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{24u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{24u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{24u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{24u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{24u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{24u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{24u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},

                                                                                            {{25u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{25u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{25u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{25u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{25u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{25u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{25u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{25u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{25u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{25u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},

                                                                                            {{26u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{26u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{26u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{26u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{26u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{26u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{26u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{26u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{26u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{26u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},

                                                                                            {{27u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{27u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{27u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{27u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{27u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{27u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{27u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{27u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{27u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{27u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},

                                                                                            {{28u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{28u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{28u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{28u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{28u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{28u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{28u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{28u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{28u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{28u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},

                                                                                            {{29u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{29u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{29u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{29u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{29u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{29u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{29u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{29u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{29u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{29u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},

                                                                                            {{30u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{30u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{30u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{30u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{30u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{30u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{30u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{30u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{30u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{30u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}}};

    using namespace std::placeholders;

    RunSubtest(
        asciiInputBuffer_,
        sizeof(asciiInputBuffer_),
        asciiOutput,
        std::bind(&LineMutations::DuplicateLine, this, _1, _2, _3, _4, _5));

    RunSubtest(
        utf8InputBuffer_,
        sizeof(utf8InputBuffer_),
        utf8Output,
        std::bind(&LineMutations::DuplicateLine, this, _1, _2, _3, _4, _5));
}

TEST_F(LineMutationTest, TestCopyLineCloseBy)
{
    // Test the CopyLineCloseBy() method in the LineMutations class.
    // The method accepts a character buffer, size, and character index.
    // If the original character buffer is UTF-8, the internal algorithm selects two random lines (source and destination), 
    // duplicates the source at destination, shifts the contents, and copies the contents to a null-terminated character buffer.
    // If the original character buffer is ASCII, no lines are removed and the
    // original contents are copied to a null-terminated character buffer.

    // The expected output data was gathered during a previous run using the default random seed.
    // If the random seed is changed, the output data will also change and the unit tests will fail.

    const std::map<std::pair<character_index, random_draw_index>, std::pair<const char* const, expected_buffer_size>> asciiOutput{
                                                                                            {{0u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{1u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{2u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{3u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{4u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{5u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{6u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{7u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{8u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{9u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{10u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{11u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{12u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{13u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{14u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{15u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{16u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{17u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{18u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{19u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{20u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{21u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{22u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{23u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{24u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{25u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{26u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{27u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{28u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{29u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{30u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}}};

    const std::map<std::pair<character_index, random_draw_index>, std::pair<const char* const, expected_buffer_size>> utf8Output{
                                                                                            {{0u, 0u}, {u8"🤣0\n🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{0u, 1u}, {u8"🤣0\n🤣1\n🤣3\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{0u, 2u}, {u8"🤣0\n🤣2\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{0u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣0\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{0u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{0u, 5u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{0u, 6u}, {u8"🤣4\0\0🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 39}},
                                                                                            {{0u, 7u}, {u8"🤣0\n🤣1\n🤣0\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{0u, 8u}, {u8"🤣3\n🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{0u, 9u}, {u8"🤣1\n🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            
                                                                                            {{1u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{1u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣2\n🤣4\0\0", 38}},
                                                                                            {{1u, 2u}, {u8"🤣0\n🤣1\n🤣4\0\0🤣2\n🤣3\n🤣4\0\0", 39}},
                                                                                            {{1u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣0\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{1u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{1u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{1u, 6u}, {u8"🤣1\n🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{1u, 7u}, {u8"🤣0\n🤣3\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{1u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{1u, 9u}, {u8"🤣0\n🤣4\0\0🤣1\n🤣2\n🤣3\n🤣4\0\0", 39}},

                                                                                            {{2u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣1\n🤣4\0\0", 38}},
                                                                                            {{2u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{2u, 2u}, {u8"🤣3\n🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{2u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{2u, 4u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{2u, 5u}, {u8"🤣0\n🤣1\n🤣3\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{2u, 6u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{2u, 7u}, {u8"🤣1\n🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{2u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣2\n🤣4\0\0", 38}},
                                                                                            {{2u, 9u}, {u8"🤣4\0\0🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 39}},
                                                                                            
                                                                                            {{3u, 0u}, {u8"🤣0\n🤣1\n🤣4\0\0🤣2\n🤣3\n🤣4\0\0", 39}},
                                                                                            {{3u, 1u}, {u8"🤣0\n🤣2\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{3u, 2u}, {u8"🤣0\n🤣1\n🤣4\0\0🤣2\n🤣3\n🤣4\0\0", 39}},
                                                                                            {{3u, 3u}, {u8"🤣1\n🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{3u, 4u}, {u8"🤣4\0\0🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 39}},
                                                                                            {{3u, 5u}, {u8"🤣0\n🤣2\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{3u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣1\n🤣4\0\0", 38}},
                                                                                            {{3u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{3u, 8u}, {u8"🤣4\0\0🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 39}},
                                                                                            {{3u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{4u, 0u}, {u8"🤣4\0\0🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 39}},
                                                                                            {{4u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣0\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{4u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{4u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{4u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{4u, 5u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{4u, 6u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{4u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣2\n🤣4\0\0", 38}},
                                                                                            {{4u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣2\n🤣4\0\0", 38}},
                                                                                            {{4u, 9u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{5u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{5u, 1u}, {u8"🤣1\n🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{5u, 2u}, {u8"🤣0\n🤣1\n🤣0\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{5u, 3u}, {u8"🤣4\0\0🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 39}},
                                                                                            {{5u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{5u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{5u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣2\n🤣4\0\0", 38}},
                                                                                            {{5u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{5u, 8u}, {u8"🤣0\n🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{5u, 9u}, {u8"🤣3\n🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{6u, 0u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{6u, 1u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{6u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣1\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{6u, 3u}, {u8"🤣0\n🤣4\0\0🤣1\n🤣2\n🤣3\n🤣4\0\0", 39}},
                                                                                            {{6u, 4u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{6u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{6u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣1\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{6u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{6u, 8u}, {u8"🤣0\n🤣2\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{6u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{7u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{7u, 1u}, {u8"🤣0\n🤣3\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{7u, 2u}, {u8"🤣0\n🤣1\n🤣4\0\0🤣2\n🤣3\n🤣4\0\0", 39}},
                                                                                            {{7u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣1\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{7u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{7u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣2\n🤣4\0\0", 38}},
                                                                                            {{7u, 6u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{7u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{7u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣1\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{7u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{8u, 0u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{8u, 1u}, {u8"🤣0\n🤣2\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{8u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣1\n🤣4\0\0", 38}},
                                                                                            {{8u, 3u}, {u8"🤣0\n🤣2\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{8u, 4u}, {u8"🤣0\n🤣1\n🤣4\0\0🤣2\n🤣3\n🤣4\0\0", 39}},
                                                                                            {{8u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣1\n🤣4\0\0", 38}},
                                                                                            {{8u, 6u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{8u, 7u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{8u, 8u}, {u8"🤣0\n🤣2\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{8u, 9u}, {u8"🤣0\n🤣1\n🤣4\0\0🤣2\n🤣3\n🤣4\0\0", 39}},

                                                                                            {{9u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{9u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{9u, 2u}, {u8"🤣0\n🤣3\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{9u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{9u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣2\n🤣4\0\0", 38}},
                                                                                            {{9u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{9u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{9u, 7u}, {u8"🤣0\n🤣1\n🤣4\0\0🤣2\n🤣3\n🤣4\0\0", 39}},
                                                                                            {{9u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{9u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣2\n🤣4\0\0", 38}},

                                                                                            {{10u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{10u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{10u, 2u}, {u8"🤣0\n🤣1\n🤣4\0\0🤣2\n🤣3\n🤣4\0\0", 39}},
                                                                                            {{10u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{10u, 4u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{10u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{10u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{10u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{10u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{10u, 9u}, {u8"🤣0\n🤣3\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{11u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{11u, 1u}, {u8"🤣0\n🤣2\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{11u, 2u}, {u8"🤣0\n🤣1\n🤣3\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{11u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{11u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣1\n🤣4\0\0", 38}},
                                                                                            {{11u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{11u, 6u}, {u8"🤣0\n🤣3\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{11u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣2\n🤣4\0\0", 38}},
                                                                                            {{11u, 8u}, {u8"🤣0\n🤣1\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{11u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{12u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{12u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{12u, 2u}, {u8"🤣0\n🤣1\n🤣3\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{12u, 3u}, {u8"🤣0\n🤣1\n🤣4\0\0🤣2\n🤣3\n🤣4\0\0", 39}},
                                                                                            {{12u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{12u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{12u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{12u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{12u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{12u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣2\n🤣4\0\0", 38}},

                                                                                            {{13u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{13u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{13u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{13u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{13u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{13u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{13u, 6u}, {u8"🤣0\n🤣1\n🤣3\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{13u, 7u}, {u8"🤣0\n🤣1\n🤣4\0\0🤣2\n🤣3\n🤣4\0\0", 39}},
                                                                                            {{13u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{13u, 9u}, {u8"🤣0\n🤣1\n🤣3\n🤣2\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{14u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{14u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣2\n🤣4\0\0", 38}},
                                                                                            {{14u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣2\n🤣4\0\0", 38}},
                                                                                            {{14u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{14u, 4u}, {u8"🤣0\n🤣1\n🤣3\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{14u, 5u}, {u8"🤣0\n🤣1\n🤣4\0\0🤣2\n🤣3\n🤣4\0\0", 39}},
                                                                                            {{14u, 6u}, {u8"🤣0\n🤣1\n🤣4\0\0🤣2\n🤣3\n🤣4\0\0", 39}},
                                                                                            {{14u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{14u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{14u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},

                                                                                            {{15u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{15u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{15u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{15u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{15u, 4u}, {u8"🤣0\n🤣1\n🤣4\0\0🤣2\n🤣3\n🤣4\0\0", 39}},
                                                                                            {{15u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{15u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{15u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣2\n🤣4\0\0", 38}},
                                                                                            {{15u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{15u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{16u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{16u, 1u}, {u8"🤣0\n🤣1\n🤣4\0\0🤣2\n🤣3\n🤣4\0\0", 39}},
                                                                                            {{16u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{16u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{16u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{16u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{16u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{16u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{16u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{16u, 9u}, {u8"🤣0\n🤣1\n🤣3\n🤣2\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{17u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{17u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{17u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{17u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{17u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣2\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{17u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{17u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{17u, 7u}, {u8"🤣0\n🤣1\n🤣4\0\0🤣2\n🤣3\n🤣4\0\0", 39}},
                                                                                            {{17u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{17u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{18u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{18u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{18u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{18u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{18u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{18u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{18u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{18u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{18u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{18u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},

                                                                                            {{19u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{19u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{19u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{19u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{19u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{19u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{19u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{19u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{19u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{19u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{20u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{20u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{20u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{20u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{20u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{20u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{20u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{20u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{20u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{20u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},

                                                                                            {{21u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{21u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{21u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{21u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{21u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{21u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{21u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{21u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{21u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{21u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{22u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{22u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{22u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{22u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{22u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{22u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{22u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{22u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{22u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{22u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{23u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{23u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{23u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{23u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{23u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{23u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{23u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{23u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣4\0\0🤣3\n🤣4\0\0", 39}},
                                                                                            {{23u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},
                                                                                            {{23u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣3\n🤣4\0\0", 38}},

                                                                                            {{24u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{24u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{24u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{24u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{24u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{24u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{24u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{24u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{24u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{24u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},

                                                                                            {{25u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{25u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{25u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{25u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{25u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{25u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{25u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{25u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{25u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{25u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},

                                                                                            {{26u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{26u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{26u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{26u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{26u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{26u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{26u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{26u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{26u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{26u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},

                                                                                            {{27u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{27u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{27u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{27u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{27u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{27u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{27u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{27u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{27u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{27u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},

                                                                                            {{28u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{28u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{28u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{28u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{28u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{28u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{28u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{28u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{28u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{28u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},

                                                                                            {{29u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{29u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{29u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{29u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{29u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{29u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{29u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{29u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{29u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{29u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},

                                                                                            {{30u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{30u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{30u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{30u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{30u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{30u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{30u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{30u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{30u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}},
                                                                                            {{30u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0🤣4\0\0", 39}}};

    using namespace std::placeholders;

    RunSubtest(
        asciiInputBuffer_,
        sizeof(asciiInputBuffer_),
        asciiOutput,
        std::bind(&LineMutations::CopyLineCloseBy, this, _1, _2, _3, _4, _5));

    RunSubtest(
        utf8InputBuffer_,
        sizeof(utf8InputBuffer_),
        utf8Output,
        std::bind(&LineMutations::CopyLineCloseBy, this, _1, _2, _3, _4, _5));
}

TEST_F(LineMutationTest, TestRepeatLine)
{
    // Test the RepeatLine() method in the LineMutations class.
    // The method accepts a character buffer, size, and character index.
    // If the original character buffer is UTF-8, the internal algorithm selects a selects a random line, 
    // duplicates it a random number of times, and copies the contents to a null-terminated character buffer.
    // If the original character buffer is ASCII, no lines are removed and the
    // original contents are copied to a null-terminated character buffer.

    // The expected output data was gathered during a previous run using the default random seed.
    // If the random seed is changed, the output data will also change and the unit tests will fail.

    // NOTE:
    // The RepeatLine() method is capable of duplicating the random line a variable number of times.
    // The range is defined as [1, 2097153].
    // Since the number of line repetitions is random and can vary greatly, it is not feasible to write a subtest which
    // exercises the cases where the original character buffer is UTF-8.
    // Any modifications that are made to the RepeatLine() method should therefore be tested manually
    // in order to verify correct behavior.
    // As of 06/29/23, the RepeatLine() method was verified to work for UTF-8 character buffers.

    const std::map<std::pair<character_index, random_draw_index>, std::pair<const char* const, expected_buffer_size>> asciiOutput{
                                                                                            {{0u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{0u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{1u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{1u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{2u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{2u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{3u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{3u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{4u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{4u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{5u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{5u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{6u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{6u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{7u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{7u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{8u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{8u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{9u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{9u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{10u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{10u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{11u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{11u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{12u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{12u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{13u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{13u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{14u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{14u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{15u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{15u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{16u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{16u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{17u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{17u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{18u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{18u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{19u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{19u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{20u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{20u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{21u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{21u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{22u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{22u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{23u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{23u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{24u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{24u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{25u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{25u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{26u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{26u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{27u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{27u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{28u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{28u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{29u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{29u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},

                                                                                            {{30u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}},
                                                                                            {{30u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0", 32}}};

    using namespace std::placeholders;

    RunSubtest(
        asciiInputBuffer_,
        sizeof(asciiInputBuffer_),
        asciiOutput,
        std::bind(&LineMutations::RepeatLine, this, _1, _2, _3, _4, _5));
}

TEST_F(LineMutationTest, TestSwapLine)
{
    // Test the TestSwapLine() method in the LineMutations class.
    // The method accepts a character buffer, size, and character index.
    // If the original character buffer is ASCII, the internal algorithm selects a selects sequential random lines, 
    // swaps them, and copies the contents to a null-terminated character buffer.
    // If the original character buffer is UTF-8, no lines are swapped and the
    // original contents are copied to a null-terminated character buffer.

    // The expected output data was gathered during a previous run using the default random seed.
    // If the random seed is changed, the output data will also change and the unit tests will fail.

    const std::map<std::pair<character_index, random_draw_index>, std::pair<const char* const, expected_buffer_size>> asciiOutput{
                                                                                            {{0u, 0u}, {"Line1\nLine0\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{0u, 1u}, {"Line1\nLine0\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{0u, 2u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{0u, 3u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{0u, 4u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{0u, 5u}, {"Line0\nLine2\nLine1\nLine3\nLine4\0\0", 32}},
                                                                                            {{0u, 6u}, {"Line1\nLine0\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{0u, 7u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{0u, 8u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{0u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},

                                                                                            {{1u, 0u}, {"Line0\nLine2\nLine1\nLine3\nLine4\0\0", 32}},
                                                                                            {{1u, 1u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{1u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{1u, 3u}, {"Line1\nLine0\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{1u, 4u}, {"Line1\nLine0\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{1u, 5u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{1u, 6u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{1u, 7u}, {"Line1\nLine0\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{1u, 8u}, {"Line0\nLine2\nLine1\nLine3\nLine4\0\0", 32}},
                                                                                            {{1u, 9u}, {"Line1\nLine0\nLine2\nLine3\nLine4\0\0", 32}},

                                                                                            {{2u, 0u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{2u, 1u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{2u, 2u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{2u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{2u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{2u, 5u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{2u, 6u}, {"Line1\nLine0\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{2u, 7u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{2u, 8u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{2u, 9u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},

                                                                                            {{3u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{3u, 1u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{3u, 2u}, {"Line0\nLine2\nLine1\nLine3\nLine4\0\0", 32}},
                                                                                            {{3u, 3u}, {"Line1\nLine0\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{3u, 4u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{3u, 5u}, {"Line0\nLine2\nLine1\nLine3\nLine4\0\0", 32}},
                                                                                            {{3u, 6u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{3u, 7u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{3u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{3u, 9u}, {"Line0\nLine2\nLine1\nLine3\nLine4\0\0", 32}},

                                                                                            {{4u, 0u}, {"Line0\nLine2\nLine1\nLine3\nLine4\0\0", 32}},
                                                                                            {{4u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{4u, 2u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{4u, 3u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{4u, 4u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{4u, 5u}, {"Line1\nLine0\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{4u, 6u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{4u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{4u, 8u}, {"Line0\nLine2\nLine1\nLine3\nLine4\0\0", 32}},
                                                                                            {{4u, 9u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},

                                                                                            {{5u, 0u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{5u, 1u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{5u, 2u}, {"Line0\nLine2\nLine1\nLine3\nLine4\0\0", 32}},
                                                                                            {{5u, 3u}, {"Line0\nLine2\nLine1\nLine3\nLine4\0\0", 32}},
                                                                                            {{5u, 4u}, {"Line0\nLine2\nLine1\nLine3\nLine4\0\0", 32}},
                                                                                            {{5u, 5u}, {"Line1\nLine0\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{5u, 6u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{5u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{5u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{5u, 9u}, {"Line1\nLine0\nLine2\nLine3\nLine4\0\0", 32}},

                                                                                            {{6u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{6u, 1u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{6u, 2u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{6u, 3u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{6u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{6u, 5u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{6u, 6u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{6u, 7u}, {"Line0\nLine2\nLine1\nLine3\nLine4\0\0", 32}},
                                                                                            {{6u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{6u, 9u}, {"Line0\nLine2\nLine1\nLine3\nLine4\0\0", 32}},

                                                                                            {{7u, 0u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{7u, 1u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{7u, 2u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{7u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{7u, 4u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{7u, 5u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{7u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{7u, 7u}, {"Line0\nLine2\nLine1\nLine3\nLine4\0\0", 32}},
                                                                                            {{7u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{7u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},

                                                                                            {{8u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{8u, 1u}, {"Line0\nLine2\nLine1\nLine3\nLine4\0\0", 32}},
                                                                                            {{8u, 2u}, {"Line0\nLine2\nLine1\nLine3\nLine4\0\0", 32}},
                                                                                            {{8u, 3u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{8u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{8u, 5u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{8u, 6u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{8u, 7u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{8u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{8u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},

                                                                                            {{9u, 0u}, {"Line0\nLine2\nLine1\nLine3\nLine4\0\0", 32}},
                                                                                            {{9u, 1u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{9u, 2u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{9u, 3u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{9u, 4u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{9u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{9u, 6u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{9u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{9u, 8u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{9u, 9u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},

                                                                                            {{10u, 0u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{10u, 1u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{10u, 2u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{10u, 3u}, {"Line0\nLine2\nLine1\nLine3\nLine4\0\0", 32}},
                                                                                            {{10u, 4u}, {"Line0\nLine2\nLine1\nLine3\nLine4\0\0", 32}},
                                                                                            {{10u, 5u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{10u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{10u, 7u}, {"Line0\nLine2\nLine1\nLine3\nLine4\0\0", 32}},
                                                                                            {{10u, 8u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{10u, 9u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},

                                                                                            {{11u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{11u, 1u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{11u, 2u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{11u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{11u, 4u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{11u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{11u, 6u}, {"Line0\nLine2\nLine1\nLine3\nLine4\0\0", 32}},
                                                                                            {{11u, 7u}, {"Line0\nLine2\nLine1\nLine3\nLine4\0\0", 32}},
                                                                                            {{11u, 8u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{11u, 9u}, {"Line0\nLine2\nLine1\nLine3\nLine4\0\0", 32}},

                                                                                            {{12u, 0u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{12u, 1u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{12u, 2u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{12u, 3u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{12u, 4u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{12u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{12u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{12u, 7u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{12u, 8u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{12u, 9u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},

                                                                                            {{13u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{13u, 1u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{13u, 2u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{13u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{13u, 4u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{13u, 5u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{13u, 6u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{13u, 7u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{13u, 8u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{13u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},

                                                                                            {{14u, 0u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{14u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{14u, 2u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{14u, 3u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{14u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{14u, 5u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{14u, 6u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{14u, 7u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{14u, 8u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{14u, 9u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},

                                                                                            {{15u, 0u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{15u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{15u, 2u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{15u, 3u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{15u, 4u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{15u, 5u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{15u, 6u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{15u, 7u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{15u, 8u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{15u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},

                                                                                            {{16u, 0u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{16u, 1u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{16u, 2u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{16u, 3u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{16u, 4u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{16u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{16u, 6u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{16u, 7u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{16u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{16u, 9u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},

                                                                                            {{17u, 0u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{17u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{17u, 2u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{17u, 3u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{17u, 4u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{17u, 5u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{17u, 6u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{17u, 7u}, {"Line0\nLine1\nLine3\nLine2\nLine4\0\0", 32}},
                                                                                            {{17u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{17u, 9u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},

                                                                                            {{18u, 0u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{18u, 1u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{18u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{18u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{18u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{18u, 5u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{18u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{18u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{18u, 8u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{18u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},

                                                                                            {{19u, 0u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{19u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{19u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{19u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{19u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{19u, 5u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{19u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{19u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{19u, 8u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{19u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},

                                                                                            {{20u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{20u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{20u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{20u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{20u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{20u, 5u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{20u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{20u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{20u, 8u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{20u, 9u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},

                                                                                            {{21u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{21u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{21u, 2u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{21u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{21u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{21u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{21u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{21u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{21u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{21u, 9u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},

                                                                                            {{22u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{22u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{22u, 2u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{22u, 3u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{22u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{22u, 5u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{22u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{22u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{22u, 8u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{22u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},

                                                                                            {{23u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{23u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{23u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{23u, 3u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{23u, 4u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{23u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{23u, 6u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{23u, 7u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{23u, 8u}, {"Line0\nLine1\nLine2\nLine4\0\0Line3\n", 32}},
                                                                                            {{23u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},

                                                                                            {{24u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{24u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{24u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{24u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{24u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{24u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{24u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{24u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{24u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{24u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},

                                                                                            {{25u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{25u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{25u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{25u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{25u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{25u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{25u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{25u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{25u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{25u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},

                                                                                            {{26u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{26u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{26u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{26u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{26u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{26u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{26u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{26u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{26u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{26u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},

                                                                                            {{27u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{27u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{27u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{27u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{27u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{27u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{27u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{27u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{27u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{27u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},

                                                                                            {{28u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{28u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{28u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{28u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{28u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{28u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{28u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{28u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{28u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{28u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},

                                                                                            {{29u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{29u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{29u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{29u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{29u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{29u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{29u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{29u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{29u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{29u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},

                                                                                            {{30u, 0u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{30u, 1u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{30u, 2u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{30u, 3u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{30u, 4u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{30u, 5u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{30u, 6u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{30u, 7u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{30u, 8u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}},
                                                                                            {{30u, 9u}, {"Line0\nLine1\nLine2\nLine3\nLine4\0\0", 32}}};

    const std::map<std::pair<character_index, random_draw_index>, std::pair<const char* const, expected_buffer_size>> utf8Output{
                                                                                            {{0u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{0u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            
                                                                                            {{1u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{1u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{2u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{2u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            
                                                                                            {{3u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{3u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{4u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{4u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{5u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{5u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{6u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{6u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{7u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{7u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{8u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{8u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},                                                                                            
                                                                                            
                                                                                            {{9u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},  
                                                                                            {{9u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{9u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{10u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},  
                                                                                            {{10u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{10u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{11u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{11u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{12u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{12u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{13u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{13u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{14u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{14u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{15u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{15u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{16u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{16u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{17u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{17u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{18u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{18u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{19u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{19u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{20u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{20u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{21u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{21u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{22u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{22u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{23u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{23u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{24u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{24u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{25u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{25u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{26u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{26u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{27u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{27u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{28u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{28u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{29u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{29u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},

                                                                                            {{30u, 0u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 1u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 2u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 3u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 4u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 5u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 6u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 7u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 8u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}},
                                                                                            {{30u, 9u}, {u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0\0", 32}}};

    using namespace std::placeholders;

    RunSubtest(
        asciiInputBuffer_,
        sizeof(asciiInputBuffer_),
        asciiOutput,
        std::bind(&LineMutations::SwapLine, this, _1, _2, _3, _4, _5));

    RunSubtest(
        utf8InputBuffer_,
        sizeof(utf8InputBuffer_),
        utf8Output,
        std::bind(&LineMutations::SwapLine, this, _1, _2, _3, _4, _5));
}

TEST_F(LineMutationTest, TestLineStructure)
{
    Line lhs;

    // Test default constructor

    EXPECT_FALSE(lhs.IsValid);
    EXPECT_EQ(lhs.StartIndex, 0u);
    EXPECT_EQ(lhs.Size, 0u);

    // Test inequality operator

    Line rhs;

    rhs.IsValid = true;
    rhs.StartIndex = 1u;
    rhs.Size = 2u;

    EXPECT_NE(lhs, rhs);

    // Test equality operator

    rhs.IsValid = false;
    rhs.StartIndex = 0u;
    rhs.Size = 0u;

    EXPECT_EQ(lhs, rhs);
}

TEST_F(LineMutationTest, TestLineVectorStructure)
{
    auto fillLineVector{
                    [&](LineVector& lineVector)
                    {
                        lineVector.Data = std::make_unique<char[]>(10u);
                        lineVector.Size = 10u;
                        
                        for (size_t it{0u}; it < lineVector.Size; ++it)
                            lineVector.Data[it] = it;
                    }};

    {
        // Test default constructor

        LineVector lineVector;

        EXPECT_EQ(lineVector.Data.get(), nullptr);
        EXPECT_EQ(lineVector.Size, 0u);
    }

    {
        // Test parameterized constructor

        constexpr size_t validCharacterIndex{0u};

        const size_t numberOfLinesAfterIndex{
                                        GetNumberOfLinesAfterIndex(
                                                            asciiInputBuffer_,
                                                            sizeof(asciiInputBuffer_),
                                                            validCharacterIndex)};

        constexpr size_t validLineIndex{0u};

        const Line lineData{
                        GetLineData(
                                asciiInputBuffer_,
                                sizeof(asciiInputBuffer_),
                                validLineIndex,
                                numberOfLinesAfterIndex)};

        const auto lineVector{
                        LineVector{
                                asciiInputBuffer_,
                                lineData}};
                                
        EXPECT_EQ(lineVector.Size, lineData.Size);
        EXPECT_EQ(memcmp(lineVector.Data.get(), asciiInputBuffer_, lineData.Size), 0);
    }

    {
        // Test inequality operator

        LineVector rhs;

        fillLineVector(rhs);

        EXPECT_NE(LineVector{}, rhs);
    }

    {
        // Test equality operator

        LineVector lhs;

        EXPECT_EQ(lhs, LineVector{});
    }

    {
        // Test copy constructor

        LineVector original;

        fillLineVector(original);

        EXPECT_EQ(original, LineVector{original});
    }

    {
        // Test move constructor

        LineVector original;

        fillLineVector(original);

        auto copy{LineVector{original}};

        LineVector moved{std::move(original)};

        EXPECT_NE(original, moved);
        EXPECT_EQ(original.Data.get(), nullptr);
        EXPECT_EQ(original.Size, 0u);
        EXPECT_EQ(copy, moved);
    }

    {
        // Test copy assignment operator

        LineVector original;

        fillLineVector(original);

        LineVector copied = original;

        EXPECT_EQ(original, copied);
    }

    {
        // Test move assignment operator

        LineVector original;

        fillLineVector(original);

        auto copy{LineVector{original}};

        LineVector moved = std::move(original);

        EXPECT_NE(original, moved);
        EXPECT_EQ(original.Data.get(), nullptr);
        EXPECT_EQ(original.Size, 0u);
        EXPECT_EQ(copy, moved);
    }
}

TEST_F(LineMutationTest, TestLineListStructure)
{
    auto fillLineList{
                [&](LineList& lineList)
                {
                    LineVector lineVector;

                    lineVector.Data = std::make_unique<char[]>(10u);
                    lineVector.Size = 10u;
                    
                    for (size_t it{0u}; it < lineVector.Size; ++it)
                        lineVector.Data[it] = it;

                    lineList.Data = std::make_unique<LineVector[]>(10u);
                    lineList.NumberOfElements = 10u;

                    for (size_t it{0u}; it < lineList.NumberOfElements; ++it)
                    {
                        lineList.Data[it] = lineVector;
                        lineList.Capacity += lineVector.Size;
                    }
                }};

    {
        // Test default constructor

        LineList lineList;

        EXPECT_EQ(lineList.Data.get(), nullptr);
        EXPECT_EQ(lineList.NumberOfElements, 0u);
        EXPECT_EQ(lineList.Capacity, 0u);
    }

    {
        // Test parameterized constructor

        auto compareLineVectors{
                            [&](const LineVector* const lhs, const LineVector* const rhs) -> bool
                            {
                                if (lhs != nullptr && rhs != nullptr)
                                {
                                    for (size_t it{0u}; it < lhs->Size; ++it)
                                        if (lhs->Data[it] != rhs->Data[it])
                                            return false;

                                    return true;
                                }
                                else if (lhs == nullptr && rhs == nullptr)
                                {
                                    return true;
                                }
                                else
                                {
                                    return false;
                                }
                            }};

        constexpr size_t validCharacterIndex{0u};

        const size_t numberOfLinesAfterIndex{
                                        GetNumberOfLinesAfterIndex(
                                                            asciiInputBuffer_,
                                                            sizeof(asciiInputBuffer_),
                                                            validCharacterIndex)};

        constexpr size_t validLineIndex{0u};

        const std::vector<Line> lineData{
                                    GetLineData(
                                            asciiInputBuffer_,
                                            sizeof(asciiInputBuffer_),
                                            validLineIndex,
                                            numberOfLinesAfterIndex)};

        const auto lineList{
                        LineList{
                            asciiInputBuffer_,
                            lineData}};

        EXPECT_EQ(lineList.NumberOfElements, 1u);

        const bool retVal{
                    compareLineVectors(
                                    lineList.Data.get(),
                                    std::make_unique<LineVector>(
                                                            asciiInputBuffer_,
                                                            lineData.front()).get())};

        EXPECT_TRUE(retVal);
    }

    {
        // Test inequality operator

        LineList rhs;

        fillLineList(rhs);

        EXPECT_NE(LineList{}, rhs);
    }

    {
        // Test equality operator

        LineList lhs;

        EXPECT_EQ(lhs, LineList{});
    }

    {
        // Test copy constructor

        LineList original;

        fillLineList(original);

        EXPECT_EQ(original, LineList{original});
    }

    {
        // Test move constructor

        LineList original;

        fillLineList(original);

        auto copy{LineList{original}};

        LineList moved{std::move(original)};

        EXPECT_NE(original, moved);
        EXPECT_EQ(original.Data.get(), nullptr);
        EXPECT_EQ(original.Capacity, 0u);
        EXPECT_EQ(original.NumberOfElements, 0u);
        EXPECT_EQ(copy, moved);
    }

    {
        // Test copy assignment operator

        LineList original;

        fillLineList(original);

        LineList copied = original;

        EXPECT_EQ(original, copied);
    }

    {
        // Test move assignment operator

        LineList original;

        fillLineList(original);

        auto copy{LineList{original}};

        LineList moved = std::move(original);

        EXPECT_NE(original, moved);
        EXPECT_EQ(original.Data.get(), nullptr);
        EXPECT_EQ(original.Capacity, 0u);
        EXPECT_EQ(original.NumberOfElements, 0u);
        EXPECT_EQ(copy, moved);
    }
}
}

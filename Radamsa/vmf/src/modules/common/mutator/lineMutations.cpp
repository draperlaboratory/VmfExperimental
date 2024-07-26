/* =============================================================================
 * Vader Modular Fuzzer
 * Copyright (c) 2021-2023 The Charles Stark Draper Laboratory, Inc.
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
/*****
 * The following includes code copied from the LibAFL_Legacy repository.
 *
 *       american fuzzy lop++ - fuzzer header
 *  ------------------------------------
 *  Originally written by Michal Zalewski
 *  Now maintained by Marc Heuse <mh@mh-sec.de>,
 *                    Heiko Eißfeldt <heiko.eissfeldt@hexco.de>,
 *                    Andrea Fioraldi <andreafioraldi@gmail.com>,
 *                    Dominik Maier <mail@dmnk.co>
 *  Copyright 2016, 2017 Google Inc. All rights reserved.
 *  Copyright 2019-2020 AFLplusplus Project. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *    http://www.apache.org/licenses/LICENSE-2.0
 *  This is the Library based on AFL++ which can be used to build
 *  customized fuzzers for a specific target while taking advantage of
 *  a lot of features that AFL++ already provides.
 */

// C/C++ Includes
#include <algorithm>

// VMF Includes
#include "lineMutations.hpp"
#include "Logging.hpp"

vmf::radamsa::mutations::LineMutations::Line vmf::radamsa::mutations::LineMutations::GetLineData(
                                                                                                const char* const buffer,
                                                                                                const size_t size,
                                                                                                const size_t lineIndex,
                                                                                                const size_t numberOfLinesAfterIndex)
{
    constexpr size_t minimumSize{1u};

    if (size < minimumSize)
        throw RuntimeException{"The buffer's minimum size must be greater than or equal to 1", RuntimeException::USAGE_ERROR};

    if (buffer == nullptr)
        throw RuntimeException{"Input buffer is null", RuntimeException::UNEXPECTED_ERROR};

    const size_t totalNumberOfLines{
                                GetNumberOfLinesAfterIndex(
                                                        buffer,
                                                        size,
                                                        0u)};

    if (lineIndex > totalNumberOfLines - 1u)
        throw RuntimeException{"Line index exceeds the maximum number of lines", RuntimeException::UNEXPECTED_ERROR};

    if (numberOfLinesAfterIndex > totalNumberOfLines)
        throw RuntimeException{"Number of lines after index exceeds the maximum number of lines", RuntimeException::UNEXPECTED_ERROR};

    const size_t lineOffset{totalNumberOfLines - numberOfLinesAfterIndex};

    constexpr size_t lower{0u};
    const size_t upper{totalNumberOfLines - 1u};
    const size_t maximumLineIndex{
                            std::clamp(
                                    lineIndex + lineOffset,
                                    lower,
                                    upper)};

    Line lineData;

    for(size_t it{0u}, reverseLineIndex{maximumLineIndex}; it < size; ++it)
    {
        if(reverseLineIndex == 0u)
        {
            if(!lineData.IsValid)
            {
                lineData.StartIndex = it;
                lineData.IsValid = true;
            }

            ++lineData.Size;

            if(buffer[it] == '\n')
                break;
        }
        else
        {
            if(buffer[it] == '\n')
                --reverseLineIndex;
        }
    }

    return lineData;
}

size_t vmf::radamsa::mutations::LineMutations::GetNumberOfLinesAfterIndex(
                                                                    const char* const buffer,
                                                                    const size_t size,
                                                                    const size_t index)
{
    constexpr size_t minimumSize{1u};

    if (size < minimumSize)
        throw RuntimeException{"The buffer's minimum size must be greater than or equal to 1", RuntimeException::USAGE_ERROR};

    if (index > size - 1u)
        throw RuntimeException{"Index is out of bounds", RuntimeException::INDEX_OUT_OF_RANGE};

    if (buffer == nullptr)
        throw RuntimeException{"Input buffer is null", RuntimeException::UNEXPECTED_ERROR};

    size_t numberOfLines{0u};

    for(size_t it{index}; it < size; ++it)
        if(buffer[it] == '\n')
            ++numberOfLines;

    return ++numberOfLines;
}

bool vmf::radamsa::mutations::LineMutations::IsBinarish(
                                                    const char* const buffer,
                                                    const size_t size)
{
    constexpr size_t minimumSize{1u};

    if (size < minimumSize)
        throw RuntimeException{"The buffer's minimum size must be greater than or equal to 1", RuntimeException::USAGE_ERROR};

    if (buffer == nullptr)
        throw RuntimeException{"Input buffer is null", RuntimeException::UNEXPECTED_ERROR};

    constexpr size_t binarishPeekSize{8u};

    for(size_t it{0}; it < binarishPeekSize; ++it)
    {
        // Peek into the data and return true if it contains UTF-8 or \0.

        if(it == size)
            break;

        if(buffer[it] == '\0')
            return true;

        if((buffer[it] & (std::numeric_limits<char>::max() + 0x01)) != 0u)
            return true;
    }

    return false;
}

void vmf::radamsa::mutations::LineMutations::DeleteLine(
                                                    StorageEntry* newEntry,
                                                    const size_t originalSize,
                                                    const char* originalBuffer,
                                                    const size_t characterIndex,
                                                    const int testCaseKey)
{
    // Consume the original buffer by deleting a line from it and appending a null-terminator to the end.

    constexpr size_t minimumSize{1u};

    if (originalSize < minimumSize)
        throw RuntimeException{"The buffer's minimum size must be greater than or equal to 1", RuntimeException::USAGE_ERROR};

    if (characterIndex > originalSize - 1u)
        throw RuntimeException{"Character index is out of bounds", RuntimeException::INDEX_OUT_OF_RANGE};

    if (originalBuffer == nullptr)
        throw RuntimeException{"Input buffer is null", RuntimeException::UNEXPECTED_ERROR};

    if (IsBinarish(originalBuffer, originalSize))
    {
        // The new buffer will contain one additional byte since a null-terminator will be appended to the end.

        const size_t newBufferSize{originalSize + 1u};

        // Allocate the new buffer, set it's elements to those of the original buffer, and append a null-terminator to the end.

        char* newBuffer{newEntry->allocateBuffer(testCaseKey, static_cast<int>(newBufferSize))};
        memset(newBuffer, 0u, newBufferSize);
        memcpy(newBuffer, originalBuffer, originalSize);
    }
    else
    {
        const size_t numberOfLinesAfterIndex{
                                        GetNumberOfLinesAfterIndex(
                                                                originalBuffer,
                                                                originalSize,
                                                                characterIndex)};

        // Select a random line to delete.

        constexpr size_t minimumRandomLineIndex{0u};
        const size_t maximumRandomLineIndex{numberOfLinesAfterIndex - 1u};

        const size_t randomLineIndex{
                                GetRandomValueWithinBounds(
                                                        minimumRandomLineIndex,
                                                        maximumRandomLineIndex)};

        const Line lineData{
                        GetLineData(
                                originalBuffer,
                                originalSize,
                                randomLineIndex,
                                numberOfLinesAfterIndex)};

        // The new buffer will be one line smaller than the original buffer;
        // additionally, it will contain one additional byte since a null-terminator will be appended to the end.

        const size_t newBufferSize{originalSize - lineData.Size + 1u};

        // Allocate the new buffer and set it's elements to zero.

        char* newBuffer{newEntry->allocateBuffer(testCaseKey, newBufferSize)};
        memset(newBuffer, 0u, newBufferSize);

        // Copy data from the original buffer into the new buffer, but skip the elements in the random line that is to be deleted.
        // The last element in the new buffer is skipped since it was implicitly set to zero during allocation.

        for(size_t sourceIndex{0u}, destinationIndex{0u}; sourceIndex < originalSize; ++sourceIndex)
        {
            const size_t lineStartIndex{lineData.StartIndex};
            const size_t lineEndIndex{lineStartIndex + lineData.Size};

            if(sourceIndex < lineStartIndex || sourceIndex >= lineEndIndex)
            {
                newBuffer[destinationIndex] = originalBuffer[sourceIndex];
                ++destinationIndex;
            }
        }
    }
}

void vmf::radamsa::mutations::LineMutations::DeleteSequentialLines(
                                                                StorageEntry* newEntry,
                                                                const size_t originalSize,
                                                                const char* originalBuffer,
                                                                const size_t characterIndex,
                                                                const int testCaseKey)
{
    // Consume the original buffer by deleting sequential lines from it and appending a null-terminator to the end.

    constexpr size_t minimumSize{1u};

    if (originalSize < minimumSize)
        throw RuntimeException{"The buffer's minimum size must be greater than or equal to 1", RuntimeException::USAGE_ERROR};

    if (characterIndex > originalSize - 1u)
        throw RuntimeException{"Minimum seed index is out of bounds", RuntimeException::INDEX_OUT_OF_RANGE};

    if (originalBuffer == nullptr)
        throw RuntimeException{"Input buffer is null", RuntimeException::UNEXPECTED_ERROR};

    if (IsBinarish(originalBuffer, originalSize))
    {
        // The new buffer will contain one additional byte since a null-terminator will be appended to the end.

        const size_t newBufferSize{originalSize + 1u};

        // Allocate the new buffer, set it's elements to those of the original buffer, and append a null-terminator to the end.

        char* newBuffer{newEntry->allocateBuffer(testCaseKey, static_cast<int>(newBufferSize))};
        memset(newBuffer, 0u, newBufferSize);
        memcpy(newBuffer, originalBuffer, originalSize);
    }
    else
    {
        const size_t numberOfLinesAfterIndex{
                                        GetNumberOfLinesAfterIndex(
                                                                originalBuffer,
                                                                originalSize,
                                                                characterIndex)};

        // Select a random line to delete.

        const size_t minimumRandomLineOffset{0u};

        const size_t randomLineIndexStart{
                                    GetRandomValueWithinBounds(
                                                            minimumRandomLineOffset,
                                                            numberOfLinesAfterIndex - 1u)};

        const size_t randomLineIndexEnd{
                                    GetRandomValueWithinBounds(
                                                            minimumRandomLineOffset,
                                                            (numberOfLinesAfterIndex - 1u) - randomLineIndexStart) + randomLineIndexStart};

        const Line startLineData{
                            GetLineData(
                                    originalBuffer,
                                    originalSize,
                                    randomLineIndexStart,
                                    numberOfLinesAfterIndex)};

        const Line endLineData{
                            GetLineData(
                                    originalBuffer,
                                    originalSize,
                                    randomLineIndexEnd,
                                    numberOfLinesAfterIndex)};

        // The new buffer will be multiple lines smaller than the original buffer;
        // additionally, it will contain one additional byte since a null-terminator will be appended to the end.

        const size_t newBufferSize{(originalSize - ((endLineData.StartIndex + endLineData.Size) - startLineData.StartIndex)) + 1u};

        // Allocate the new buffer and set it's elements to zero.

        char* newBuffer{newEntry->allocateBuffer(testCaseKey, newBufferSize)};
        memset(newBuffer, 0u, newBufferSize);

        // Copy data from the original buffer into the new buffer, but skip the elements in the random lines that are to be deleted.
        // The last element in the new buffer is skipped since it was implicitly set to zero during allocation.

        for(size_t sourceIndex{0u}, destinationIndex{0u}; sourceIndex < originalSize; ++sourceIndex)
        {
            const size_t lineStartIndex{startLineData.StartIndex};
            const size_t lineEndIndex{endLineData.StartIndex + endLineData.Size};

            if(sourceIndex < lineStartIndex || sourceIndex >= lineEndIndex)
            {
                newBuffer[destinationIndex] = originalBuffer[sourceIndex];
                ++destinationIndex;
            }
        }
    }
}

void vmf::radamsa::mutations::LineMutations::DuplicateLine(
                                                        StorageEntry* newEntry,
                                                        const size_t originalSize,
                                                        const char* originalBuffer,
                                                        const size_t characterIndex,
                                                        const int testCaseKey)
{
    // Consume the original buffer by duplicating a line from it and appending a null-terminator to the end.

    constexpr size_t minimumSize{1u};

    if (originalSize < minimumSize)
        throw RuntimeException{"The buffer's minimum size must be greater than or equal to 1", RuntimeException::USAGE_ERROR};

    if (characterIndex > originalSize - 1u)
        throw RuntimeException{"Minimum seed index is out of bounds", RuntimeException::INDEX_OUT_OF_RANGE};

    if (originalBuffer == nullptr)
        throw RuntimeException{"Input buffer is null", RuntimeException::UNEXPECTED_ERROR};

    const size_t numberOfLinesAfterIndex{
                                    GetNumberOfLinesAfterIndex(
                                                        originalBuffer,
                                                        originalSize,
                                                        characterIndex)};

    if (!IsBinarish(originalBuffer, originalSize))
    {
        // The new buffer will contain one additional byte since a null-terminator will be appended to the end.

        const size_t newBufferSize{originalSize + 1u};

        // Allocate the new buffer, set it's elements to those of the original buffer, and append a null-terminator to the end.

        char* newBuffer{newEntry->allocateBuffer(testCaseKey, static_cast<int>(newBufferSize))};
        memset(newBuffer, 0u, newBufferSize);
        memcpy(newBuffer, originalBuffer, originalSize);
    }
    else
    {
        // Select a random line to duplicate.

        constexpr size_t minimumRandomLineIndex{0u};
        const size_t maximumRandomLineIndex{numberOfLinesAfterIndex - 1u};

        const size_t randomLineIndex{
                                GetRandomValueWithinBounds(
                                                        minimumRandomLineIndex,
                                                        maximumRandomLineIndex)};

        const Line lineData{
                        GetLineData(
                                originalBuffer,
                                originalSize,
                                randomLineIndex,
                                numberOfLinesAfterIndex)};

        // The new buffer will be one line larger than the original buffer;
        // additionally, it will contain one additional byte since a null-terminator will be appended to the end.

        const size_t newBufferSize{originalSize + lineData.Size + 1u};

        // Allocate the new buffer and set it's elements to zero.

        char* newBuffer{newEntry->allocateBuffer(testCaseKey, newBufferSize)};
        memset(newBuffer, 0u, newBufferSize);

        // Copy data from the original buffer into the new buffer, but duplicate the random line.
        // The last element in the new buffer is skipped since it was implicitly set to zero during allocation.

        {
            // Copy all of the elements including the line that is to be duplicated.

            const size_t numberOfBytes{lineData.StartIndex + lineData.Size};

            char* destination{newBuffer};
            const char* source{originalBuffer};

            memcpy(destination, source, numberOfBytes);
        }

        {
            // Duplicate the line.

            const size_t numberOfBytes{lineData.Size};

            char* destination{newBuffer + lineData.StartIndex + lineData.Size};
            const char* source{originalBuffer + lineData.StartIndex};

            memcpy(destination, source, numberOfBytes);
        }

        {
            // Copy all of the elements after the line that was duplicated.

            const size_t numberOfBytes{originalSize - (lineData.StartIndex + lineData.Size)};

            char* destination{newBuffer + lineData.StartIndex + 2 * lineData.Size};
            const char* source{originalBuffer + lineData.StartIndex + lineData.Size};

            memcpy(destination, source, numberOfBytes);
        }
    }
}

void vmf::radamsa::mutations::LineMutations::CopyLineCloseBy(
                                                        StorageEntry* newEntry,
                                                        const size_t originalSize,
                                                        const char* originalBuffer,
                                                        const size_t characterIndex,
                                                        const int testCaseKey)
{
    // Consume the original buffer by copying a line to a random location and appending a null-terminator to the end.

    constexpr size_t minimumSize{1u};

    if (originalSize < minimumSize)
        throw RuntimeException{"The buffer's minimum size must be greater than or equal to 1", RuntimeException::USAGE_ERROR};

    if (characterIndex > originalSize - 1u)
        throw RuntimeException{"Minimum seed index is out of bounds", RuntimeException::INDEX_OUT_OF_RANGE};

    if (originalBuffer == nullptr)
        throw RuntimeException{"Input buffer is null", RuntimeException::UNEXPECTED_ERROR};

    const size_t numberOfLinesAfterIndex{
                                    GetNumberOfLinesAfterIndex(
                                                        originalBuffer,
                                                        originalSize,
                                                        characterIndex)};

    if (!IsBinarish(originalBuffer, originalSize))
    {
        // The new buffer will contain one additional byte since a null-terminator will be appended to the end.

        const size_t newBufferSize{originalSize + 1u};

        // Allocate the new buffer, set it's elements to those of the original buffer, and append a null-terminator to the end.

        char* newBuffer{newEntry->allocateBuffer(testCaseKey, static_cast<int>(newBufferSize))};
        memset(newBuffer, 0u, newBufferSize);
        memcpy(newBuffer, originalBuffer, originalSize);
    }
    else
    {
        // Select random line to copy from/to.

        const size_t minimumRandomLineOffset{0u};

        const size_t randomLineIndexSource{
                                    GetRandomValueWithinBounds(
                                                        minimumRandomLineOffset,
                                                        numberOfLinesAfterIndex - 1u)};

        const size_t randomLineIndexDestination{
                                        GetRandomValueWithinBounds(
                                                            minimumRandomLineOffset,
                                                            numberOfLinesAfterIndex - 1u)};

        const Line lineDataSource{
                            GetLineData(
                                    originalBuffer,
                                    originalSize,
                                    randomLineIndexSource,
                                    numberOfLinesAfterIndex)};

        const Line lineDataDestination{
                                GetLineData(
                                        originalBuffer,
                                        originalSize,
                                        randomLineIndexDestination,
                                        numberOfLinesAfterIndex)};

        // The new buffer will be one line larger than the original buffer;
        // additionally, it will contain one additional byte since a null-terminator will be appended to the end.

        const size_t newBufferSize{originalSize + lineDataSource.Size + 1u};

        // Allocate the new buffer and set it's elements to zero.

        char* newBuffer{newEntry->allocateBuffer(testCaseKey, newBufferSize)};
        memset(newBuffer, 0u, newBufferSize);

        // Copy data from the original buffer into the new buffer, but copy the random line.
        // The last element in the new buffer is skipped since it was implicitly set to zero during allocation.

        for(size_t sourceIndex{0u}, destinationIndex{0u}; sourceIndex < originalSize; ++sourceIndex)
        {
            if(sourceIndex == lineDataDestination.StartIndex)
            {
                memcpy(&newBuffer[destinationIndex], &originalBuffer[lineDataSource.StartIndex], lineDataSource.Size);

                destinationIndex += lineDataSource.Size;
            }

            newBuffer[destinationIndex] = originalBuffer[sourceIndex];

            ++destinationIndex;
        }
    }
}

void vmf::radamsa::mutations::LineMutations::RepeatLine(
                                                    StorageEntry* newEntry,
                                                    const size_t originalSize,
                                                    const char* originalBuffer,
                                                    const size_t characterIndex,
                                                    const int testCaseKey)
{
    // Consume the original buffer by repeating a random line multiple times and appending a null-terminator to the end.

    constexpr size_t minimumSize{1u};

    if (originalSize < minimumSize)
        throw RuntimeException{"The buffer's minimum size must be greater than or equal to 1", RuntimeException::USAGE_ERROR};

    if (characterIndex > originalSize - 1u)
        throw RuntimeException{"Minimum seed index is out of bounds", RuntimeException::INDEX_OUT_OF_RANGE};

    if (originalBuffer == nullptr)
        throw RuntimeException{"Input buffer is null", RuntimeException::UNEXPECTED_ERROR};

    const size_t numberOfLinesAfterIndex{
                                    GetNumberOfLinesAfterIndex(
                                                        originalBuffer,
                                                        originalSize,
                                                        characterIndex)};

    if (!IsBinarish(originalBuffer, originalSize))
    {
        // The new buffer will contain one additional byte since a null-terminator will be appended to the end.

        const size_t newBufferSize{originalSize + 1u};

        // Allocate the new buffer, set it's elements to those of the original buffer, and append a null-terminator to the end.

        char* newBuffer{newEntry->allocateBuffer(testCaseKey, static_cast<int>(newBufferSize))};
        memset(newBuffer, 0u, newBufferSize);
        memcpy(newBuffer, originalBuffer, originalSize);
    }
    else
    {
        // Select a random line to duplicate.

        constexpr size_t minimumRandomLineIndex{0u};
        const size_t maximumRandomLineIndex{numberOfLinesAfterIndex - 1u};

        const size_t randomLineIndex{
                                GetRandomValueWithinBounds(
                                                        minimumRandomLineIndex,
                                                        maximumRandomLineIndex)};

        const Line lineData{
                        GetLineData(
                                originalBuffer,
                                originalSize,
                                randomLineIndex,
                                numberOfLinesAfterIndex)};

        const size_t numberOfRandomLineRepetitions{GetRandomByteRepetitionLength()};

        // The new buffer will be multiple lines larger than the original buffer;
        // additionally, it will contain one additional byte since a null-terminator will be appended to the end.

        const size_t newBufferSize{originalSize + (lineData.Size * numberOfRandomLineRepetitions) + 1u};

        // Allocate the new buffer and set it's elements to zero.

        char* newBuffer{newEntry->allocateBuffer(testCaseKey, newBufferSize)};
        memset(newBuffer, 0u, newBufferSize);

        // Copy data from the original buffer into the new buffer, but repeat the random line.
        // The last element in the new buffer is skipped since it was implicitly set to zero during allocation.

        for(size_t sourceIndex{0u}, destinationIndex{0u}; sourceIndex < originalSize; ++sourceIndex)
        {
            if(sourceIndex == lineData.StartIndex)
            {
                for (size_t k{0u}; k < (numberOfRandomLineRepetitions + 1u); ++k)
                {
                    memcpy(&newBuffer[destinationIndex], &originalBuffer[sourceIndex], lineData.Size);

                    destinationIndex += lineData.Size;
                }

                sourceIndex += lineData.Size;
            }

            newBuffer[destinationIndex] = originalBuffer[sourceIndex];

            ++destinationIndex;
        }
    }
}

void vmf::radamsa::mutations::LineMutations::SwapLine(
                                                    StorageEntry* newEntry,
                                                    const size_t originalSize,
                                                    const char* originalBuffer,
                                                    const size_t characterIndex,
                                                    const int testCaseKey)
{
    // Consume the original buffer by copying a line to a random location and appending a null-terminator to the end.

    constexpr size_t minimumSize{1u};

    if (originalSize < minimumSize)
        throw RuntimeException{"The buffer's minimum size must be greater than or equal to 1", RuntimeException::USAGE_ERROR};

    if (characterIndex > originalSize - 1u)
        throw RuntimeException{"Minimum seed index is out of bounds", RuntimeException::INDEX_OUT_OF_RANGE};

    if (originalBuffer == nullptr)
        throw RuntimeException{"Input buffer is null", RuntimeException::UNEXPECTED_ERROR};

    const size_t numberOfLinesAfterIndex{
                                    GetNumberOfLinesAfterIndex(
                                                        originalBuffer,
                                                        originalSize,
                                                        characterIndex)};

    if (IsBinarish(originalBuffer, originalSize))
    {
        // The new buffer will contain one additional byte since a null-terminator will be appended to the end.

        const size_t newBufferSize{originalSize + 1u};

        // Allocate the new buffer, set it's elements to those of the original buffer, and append a null-terminator to the end.

        char* newBuffer{newEntry->allocateBuffer(testCaseKey, static_cast<int>(newBufferSize))};
        memset(newBuffer, 0u, newBufferSize);
        memcpy(newBuffer, originalBuffer, originalSize);
    }
    else
    {
        // Select random line to copy from/to.

        const size_t minimumRandomLineOffset{0u};

        const size_t firstRandomLineIndex{
                                    GetRandomValueWithinBounds(
                                                        minimumRandomLineOffset,
                                                        numberOfLinesAfterIndex - 1u)};

        const size_t totalNumberOfLines{
                                    GetNumberOfLinesAfterIndex(
                                                            originalBuffer,
                                                            originalSize,
                                                            0u)};


        constexpr size_t lower{0u};
        const size_t upper{totalNumberOfLines - 1u};
        const size_t secondRandomLineIndex{
                                        std::clamp(
                                                firstRandomLineIndex + 1u,
                                                lower,
                                                upper)};

        const Line firstRandomLineData{
                                GetLineData(
                                        originalBuffer,
                                        originalSize,
                                        firstRandomLineIndex,
                                        numberOfLinesAfterIndex)};

        const Line secondRandomLineData{
                                GetLineData(
                                        originalBuffer,
                                        originalSize,
                                        secondRandomLineIndex,
                                        numberOfLinesAfterIndex)};

        // The new buffer will be one line larger than the original buffer;
        // additionally, it will contain one additional byte since a null-terminator will be appended to the end.

        const size_t newBufferSize{originalSize + 1u};

        // Allocate the new buffer and set it's elements to zero.

        char* newBuffer{newEntry->allocateBuffer(testCaseKey, newBufferSize)};
        memset(newBuffer, 0u, newBufferSize);

        // Copy data from the original buffer into the new buffer, but duplicate the random line.
        // The last element in the new buffer is skipped since it was implicitly set to zero during allocation.

        {
            // Copy all of the elements including the line that is to be duplicated.

            const size_t numberOfBytes{originalSize};

            char* destination{newBuffer};
            const char* source{originalBuffer};

            memcpy(destination, source, numberOfBytes);
        }

        {
            // Duplicate the line.

            const size_t numberOfBytes{secondRandomLineData.Size};

            char* destination{newBuffer + firstRandomLineData.StartIndex};
            const char* source{originalBuffer + secondRandomLineData.StartIndex};

            memcpy(destination, source, numberOfBytes);
        }

        {
            // Copy all of the elements after the line that was duplicated.

            const size_t numberOfBytes{firstRandomLineData.Size};

            char* destination{
                        (firstRandomLineData == secondRandomLineData) ?
                        (newBuffer + firstRandomLineData.StartIndex) :
                        (newBuffer + firstRandomLineData.StartIndex + secondRandomLineData.Size)};

            const char* source{originalBuffer + firstRandomLineData.StartIndex};

            memcpy(destination, source, numberOfBytes);
        }
    }
}

size_t vmf::radamsa::mutations::LineMutations::GetRandomLogValue(const size_t maximumValue)
{
    constexpr size_t minimumValue{2u};

    if(maximumValue <= minimumValue)
        return 0u;

    return GetRandomN_Bit(GetRandomValueWithinBounds(0u, maximumValue - minimumValue) + minimumValue);
}

size_t vmf::radamsa::mutations::LineMutations::GetRandomN_Bit(const size_t n)
{
    const size_t highValue{(n - 1u) << 1u};
    const size_t randomValue{GetRandomValueWithinBounds(0u, highValue)};
    const size_t nBitValue{randomValue | highValue};

    return nBitValue;
}

void vmf::radamsa::mutations::LineMutations::PermuteLine(
                                                        StorageEntry* newEntry,
                                                        const size_t originalSize,
                                                        const char* originalBuffer,
                                                        const size_t characterIndex,
                                                        const int testCaseKey)
{
    // Consume the original buffer by copying a line to a random location and appending a null-terminator to the end.

    constexpr size_t minimumSize{1u};

    if (originalSize < minimumSize)
        throw RuntimeException{"The buffer's minimum size must be greater than or equal to 1", RuntimeException::USAGE_ERROR};

    if (characterIndex > originalSize - 1u)
        throw RuntimeException{"Minimum seed index is out of bounds", RuntimeException::INDEX_OUT_OF_RANGE};

    if (originalBuffer == nullptr)
        throw RuntimeException{"Input buffer is null", RuntimeException::UNEXPECTED_ERROR};

    const size_t numberOfLinesAfterIndex{
                                    GetNumberOfLinesAfterIndex(
                                                        originalBuffer,
                                                        originalSize,
                                                        characterIndex)};

    if (IsBinarish(originalBuffer, originalSize))
    {
        // The new buffer will contain one additional byte since a null-terminator will be appended to the end.

        const size_t newBufferSize{originalSize + 1u};

        // Allocate the new buffer, set it's elements to those of the original buffer, and append a null-terminator to the end.

        char* newBuffer{newEntry->allocateBuffer(testCaseKey, static_cast<int>(newBufferSize))};
        memset(newBuffer, 0u, newBufferSize);
        memcpy(newBuffer, originalBuffer, originalSize);
    }
    else
    {
        auto getLineData{
                    [&](const char* const buffer, const size_t size, const size_t numberOfLinesAfterIndex) -> std::vector<Line>
                    {
                        std::vector<Line> lineData;

                        lineData.reserve(numberOfLinesAfterIndex);

                        for(size_t it{0u}; it < numberOfLinesAfterIndex; ++it)
                        {
                            lineData.emplace_back(
                                            GetLineData(
                                                    buffer,
                                                    size,
                                                    it,
                                                    numberOfLinesAfterIndex));                    
                        }

                        return lineData;
                    }};

        // Select random line to copy from/to.

        constexpr size_t minimumRandomLineOffset{0u};

        const size_t randomStartLineIndex{
                                    (numberOfLinesAfterIndex <= 3u) ?
                                    (GetRandomValueWithinBounds(
                                                            minimumRandomLineOffset,
                                                            numberOfLinesAfterIndex - 1u)) :
                                    (GetRandomValueWithinBounds(
                                                            minimumRandomLineOffset,
                                                            numberOfLinesAfterIndex - 4u))}; // numlines - 3

        const size_t firstNumberOfRandomLinePermutations{
                                                    GetRandomValueWithinBounds(
                                                                        minimumRandomLineOffset,
                                                                        numberOfLinesAfterIndex - randomStartLineIndex - 1u) + 2u};

        constexpr size_t maximumValue{10u};
        const size_t secondNumberOfRandomLinePermutations{GetRandomLogValue(maximumValue)};

        constexpr size_t lhs{2u};
        const size_t totalNumberOfRandomLinePermutations{
                                                    std::max<size_t>(
                                                                    lhs,
                                                                    std::min(
                                                                        firstNumberOfRandomLinePermutations,
                                                                        secondNumberOfRandomLinePermutations))};

        const std::vector<Line> lineData{
                                    getLineData(
                                            originalBuffer,
                                            originalSize,
                                            numberOfLinesAfterIndex)};

        auto lineList{
                LineList{
                    originalBuffer,
                    lineData}};

        for (size_t permutationLenght{totalNumberOfRandomLinePermutations}, startLineIndex{randomStartLineIndex}; permutationLenght != 1u; permutationLenght--, startLineIndex++)
        {
            const size_t randomLineIndex{GetRandomValueWithinBounds(0u, permutationLenght) + randomStartLineIndex};

            std::swap(lineList.Data[randomStartLineIndex], lineList.Data[randomLineIndex]);
        }

        // The new buffer will be one line larger than the original buffer;
        // additionally, it will contain one additional byte since a null-terminator will be appended to the end.

        const size_t newBufferSize{lineList.Capacity + 1u};

        // Allocate the new buffer and set it's elements to zero.

        char* newBuffer{newEntry->allocateBuffer(testCaseKey, newBufferSize)};
        memset(newBuffer, 0u, newBufferSize);

        for (size_t it{0u}, destinationIndex{0u}; it < lineList.NumberOfElements; ++it)
        {
            const size_t numberOfBytes{lineList.Data[it].Size};

            const char* const source{lineList.Data[it].Data.get()};
            char* destination{&newBuffer[destinationIndex]};
            
            memcpy(destination, source, numberOfBytes);

            destinationIndex += lineList.Data[it].Size;
            std::cout << "\ntest!!!";
        }
    }
}
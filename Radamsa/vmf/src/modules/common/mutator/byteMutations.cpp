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

#include "byteMutations.hpp"

void vmf::radamsa::mutations::ByteMutations::DropByte(
                                                    StorageEntry* newEntry,
                                                    const size_t originalSize,
                                                    const char* originalBuffer,
                                                    const size_t minimumSeedIndex,
                                                    const int testCaseKey)
{
    // Consume the original buffer by dropping a byte and appending a null-terminator to the end.

    constexpr size_t minimumSize{1u};

    if (originalSize < minimumSize)
        throw RuntimeException{"The buffer's minimum size must be greater than or equal to 1", RuntimeException::USAGE_ERROR};

    if (minimumSeedIndex > originalSize - 1u)
        throw RuntimeException{"Minimum seed index is out of bounds", RuntimeException::INDEX_OUT_OF_RANGE};

    if (originalBuffer == nullptr)
        throw RuntimeException{"Input buffer is null", RuntimeException::UNEXPECTED_ERROR};

    // The new buffer will contain one less byte, but a null-terminator will be appended to the end; therefore, the sizes will be equal.

    const size_t newBufferSize{originalSize};

    // Allocate the new buffer and set it's elements to zero.

    char* newBuffer{newEntry->allocateBuffer(testCaseKey, newBufferSize)};
    memset(newBuffer, 0u, newBufferSize);

    // Select a random byte to drop from the original buffer.

    const size_t lower{0u};
    const size_t upper{originalSize - 1u};
    const size_t maximumRandomIndexValue{originalSize - minimumSeedIndex};
    const size_t randomIndexToDrop{
                            std::clamp(
                                    GetRandomValueWithinBounds(
                                                        lower,
                                                        maximumRandomIndexValue) + minimumSeedIndex,
                                                        lower,
                                                        upper)};

    // Copy data from the original buffer into the new buffer, but exclude the random byte.
    // The last element in the new buffer is skipped since it was implicitly set to zero during allocation.
    
    for (size_t sourceIndex{0u}, destinationIndex{0u}; sourceIndex < originalSize; ++sourceIndex)
    {
        if (sourceIndex != randomIndexToDrop)
        {
            newBuffer[destinationIndex] = originalBuffer[sourceIndex];

            ++destinationIndex;
        }
    }
}

void vmf::radamsa::mutations::ByteMutations::FlipByte(
                                                    StorageEntry* newEntry,
                                                    const size_t originalSize,
                                                    const char* originalBuffer,
                                                    const size_t minimumSeedIndex,
                                                    const int testCaseKey)
{
    // Consume the original buffer by flipping a byte and appending a null-terminator to the end.

    constexpr size_t minimumSize{1u};

    if (originalSize < minimumSize)
        throw RuntimeException{"The buffer's minimum size must be greater than or equal to 1", RuntimeException::USAGE_ERROR};

    if (minimumSeedIndex > originalSize - 1u)
        throw RuntimeException{"Minimum seed index is out of bounds", RuntimeException::INDEX_OUT_OF_RANGE};

    if (originalBuffer == nullptr)
        throw RuntimeException{"Input buffer is null", RuntimeException::UNEXPECTED_ERROR};

    // The new buffer size will contain one additional element since we are appending a null-terminator to the end.

    const size_t newBufferSize{originalSize + 1u};

    // Allocate the new buffer, set it's elements to those of the original buffer, and append a null-terminator to the end.

    char* newBuffer{newEntry->allocateBuffer(testCaseKey, static_cast<int>(newBufferSize))};
    memset(newBuffer, 0u, newBufferSize);
    memcpy(newBuffer, originalBuffer, originalSize);

    // Select a random byte to drop from the original buffer.

    const size_t lower{0u};
    const size_t upper{originalSize - 1u};
    const size_t maximumRandomIndexValue{originalSize - minimumSeedIndex};
    const size_t randomIndexToFlip{
                            std::clamp(
                                    GetRandomValueWithinBounds(
                                                        lower,
                                                        maximumRandomIndexValue) + minimumSeedIndex,
                                                        lower,
                                                        upper)};

    // Select a random bit to flip from the random byte.
    // When computing the random bit shift,
    // we add 1 so that a maximum number of 8 bit shift operations can be performed against a char containing the value 0x01.

    const size_t randomBitShift{GetRandomValueWithinBounds(0u, std::numeric_limits<char>::digits + 1u)};
    const char randomMaskedBit{static_cast<char>(0x01u << randomBitShift)};

    // Flip the random byte by performing an XOR operation with a random masked bit.

    newBuffer[randomIndexToFlip] ^= randomMaskedBit;
}

void vmf::radamsa::mutations::ByteMutations::InsertByte(
                                                    StorageEntry* newEntry,
                                                    const size_t originalSize,
                                                    const char* originalBuffer,
                                                    const size_t minimumSeedIndex,
                                                    const int testCaseKey)
{
    // Consume the original buffer by inserting a byte and appending a null-terminator to the end.

    constexpr size_t minimumSize{1u};

    if (originalSize < minimumSize)
        throw RuntimeException{"The buffer's minimum size must be greater than or equal to 1", RuntimeException::USAGE_ERROR};

    if (minimumSeedIndex > originalSize - 1u)
        throw RuntimeException{"Minimum seed index is out of bounds", RuntimeException::INDEX_OUT_OF_RANGE};

    if (originalBuffer == nullptr)
        throw RuntimeException{"Input buffer is null", RuntimeException::UNEXPECTED_ERROR};

    // The new buffer size will contain two additional elements since we are inserting a random byte and appending a null-terminator to the end.

    const size_t newBufferSize{originalSize + 2u};

    // Allocate the new buffer and set it's elements to zero.

    char* newBuffer{newEntry->allocateBuffer(testCaseKey, static_cast<int>(newBufferSize))};
    memset(newBuffer, 0u, newBufferSize);

    // Select a random index from which the new byte will be inserted.

    const size_t lower{0u};
    const size_t upper{originalSize - 1u};
    const size_t maximumRandomIndexValue{originalSize - minimumSeedIndex};
    const size_t randomInsertionIndex{
                                std::clamp(
                                        GetRandomValueWithinBounds(
                                                                lower,
                                                                maximumRandomIndexValue) + minimumSeedIndex,
                                                                lower,
                                                                upper)};

    // Copy data from the original buffer into the new buffer, but insert a random byte.
    // The last element in the new buffer is skipped since it was implicitly set to zero during allocation.

    for (size_t sourceIndex{0u}, destinationIndex{0u}; sourceIndex < originalSize; ++sourceIndex)
    {
        newBuffer[destinationIndex] = originalBuffer[sourceIndex];

        if (sourceIndex == randomInsertionIndex)
            newBuffer[++destinationIndex] = static_cast<char>(GetRandomValueWithinBounds(0u, std::numeric_limits<char>::max()));

        ++destinationIndex;
    }
}

void vmf::radamsa::mutations::ByteMutations::RepeatByte(
                                                    StorageEntry* newEntry,
                                                    const size_t originalSize,
                                                    const char* originalBuffer,
                                                    const size_t minimumSeedIndex,
                                                    const int testCaseKey)
{
    // Consume the original buffer by repeating a byte a random number of times and appending a null-terminator to the end.

    constexpr size_t minimumSize{1u};

    if (originalSize < minimumSize)
        throw RuntimeException{"The buffer's minimum size must be greater than or equal to 1", RuntimeException::USAGE_ERROR};

    if (minimumSeedIndex > originalSize - 1u)
        throw RuntimeException{"Minimum seed index is out of bounds", RuntimeException::INDEX_OUT_OF_RANGE};

    if (originalBuffer == nullptr)
        throw RuntimeException{"Input buffer is null", RuntimeException::UNEXPECTED_ERROR};

    // The new buffer size will contain a random number of additional elements since we are repeating a random byte.
    // Furthermore, it will contain one more element since we are appending a null-terminator to the end.

    const size_t numberOfRandomByteRepetitions{GetRandomByteRepetitionLength()};
    const size_t newBufferSize{originalSize + numberOfRandomByteRepetitions + 1u};

    // Allocate the new buffer and set it's elements to zero.

    char* newBuffer{newEntry->allocateBuffer(testCaseKey, static_cast<int>(newBufferSize))};
    memset(newBuffer, 0u, newBufferSize);

    // Select a random index from which the new bytes will be repeated.

    const size_t lower{0u};
    const size_t upper{originalSize - 1u};
    const size_t maximumRandomIndexValue{originalSize - minimumSeedIndex};
    const size_t randomByteRepetitionIndex{
                                    std::clamp(
                                            GetRandomValueWithinBounds(
                                                                    lower,
                                                                    maximumRandomIndexValue) + minimumSeedIndex,
                                                                    lower,
                                                                    upper)};

    // Copy data from the original buffer into the new buffer, but repeat the target byte.
    // The last element in the new buffer is skipped since it was implicitly set to zero during allocation.

    for (size_t sourceIndex{0u}, destinationIndex{0u}; sourceIndex < originalSize; ++sourceIndex)
    {
        if (sourceIndex == randomByteRepetitionIndex)
        {
            memset(&newBuffer[destinationIndex], originalBuffer[sourceIndex], numberOfRandomByteRepetitions + 1u);

            ++destinationIndex += numberOfRandomByteRepetitions;
        }
        else
        {
            newBuffer[destinationIndex] = originalBuffer[sourceIndex];

            ++destinationIndex;
        }
    }
}

void vmf::radamsa::mutations::ByteMutations::PermuteByte(
                                                    StorageEntry* newEntry,
                                                    const size_t originalSize,
                                                    const char* originalBuffer,
                                                    const size_t minimumSeedIndex,
                                                    const int testCaseKey)
{
    // Consume the original buffer by rearranging a random number of bytes and appending a null-terminator to the end.

    constexpr size_t minimumSize{1u};

    if (originalSize < minimumSize)
        throw RuntimeException{"The buffer's minimum size must be greater than or equal to 1", RuntimeException::USAGE_ERROR};

    if (minimumSeedIndex > originalSize - 1u)
        throw RuntimeException{"Minimum seed index is out of bounds", RuntimeException::INDEX_OUT_OF_RANGE};

    if (originalBuffer == nullptr)
        throw RuntimeException{"Input buffer is null", RuntimeException::UNEXPECTED_ERROR};

    // The new buffer size will contain one additional element since we are appending a null-terminator to the end.

    const size_t newBufferSize{originalSize + 1u};

    // Allocate the new buffer, set it's elements to those of the original buffer, and append a null-terminator to the end.

    char* newBuffer{newEntry->allocateBuffer(testCaseKey, static_cast<int>(newBufferSize))};
    memset(newBuffer, 0u, newBufferSize);
    memcpy(newBuffer, originalBuffer, originalSize);

    // Copy data from the original buffer into the new buffer, but swap random bytes.
    // The last element in the new buffer is skipped since it was implicitly set to zero during allocation.

    for (size_t sourceIndex{minimumSeedIndex}; sourceIndex < originalSize; ++sourceIndex)
    {
        // Select a random index and swap the two bytes.

        const size_t lower{0u};
        const size_t upper{originalSize - 1u};
        const size_t maximumRandomIndexValue{originalSize - minimumSeedIndex};
        const size_t randomIndexToSwap{
                                    std::clamp(
                                            GetRandomValueWithinBounds(
                                                                    lower,
                                                                    maximumRandomIndexValue) + minimumSeedIndex,
                                                                    lower,
                                                                    upper)};

        const char sourceByte{newBuffer[sourceIndex]};
        const char swappedByte{newBuffer[randomIndexToSwap]};

        newBuffer[sourceIndex] = swappedByte;
        newBuffer[randomIndexToSwap] = sourceByte;
    }
}

void vmf::radamsa::mutations::ByteMutations::IncrementByte(
                                                        StorageEntry* newEntry,
                                                        const size_t originalSize,
                                                        const char* originalBuffer,
                                                        const size_t minimumSeedIndex,
                                                        const int testCaseKey)
{
    // Consume the original buffer by incrementing a random byte and appending a null-terminator to the end.

    constexpr size_t minimumSize{1u};

    if (originalSize < minimumSize)
        throw RuntimeException{"The buffer's minimum size must be greater than or equal to 1", RuntimeException::USAGE_ERROR};

    if (minimumSeedIndex > originalSize - 1u)
        throw RuntimeException{"Minimum seed index is out of bounds", RuntimeException::INDEX_OUT_OF_RANGE};

    if (originalBuffer == nullptr)
        throw RuntimeException{"Input buffer is null", RuntimeException::UNEXPECTED_ERROR};

    // The new buffer size will contain one additional element since we are appending a null-terminator to the end.

    const size_t newBufferSize{originalSize + 1u};

    // Allocate the new buffer, set it's elements to those of the original buffer, and append a null-terminator to the end.

    char* newBuffer{newEntry->allocateBuffer(testCaseKey, static_cast<int>(newBufferSize))};
    memset(newBuffer, 0u, newBufferSize);
    memcpy(newBuffer, originalBuffer, originalSize);

    // Select a random byte to circularly increment.

    const size_t lower{0u};
    const size_t upper{originalSize - 1u};
    const size_t maximumRandomIndexValue{originalSize - minimumSeedIndex};
    const size_t randomIndexToIncrement{
                                    std::clamp(
                                            GetRandomValueWithinBounds(
                                                                    lower,
                                                                    maximumRandomIndexValue) + minimumSeedIndex,
                                                                    lower,
                                                                    upper)};

    newBuffer[randomIndexToIncrement] = static_cast<char>((originalBuffer[randomIndexToIncrement] + 0x01u) % std::numeric_limits<char>::max());
}

void vmf::radamsa::mutations::ByteMutations::DecrementByte(
                                                        StorageEntry* newEntry,
                                                        const size_t originalSize,
                                                        const char* originalBuffer,
                                                        const size_t minimumSeedIndex,
                                                        const int testCaseKey)
{
    // Consume the original buffer by decrementing a random byte and appending a null-terminator to the end.

    constexpr size_t minimumSize{1u};

    if (originalSize < minimumSize)
        throw RuntimeException{"The buffer's minimum size must be greater than or equal to 1", RuntimeException::USAGE_ERROR};

    if (minimumSeedIndex > originalSize - 1u)
        throw RuntimeException{"Minimum seed index is out of bounds", RuntimeException::INDEX_OUT_OF_RANGE};

    if (originalBuffer == nullptr)
        throw RuntimeException{"Input buffer is null", RuntimeException::UNEXPECTED_ERROR};

    // The new buffer size will contain one additional element since we are appending a null-terminator to the end.

    const size_t newBufferSize{originalSize + 1u};

    // Allocate the new buffer, set it's elements to those of the original buffer, and append a null-terminator to the end.

    char* newBuffer{newEntry->allocateBuffer(testCaseKey, static_cast<int>(newBufferSize))};
    memset(newBuffer, 0u, newBufferSize);
    memcpy(newBuffer, originalBuffer, originalSize);

    // Select a random byte to circularly decrement.

    const size_t lower{0u};
    const size_t upper{originalSize - 1u};
    const size_t maximumRandomIndexValue{originalSize - minimumSeedIndex};
    const size_t randomIndexToDecrement{
                                    std::clamp(
                                            GetRandomValueWithinBounds(
                                                                    lower,
                                                                    maximumRandomIndexValue) + minimumSeedIndex,
                                                                    lower,
                                                                    upper)};

    newBuffer[randomIndexToDecrement] = static_cast<char>((originalBuffer[randomIndexToDecrement] - 0x01u) % std::numeric_limits<char>::max());
}

void vmf::radamsa::mutations::ByteMutations::RandomizeByte(
                                                        StorageEntry* newEntry,
                                                        const size_t originalSize,
                                                        const char* originalBuffer,
                                                        const size_t minimumSeedIndex,
                                                        const int testCaseKey)
{
    // Consume the original buffer by randomizing a random byte and appending a null-terminator to the end.

    constexpr size_t minimumSize{1u};

    if (originalSize < minimumSize)
        throw RuntimeException{"The buffer's minimum size must be greater than or equal to 1", RuntimeException::USAGE_ERROR};

    if (minimumSeedIndex > originalSize - 1u)
        throw RuntimeException{"Minimum seed index is out of bounds", RuntimeException::INDEX_OUT_OF_RANGE};

    if (originalBuffer == nullptr)
        throw RuntimeException{"Input buffer is null", RuntimeException::UNEXPECTED_ERROR};

    // The new buffer size will contain one additional element since we are appending a null-terminator to the end.

    const size_t newBufferSize{originalSize + 1u};

    // Allocate the new buffer, set it's elements to those of the original buffer, and append a null-terminator to the end.

    char* newBuffer{newEntry->allocateBuffer(testCaseKey, static_cast<int>(newBufferSize))};
    memset(newBuffer, 0u, newBufferSize);
    memcpy(newBuffer, originalBuffer, originalSize);

    // Select a random byte to randomize

    const size_t lower{0u};
    const size_t upper{originalSize - 1u};
    const size_t maximumRandomIndexValue{originalSize - minimumSeedIndex};
    const size_t randomIndexToRandomize{
                                    std::clamp(
                                            GetRandomValueWithinBounds(
                                                                    lower,
                                                                    maximumRandomIndexValue) + minimumSeedIndex,
                                                                    lower,
                                                                    upper)};

    newBuffer[randomIndexToRandomize] = static_cast<char>(GetRandomValueWithinBounds(0u, std::numeric_limits<char>::max()));
}
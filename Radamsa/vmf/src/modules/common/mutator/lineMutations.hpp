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
#pragma once

// C/C++ Includes
#include <memory>
#include <vector>

// Module Includes

#include "mutationBase.hpp"

// Common Includes

#include "StorageEntry.hpp"
#include "RuntimeException.hpp"


namespace vmf::radamsa::mutations
{
/**
 * @brief This module is draws heavily upon the libAFL mutator.c
 * 
 * Uses the specified AFL-style mutation algorithm to mutate the provided
 * input.  createTestCase is the main mutation method.
 *
 * See https://github.com/AFLplusplus/LibAFL-legacy/blob/dev/src/mutator.c
 * 
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
class LineMutations: public vmf::radamsa::mutations::MutationBase
{
public:
    struct Line
    {
        Line() = default;
        ~Line() = default;

        Line(Line&&) = default;
        Line(const Line&) = default;

        Line& operator=(Line&&) = default;
        Line& operator=(const Line&) = default;

        bool operator==(const Line &other) const { return (IsValid == other.IsValid && StartIndex == other.StartIndex && Size == other.Size); }
        bool operator!=(const Line &other) const { return !(*this == other); }

        bool IsValid{false};
        size_t StartIndex{0u};
        size_t Size{0u};
    };

    struct LineVector
    {
        ~LineVector() = default;
        LineVector() = default;

        LineVector(
            const char* const buffer,
            const Line& lineData)
        {
            Data = std::make_unique<char[]>(lineData.Size);
            memcpy(Data.get(), &buffer[lineData.StartIndex], lineData.Size);

            Size = lineData.Size;
        }

        LineVector(const LineVector &other) noexcept
        {
            // Copy Data

            const size_t& size{other.Size};

            Data = std::make_unique<char[]>(size);
            memcpy(Data.get(), other.Data.get(), size);

            Size = size;
        }

        LineVector(LineVector&& other) noexcept
        {
            // Copy Data

            const size_t& size{other.Size};

            Data = std::make_unique<char[]>(size);
            memcpy(Data.get(), other.Data.get(), size);

            Size = size;

            // Release ownership

            other.Data.release();
            other.Size = 0u;
        }

        LineVector& operator=(const LineVector& other)
        {
            // Copy Data

            const size_t& size{other.Size};

            Data = std::make_unique<char[]>(size);
            memcpy(Data.get(), other.Data.get(), size);

            Size = size;

            return *this;
        }

        LineVector& operator=(LineVector&& other)
        {
            // Copy Data

            const size_t& size{other.Size};

            Data = std::make_unique<char[]>(size);
            memcpy(Data.get(), other.Data.get(), size);

            Size = size;

            // Release ownership

            other.Data.release();
            other.Size = 0u;

            return *this;
        }

        bool operator==(const LineVector &other) const { return (Size == other.Size && (memcmp(Data.get(), other.Data.get(), other.Size) == 0)); }

        bool operator!=(const LineVector &other) const { return !(*this == other); }

        std::unique_ptr<char[]> Data{nullptr};
        size_t Size{0u};
    };

    struct LineList
    {
        ~LineList() = default;
        LineList() = default;

        LineList(
            const char* const buffer,
            const std::vector<Line>& lineData) noexcept
        {
            const size_t numberOfElements{lineData.size()};

            auto data{std::make_unique<LineVector[]>(numberOfElements)};

            for(size_t it{0u}; it < numberOfElements; ++it)
            {
                const Line& line{lineData.at(it)};

                data[it] = std::move(
                                LineVector{
                                        buffer,
                                        line});

                Capacity += line.Size;
            }

            NumberOfElements = numberOfElements;
            Data = std::move(data);
        }

        LineList(const LineList& other) noexcept
        {
            // Copy Data

            const size_t& numberOfElements{other.NumberOfElements};

            NumberOfElements = numberOfElements;
            Capacity = other.Capacity;

            Data = std::make_unique<LineVector[]>(numberOfElements);

            for (size_t it{0u}; it < numberOfElements; ++it)
                Data[it] = other.Data[it];
        }

        LineList(LineList&& other) noexcept
        {
            // Copy Data

            const size_t& numberOfElements{other.NumberOfElements};

            NumberOfElements = numberOfElements;
            Capacity = other.Capacity;

            Data = std::make_unique<LineVector[]>(numberOfElements);
            //memcpy(Data.get(), other.Data.get(), numberOfElements); //not legal
            int count = numberOfElements;
            for(int i=0; i<count; i++)
            {
                Data[i] = other.Data[i];
            }


            // Release ownership

            other.Data.release();
            other.Capacity = 0u;
            other.NumberOfElements = 0u;
        }

        LineList& operator=(const LineList& other)
        {
            // Copy Data

            const size_t& numberOfElements{other.NumberOfElements};

            NumberOfElements = numberOfElements;
            Capacity = other.Capacity;

            Data = std::make_unique<LineVector[]>(numberOfElements);
            //memcpy(Data.get(), other.Data.get(), numberOfElements); //not legal
            int count = numberOfElements;
            for(int i=0; i<count; i++)
            {
                Data[i] = other.Data[i];
            }

            return *this;
        }

        LineList& operator=(LineList&& other)
        {
            // Copy Data

            const size_t& numberOfElements{other.NumberOfElements};

            NumberOfElements = numberOfElements;
            Capacity = other.Capacity;

            Data = std::make_unique<LineVector[]>(numberOfElements);
            //memcpy(Data.get(), other.Data.get(), numberOfElements); //not legal
            int count = numberOfElements;
            for(int i=0; i<count; i++)
            {
                Data[i] = other.Data[i];
            }

            // Release ownership

            other.Data.release();
            other.Capacity = 0u;
            other.NumberOfElements = 0u;

            return *this;
        }

        bool operator==(const LineList& other) const
        {
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

            return ((NumberOfElements == other.NumberOfElements) &&
                    (Capacity == other.Capacity) &&
                    (compareLineVectors(Data.get(), other.Data.get())));
        }

        bool operator!=(const LineList& other) const { return !(*this == other); }

        std::unique_ptr<LineVector[]> Data{nullptr};
        size_t NumberOfElements{0u};
        size_t Capacity{0u};
    };

    LineMutations() = delete;
    virtual ~LineMutations() = default;

    void DeleteLine(
                StorageEntry* newEntry,
                const size_t originalSize,
                const char* originalBuffer,
                const size_t characterIndex,
                const int testCaseKey);
  
    void DeleteSequentialLines(
                            StorageEntry* newEntry,
                            const size_t originalSize,
                            const char* originalBuffer,
                            const size_t characterIndex,
                            const int testCaseKey);

    void DuplicateLine(
                    StorageEntry* newEntry,
                    const size_t originalSize,
                    const char* originalBuffer,
                    const size_t characterIndex,
                    const int testCaseKey);

    void CopyLineCloseBy(
                    StorageEntry* newEntry,
                    const size_t originalSize,
                    const char* originalBuffer,
                    const size_t characterIndex,
                    const int testCaseKey);

    void RepeatLine(
                StorageEntry* newEntry,
                const size_t originalSize,
                const char* originalBuffer,
                const size_t characterIndex,
                const int testCaseKey);

    void SwapLine(
            StorageEntry* newEntry,
            const size_t originalSize,
            const char* originalBuffer,
            const size_t characterIndex,
            const int testCaseKey);

protected:
    LineMutations(std::default_random_engine& randomNumberGenerator) : MutationBase{randomNumberGenerator} {}

    Line GetLineData(
                const char* const buffer,
                const size_t size,
                const size_t lineIndex,
                const size_t numberOfLinesAfterIndex);

    bool IsBinarish(
                const char* const buffer,
                const size_t size);

    size_t GetNumberOfLinesAfterIndex(
                                const char* const buffer,
                                const size_t size,
                                const size_t index);

    size_t GetRandomLogValue(const size_t maximumValue);

    size_t GetRandomN_Bit(const size_t n);

private:
    // Experimental and to be implemented in the next release cycle.

    void PermuteLine(
                StorageEntry* newEntry,
                const size_t originalSize,
                const char* originalBuffer,
                const size_t characterIndex,
                const int testCaseKey);

    bool Rad_LineInsElsewhere(const size_t index);

    bool Rad_LineReplaceElsewhere(const size_t index);
};
}
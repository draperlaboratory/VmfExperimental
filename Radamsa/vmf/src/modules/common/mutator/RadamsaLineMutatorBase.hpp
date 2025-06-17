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

#pragma once

#include "RadamsaMutatorBase.hpp"
#include "VmfRand.hpp"

namespace vmf
{
/**
 *
 */
class RadamsaLineMutatorBase: public RadamsaMutatorBase
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

        bool operator==(const Line &other) const { 
            return (IsValid == other.IsValid && 
                    StartIndex == other.StartIndex && 
                    Size == other.Size); 
        }
        bool operator!=(const Line &other) const { return !(*this == other); } // we may want to change this to test for equality instead of identity

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

        bool operator==(const LineVector &other) const { 
            return (Size == other.Size && 
                    (memcmp(Data.get(), other.Data.get(), other.Size) == 0)); 
        }

        bool operator!=(const LineVector &other) const { return !(*this == other); } // we may want to change this to test for equality instead of identity

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

                data[it] = std::move(LineVector{buffer,line});

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
            {
                Data[it] = other.Data[it];
            }
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
                }
            };

            return ((NumberOfElements == other.NumberOfElements) &&
                    (Capacity == other.Capacity) &&
                    (compareLineVectors(Data.get(), other.Data.get())));
        }

        bool operator!=(const LineList& other) const { return !(*this == other); }

        std::unique_ptr<LineVector[]> Data{nullptr};
        size_t NumberOfElements{0u};
        size_t Capacity{0u};
    };

    RadamsaLineMutatorBase() = default;
    virtual ~RadamsaLineMutatorBase() = default;

    Line GetLineData(
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

    size_t GetNumberOfLinesAfterIndex(
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

        return numberOfLines;
    }

    bool IsBinarish(
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

    size_t GetRandomLogValue(const size_t maximumValue, VmfRand* rand)
    {
        constexpr size_t minimumValue{2u};

        if(maximumValue <= minimumValue)
            return 0u;

        return GetRandomN_Bit(
                            rand->randBetween(0u, maximumValue - minimumValue) + minimumValue,
                            rand);
    }

    size_t GetRandomN_Bit(const size_t n, VmfRand* rand)
    {
        const size_t highValue{(n - 1u) << 1u};
        const size_t randomValue{rand->randBetween(0u, highValue)};
        const size_t nBitValue{randomValue | highValue};

        return nBitValue;
    }
};
}

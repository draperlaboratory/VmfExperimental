/* =============================================================================
 * Vader Modular Fuzzer (VMF)
 * Copyright (c) 2021-2024 The Charles Stark Draper Laboratory, Inc.
 * <vmf@draper.com>
 *  
 * Effort sponsored by the U.S. Government under Other Transaction number
 * W9124P-19-9-0001 between AMTC and the Government. The U.S. Government
 * Is authorized to reproduce and distribute reprints for Governmental purposes
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
 /**
  *
  */
#include "RadamsaRepeatLineMutator.hpp"
#include "RuntimeException.hpp"
#include <random>
#include <algorithm>

using namespace vmf;

#include "ModuleFactory.hpp"
REGISTER_MODULE(RadamsaRepeatLineMutator);

/**
 * @brief Builder method to support the ModuleFactory
 * Constructs an instance of this class
 * @return Module* - Pointer to the newly created instance
 */
Module* RadamsaRepeatLineMutator::build(std::string name)
{
    return new RadamsaRepeatLineMutator(name);
}

/**
 * @brief Initialization method
 *
 * @param config - Configuration object
 */
void RadamsaRepeatLineMutator::init(ConfigInterface& config)
{

}

/**
 * @brief Construct a new RadamsaRepeatLineMutator::RadamsaRepeatLineMutator object
 *
 * @param name The of the name module
 */
RadamsaRepeatLineMutator::RadamsaRepeatLineMutator(std::string name) : MutatorModule(name)
{
    // rand.randInit();
}

/**
 * @brief Destroy the RadamsaRepeatLineMutator::RadamsaRepeatLineMutator object
 *
 */
RadamsaRepeatLineMutator::~RadamsaRepeatLineMutator()
{

}

/**
 * @brief Register the storage needs for this module
 *
 * @param registry - StorageRegistry object
 */
void RadamsaRepeatLineMutator::registerStorageNeeds(StorageRegistry& registry)
{
    // This module does not register for a test case buffer key, because mutators are told which buffer to write in storage
    // by the input generator that calls them
}

void RadamsaRepeatLineMutator::mutateTestCase(StorageModule& storage, StorageEntry* baseEntry, StorageEntry* newEntry, int testCaseKey)
{
    // Consume the original buffer by repeating a random line multiple times and appending a null-terminator to the end.

    constexpr size_t minimumSize{1u};
    const size_t minimumSeedIndex{0u};
    const size_t characterIndex{0u};
    const size_t originalSize = baseEntry->getBufferSize(testCaseKey);
    char* originalBuffer = baseEntry->getBufferPointer(testCaseKey);

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

    // Select a random line to duplicate.

    constexpr size_t minimumRandomLineIndex{0u};
    const size_t maximumRandomLineIndex{numberOfLinesAfterIndex - 1u};

    const size_t randomLineIndex{
                            rand->randBetween(
                                            minimumRandomLineIndex,
                                            maximumRandomLineIndex)};

    const Line lineData{
                    GetLineData(
                            originalBuffer,
                            originalSize,
                            randomLineIndex,
                            numberOfLinesAfterIndex)};

    const size_t numberOfRandomLineRepetitions{GetRandomRepetitionLength(this->rand)};

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
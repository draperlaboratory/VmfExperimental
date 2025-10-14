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
#include "RadamsaInsertLineMutator.hpp"
#include "RuntimeException.hpp"
#include <random>
#include <algorithm>

using namespace vmf;

#include "ModuleFactory.hpp"
REGISTER_MODULE(RadamsaInsertLineMutator);

/**
 * @brief Builder method to support the ModuleFactory
 * Constructs an instance of this class
 * @return Module* - Pointer to the newly created instance
 */
Module* RadamsaInsertLineMutator::build(std::string name)
{
    return new RadamsaInsertLineMutator(name);
}

/**
 * @brief Initialization method
 *
 * @param config - Configuration object
 */
void RadamsaInsertLineMutator::init(ConfigInterface& config)
{

}

/**
 * @brief Construct a new RadamsaInsertLineFromElsewhereMutator::RadamsaInsertLineFromElsewhereMutator object
 *
 * @param name The of the name module
 */
RadamsaInsertLineMutator::RadamsaInsertLineMutator(std::string name) : MutatorModule(name)
{
    // rand->randInit();
}

/**
 * @brief Destroy the RadamsaInsertLineFromElsewhereMutator::RadamsaInsertLineFromElsewhereMutator object
 *
 */
RadamsaInsertLineMutator::~RadamsaInsertLineMutator()
{

}

/**
 * @brief Register the storage needs for this module
 *
 * @param registry - StorageRegistry object
 */
void RadamsaInsertLineMutator::registerStorageNeeds(StorageRegistry& registry)
{
    // This module does not register for a test case buffer key, because mutators are told which buffer to write in storage
    // by the input generator that calls them
}

void RadamsaInsertLineMutator::mutateTestCase(StorageModule& storage, StorageEntry* baseEntry, StorageEntry* newEntry, int testCaseKey)
{
    // Insert a random existing line into a random place

    const size_t minimumSize{2};   // minimal case consists of two newlines
    const size_t minimumLines{2};
    const size_t minimumSeedIndex{0u};
    const size_t characterIndex{0u};
    const size_t originalSize = baseEntry->getBufferSize(testCaseKey);
    char* originalBuffer = baseEntry->getBufferPointer(testCaseKey);

    const size_t numLines{
                    GetNumberOfLinesAfterIndex(
                                        originalBuffer,
                                        originalSize,
                                        characterIndex)};

    if (originalSize < minimumSize)
        throw RuntimeException{"The buffer's minimum size must be greater than or equal to 2", RuntimeException::USAGE_ERROR};

    if (minimumSeedIndex > originalSize - 1u)
        throw RuntimeException{"Minimum seed index is out of bounds", RuntimeException::INDEX_OUT_OF_RANGE};

    if (originalBuffer == nullptr)
        throw RuntimeException{"Input buffer is null", RuntimeException::UNEXPECTED_ERROR};

    if (numLines < minimumLines) {
        throw RuntimeException{"The buffer's minimum number of lines must be greater than or equal to 2", RuntimeException::USAGE_ERROR};
    }

    std::vector<size_t> lineOrder(numLines);
    std::vector<Line> lines(numLines);
    for(size_t i{0}; i < numLines; ++i) {
        lineOrder[i] = i;
        lines[i] = GetLineData(
                            originalBuffer,
                            originalSize,
                            i,
                            numLines);
    }

    const size_t original_lineIndex = this->rand->randBetween(characterIndex, numLines - 1);
    const size_t new_lineIndex = this->rand->randBetween(characterIndex, numLines);

    lineOrder.insert(lineOrder.begin() + new_lineIndex, original_lineIndex);

    // create new buffer with modified order
    const size_t newBufferSize{originalSize + lines[original_lineIndex].Size + 1u};  // +1 to implicitly append null terminator
    char* newBuffer{newEntry->allocateBuffer(testCaseKey, static_cast<int>(newBufferSize))};
    memset(newBuffer, 0u, newBufferSize);
    for(
        size_t i{0}, nextBufferIndex{0}; 
        i < lineOrder.size(); 
        nextBufferIndex += lines[lineOrder[i]].Size, ++i
    ) {
        memcpy(
            newBuffer + nextBufferIndex, 
            originalBuffer + lines[lineOrder[i]].StartIndex, 
            lines[lineOrder[i]].Size
        );
    }
}
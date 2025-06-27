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
#include "RadamsaRepeatByteSequenceMutator.hpp"
#include "RuntimeException.hpp"
#include <random>
#include <algorithm>

using namespace vmf;

#include "ModuleFactory.hpp"
REGISTER_MODULE(RadamsaRepeatByteSequenceMutator);

/**
 * @brief Builder method to support the ModuleFactory
 * Constructs an instance of this class
 * @return Module* - Pointer to the newly created instance
 */
Module* RadamsaRepeatByteSequenceMutator::build(std::string name)
{
    return new RadamsaRepeatByteSequenceMutator(name);
}

/**
 * @brief Initialization method
 *
 * @param config - Configuration object
 */
void RadamsaRepeatByteSequenceMutator::init(ConfigInterface& config)
{

}

/**
 * @brief Construct a new RadamsaRepeatByteSequenceMutator::RadamsaRepeatByteSequenceMutator object
 *
 * @param name The of the name module
 */
RadamsaRepeatByteSequenceMutator::RadamsaRepeatByteSequenceMutator(std::string name) : MutatorModule(name)
{
    // rand->randInit();
}

/**
 * @brief Destroy the RadamsaRepeatByteSequenceMutator::RadamsaRepeatByteSequenceMutator object
 *
 */
RadamsaRepeatByteSequenceMutator::~RadamsaRepeatByteSequenceMutator()
{

}

/**
 * @brief Register the storage needs for this module
 *
 * @param registry - StorageRegistry object
 */
void RadamsaRepeatByteSequenceMutator::registerStorageNeeds(StorageRegistry& registry)
{
    // This module does not register for a test case buffer key, because mutators are told which buffer to write in storage
    // by the input generator that calls them
}

void RadamsaRepeatByteSequenceMutator::mutateTestCase(StorageModule& storage, StorageEntry* baseEntry, StorageEntry* newEntry, int testCaseKey)
{
    // select a random number of consecutive bytes and repeat them a random number of times

    constexpr size_t minimumSize{2u};
    const size_t minimumSeedIndex{0u};
    const size_t originalSize = baseEntry->getBufferSize(testCaseKey);
    char* originalBuffer = baseEntry->getBufferPointer(testCaseKey);

    if (originalSize < minimumSize)
        throw RuntimeException{"The buffer's minimum size must be greater than or equal to 2", RuntimeException::USAGE_ERROR};

    if (minimumSeedIndex > originalSize - 1u)
        throw RuntimeException{"Minimum seed index is out of bounds", RuntimeException::INDEX_OUT_OF_RANGE};

    if (originalBuffer == nullptr)
        throw RuntimeException{"Input buffer is null", RuntimeException::UNEXPECTED_ERROR};

    

    // Select random indexes for the start and end of the sequence
    const size_t start_lower{0u};
    const size_t start_upper{originalSize - 1u - 1u}; // additional -1 to leave at least one byte at the end
    const size_t start_index{rand->randBetween(start_lower, start_upper)};

    const size_t end_lower{start_index + 1u};
    const size_t end_upper{originalSize - 1u};
    const size_t end_index{rand->randBetween(end_lower, end_upper)};

    // Get random number of sequence repetitions
    const size_t numberOfRepetitions{GetRandomRepetitionLength(rand)};

    // Calculate the size of the modified buffer
    const size_t seq_len{end_index - start_index + 1u};
    const size_t newBufferSize{originalSize + (seq_len * numberOfRepetitions) + 1u}; // +1 because we're appending a null-terminator

    // Allocate the new buffer and set it's elements to zero.
    char* newBuffer{newEntry->allocateBuffer(testCaseKey, static_cast<int>(newBufferSize))};
    memset(newBuffer, 0u, newBufferSize);

    // Copy pre-sequence into modified buffer
    memcpy(newBuffer, originalBuffer, start_index);

    // Copy post-sequence into modified buffer
    memcpy(
        newBuffer, 
        originalBuffer + start_index + (seq_len * numberOfRepetitions), 
        originalSize - end_index - 1u
    );

    // Fill the rest with the byte sequence
    for (size_t i = 1; i < numberOfRepetitions; ++i) {
        memcpy(
            newBuffer + start_index + (i * seq_len), 
            originalBuffer + start_index, 
            seq_len
        );
    }
}
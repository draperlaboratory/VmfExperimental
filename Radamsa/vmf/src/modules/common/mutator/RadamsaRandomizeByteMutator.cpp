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
#include "RadamsaRandomizeByteMutator.hpp"
#include "RuntimeException.hpp"
#include <random>
#include <algorithm>

using namespace vmf;

#include "ModuleFactory.hpp"
REGISTER_MODULE(RadamsaRandomizeByteMutator);

/**
 * @brief Builder method to support the ModuleFactory
 * Constructs an instance of this class
 * @return Module* - Pointer to the newly created instance
 */
Module* RadamsaRandomizeByteMutator::build(std::string name)
{
    return new RadamsaRandomizeByteMutator(name);
}

/**
 * @brief Initialization method
 *
 * @param config - Configuration object
 */
void RadamsaRandomizeByteMutator::init(ConfigInterface& config)
{

}

/**
 * @brief Construct a new RadamsaRandomizeByteMutator::RadamsaRandomizeByteMutator object
 *
 * @param name The of the name module
 */
RadamsaRandomizeByteMutator::RadamsaRandomizeByteMutator(std::string name) : MutatorModule(name)
{
    // rand->randInit();
}

/**
 * @brief Destroy the RadamsaRandomizeByteMutator::RadamsaRandomizeByteMutator object
 *
 */
RadamsaRandomizeByteMutator::~RadamsaRandomizeByteMutator()
{

}

/**
 * @brief Register the storage needs for this module
 *
 * @param registry - StorageRegistry object
 */
void RadamsaRandomizeByteMutator::registerStorageNeeds(StorageRegistry& registry)
{
    // This module does not register for a test case buffer key, because mutators are told which buffer to write in storage
    // by the input generator that calls them
}

void RadamsaRandomizeByteMutator::mutateTestCase(StorageModule& storage, StorageEntry* baseEntry, StorageEntry* newEntry, int testCaseKey)
{
    // Consume the original buffer by randomizing a random byte and appending a null-terminator to the end.

    constexpr size_t minimumSize{1u};
    const size_t minimumSeedIndex{0u};
    const size_t originalSize = baseEntry->getBufferSize(testCaseKey);
    char* originalBuffer = baseEntry->getBufferPointer(testCaseKey);

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
                                        rand->randBetween(
                                            lower,
                                            maximumRandomIndexValue) + minimumSeedIndex,
                                        lower,
                                        upper
                                    )
    };

    newBuffer[randomIndexToRandomize] = static_cast<char>(rand->randBetween(0u, std::numeric_limits<char>::max()));
}
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
#include "RadamsaFuseThisMutator.hpp"
#include "RuntimeException.hpp"
#include <random>
#include <algorithm>

using namespace vmf;

#include "ModuleFactory.hpp"
REGISTER_MODULE(RadamsaFuseThisMutator);

/**
 * @brief Builder method to support the ModuleFactory
 * Constructs an instance of this class
 * @return Module* - Pointer to the newly created instance
 */
Module* RadamsaFuseThisMutator::build(std::string name)
{
    return new RadamsaFuseThisMutator(name);
}

/**
 * @brief Initialization method
 *
 * @param config - Configuration object
 */
void RadamsaFuseThisMutator::init(ConfigInterface& config)
{

}

/**
 * @brief Construct a new RadamsaFuseThisMutator::RadamsaFuseThisMutator object
 *
 * @param name The of the name module
 */
RadamsaFuseThisMutator::RadamsaFuseThisMutator(std::string name) : MutatorModule(name)
{
    // rand->randInit();
}

/**
 * @brief Destroy the RadamsaFuseThisMutator::RadamsaFuseThisMutator object
 *
 */
RadamsaFuseThisMutator::~RadamsaFuseThisMutator()
{

}

/**
 * @brief Register the storage needs for this module
 *
 * @param registry - StorageRegistry object
 */
void RadamsaFuseThisMutator::registerStorageNeeds(StorageRegistry& registry)
{
    // This module does not register for a test case buffer key, because mutators are told which buffer to write in storage
    // by the input generator that calls them
}

void RadamsaFuseThisMutator::mutateTestCase(StorageModule& storage, StorageEntry* baseEntry, StorageEntry* newEntry, int testCaseKey)
{
    // Combines a prefix substring and a suffix substring from random indexes of the buffer
    // NOTE: Very likely to return buffer unmodified for small buffer sizes

    const size_t minimumSize{1u};
    const size_t minimumSeedIndex{0u};
    const size_t originalSize = baseEntry->getBufferSize(testCaseKey);
    char* originalBuffer = baseEntry->getBufferPointer(testCaseKey);

    if (originalSize < minimumSize) {
        throw RuntimeException{"The buffer's minimum size must be greater than or equal to 1", RuntimeException::USAGE_ERROR};
    }
    if (minimumSeedIndex > originalSize - 1u) {
        throw RuntimeException{"Minimum seed index is out of bounds", RuntimeException::INDEX_OUT_OF_RANGE};
    }
    if (originalBuffer == nullptr) {
        throw RuntimeException{"Input buffer is null", RuntimeException::UNEXPECTED_ERROR};
    }

    vector<char> data(originalBuffer, originalBuffer + originalSize);
    vector<char> new_data = fuse(data, data, this->rand);

    const size_t newBufferSize{new_data.size() + 1}; // +1 to implicitly append a null terminator
    char* newBuffer{newEntry->allocateBuffer(testCaseKey, newBufferSize)};
    memset(newBuffer, 0u, newBufferSize);
    memcpy(newBuffer, new_data.data(), new_data.size());
}
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
#include "RadamsaModifyTextNumberMutator.hpp"
#include "RuntimeException.hpp"
#include <random>
#include <algorithm>

using namespace vmf;
using std::vector;

#include "ModuleFactory.hpp"
REGISTER_MODULE(RadamsaModifyTextNumberMutator);

/**
 * @brief Builder method to support the ModuleFactory
 * Constructs an instance of this class
 * @return Module* - Pointer to the newly created instance
 */
Module* RadamsaModifyTextNumberMutator::build(std::string name)
{
    return new RadamsaModifyTextNumberMutator(name);
}

/**
 * @brief Initialization method
 *
 * @param config - Configuration object
 */
void RadamsaModifyTextNumberMutator::init(ConfigInterface& config)
{

}

/**
 * @brief Construct a new RadamsaModifyTextNumberMutator::RadamsaModifyTextNumberMutator object
 *
 * @param name The of the name module
 */
RadamsaModifyTextNumberMutator::RadamsaModifyTextNumberMutator(std::string name) : MutatorModule(name)
{
    // rand->randInit();
}

/**
 * @brief Destroy the RadamsaModifyTextNumberMutator::RadamsaModifyTextNumberMutator object
 *
 */
RadamsaModifyTextNumberMutator::~RadamsaModifyTextNumberMutator()
{

}

/**
 * @brief Register the storage needs for this module
 *
 * @param registry - StorageRegistry object
 */
void RadamsaModifyTextNumberMutator::registerStorageNeeds(StorageRegistry& registry)
{
    // This module does not register for a test case buffer key, because mutators are told which buffer to write in storage
    // by the input generator that calls them
}

void RadamsaModifyTextNumberMutator::mutateTestCase(StorageModule& storage, StorageEntry* baseEntry, StorageEntry* newEntry, int testCaseKey)
{
    // Mutate a random ASCII number via a randomly selected numerical mutation

    const size_t minimumSize{1u};
    const size_t minimumSeedIndex{0u};
    const size_t minimumNumbers{1u};
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

    vector<uint8_t> data(originalBuffer, originalBuffer + originalSize);
    vector<NumInfo> dataNums = this->extractTextualNumbers(data);

    if (dataNums.size() < minimumNumbers) {
        throw RuntimeException{"The amount of ASCII numbers must be greater than or equal 1", RuntimeException::USAGE_ERROR};
    }

    NumInfo toMutate = dataNums[this->rand->randBetween(0, dataNums.size() - 1)];

    const vector<unsigned int> interestingNums = this->generateInterestingNumbers();
    unsigned int newValue;
    switch (this->rand->randBetween(0, 11)) {
        case 0:
            newValue = toMutate.value + 1; break;
        case 1:
            newValue = (toMutate.value > 0) ? toMutate.value - 1 : 0; break;
        case 2:
            newValue = 0; break;
        case 3:
            newValue = 1; break;
        case 4:
        case 5:
        case 6:
            newValue = interestingNums[
                this->rand->randBetween(0, interestingNums.size() - 1)
            ]; break;
        case 7:
            newValue = toMutate.value + interestingNums[
                this->rand->randBetween(0, interestingNums.size() - 1)
            ]; break;
        case 8: {
            unsigned int val = interestingNums[
                this->rand->randBetween(0, interestingNums.size() - 1)
            ];
            newValue = (toMutate.value > val) ? toMutate.value - val : 0;
            break;
        }
        case 9:
            newValue = 2 * toMutate.value; break;
        default: {
            unsigned int n = this->rand->randBetween(1, 128);
            unsigned int s = this->rand->randBetween(0, 2);
            newValue = (s == 0 && toMutate.value > n) ? (toMutate.value - n) : (toMutate.value + n);
            break;
        }
    }

    std::string newValueStr = std::to_string(newValue);
    vector<uint8_t> new_data;
    new_data.insert(    // everything before the original value
        new_data.end(), 
        data.begin(), 
        data.begin() + toMutate.offset
    );
    new_data.insert(    // the new value
        new_data.end(),
        newValueStr.begin(),
        newValueStr.end()
    );
    new_data.insert(    // everything after the original value
        new_data.end(),
        data.begin() + toMutate.offset + toMutate.length,
        data.end()
    );

    const size_t newBufferSize{new_data.size() + 1}; // +1 to implicitly append a null terminator
    char* newBuffer{newEntry->allocateBuffer(testCaseKey, newBufferSize)};
    memset(newBuffer, 0u, newBufferSize);
    memcpy(newBuffer, new_data.data(), new_data.size());
}
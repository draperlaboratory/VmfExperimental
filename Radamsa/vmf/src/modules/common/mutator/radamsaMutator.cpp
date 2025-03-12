/* =============================================================================
 * Vader Modular Fuzzer
 * Copyright (c) 2021-2024 The Charles Stark Draper Laboratory, Inc.
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

// VMF Includes
#include "ModuleFactory.hpp"
#include "radamsaMutator.hpp"

namespace vmf
{
REGISTER_MODULE(vmf::modules::radamsa::RadamsaMutator);
}

vmf::Module* vmf::modules::radamsa::RadamsaMutator::build(std::string name) { return new RadamsaMutator(name); }

void vmf::modules::radamsa::RadamsaMutator::SetAlgorithmType(const AlgorithmType algorithmType)
{
    switch(algorithmType)
    {
        case AlgorithmType::ByteMutations_DropByte:
        case AlgorithmType::ByteMutations_FlipByte:
        case AlgorithmType::ByteMutations_InsertByte:
        case AlgorithmType::ByteMutations_RepeatByte:
        case AlgorithmType::ByteMutations_PermuteByte:
        case AlgorithmType::ByteMutations_IncrementByte:
        case AlgorithmType::ByteMutations_DecrementByte:
        case AlgorithmType::ByteMutations_RandomizeByte:
        case AlgorithmType::LineMutations_DeleteLine:
        case AlgorithmType::LineMutations_DeleteSequentialLines:
        case AlgorithmType::LineMutations_DuplicateLine:
        case AlgorithmType::LineMutations_CopyLineCloseBy:
        case AlgorithmType::LineMutations_RepeatLine:
        case AlgorithmType::LineMutations_SwapLine: // Intentional Fallthrough
            algorithmType_ = algorithmType;

            break;
        case AlgorithmType::Unknown:
            throw RuntimeException{
                            "Attempted to set algorithm type to unknown value",
                            RuntimeException::USAGE_ERROR};
        default:
            throw RuntimeException{
                            "Invalid RadamsaMutator algorithm type",
                            RuntimeException::UNEXPECTED_ERROR};
    }
}

void vmf::modules::radamsa::RadamsaMutator::registerStorageNeeds(StorageRegistry& registry)
{
    normalTag_ = registry.registerTag(
                                "RAN_SUCCESSFULLY",
                                StorageRegistry::READ_ONLY);
}

void vmf::modules::radamsa::RadamsaMutator::mutateTestCase(StorageModule& storage, StorageEntry* baseEntry, StorageEntry* newEntry, int testCaseKey)
{
    if (baseEntry == nullptr)
        throw RuntimeException("RadamsaMutator mutate called with null base entry", RuntimeException::OTHER);
    if (newEntry == nullptr)
	throw RuntimeException("RadamsaMutator mutate called with numm new entry", RuntimeException::OTHER);

    const size_t minimumSeedIndex{0u};
    const int size{baseEntry->getBufferSize(testCaseKey)};
    const char* buffer{baseEntry->getBufferPointer(testCaseKey)};

    if(size <= 0)
        throw RuntimeException("RadamsaMutator mutate called with zero sized buffer", RuntimeException::USAGE_ERROR);

    switch(algorithmType_)
    {
    case AlgorithmType::ByteMutations_DropByte:
        DropByte(newEntry, size, buffer, minimumSeedIndex, testCaseKey);
        
        break;
    case AlgorithmType::ByteMutations_FlipByte:
        FlipByte(newEntry, size, buffer, minimumSeedIndex, testCaseKey);
        
        break;
    case AlgorithmType::ByteMutations_InsertByte:
        InsertByte(newEntry, size, buffer, minimumSeedIndex, testCaseKey);
        
        break;
    case AlgorithmType::ByteMutations_RepeatByte:
        RepeatByte(newEntry, size, buffer, minimumSeedIndex, testCaseKey);
        
        break;
    case AlgorithmType::ByteMutations_PermuteByte:
        PermuteByte(newEntry, size, buffer, minimumSeedIndex, testCaseKey);
        
        break;
    case AlgorithmType::ByteMutations_IncrementByte:
        IncrementByte(newEntry, size, buffer, minimumSeedIndex, testCaseKey);
        
        break;
    case AlgorithmType::ByteMutations_DecrementByte:
        DecrementByte(newEntry, size, buffer, minimumSeedIndex, testCaseKey);
        
        break;
    case AlgorithmType::ByteMutations_RandomizeByte:
        RandomizeByte(newEntry, size, buffer, minimumSeedIndex, testCaseKey);
        
        break;
    case AlgorithmType::LineMutations_DeleteLine:
        DeleteLine(newEntry, size, buffer, minimumSeedIndex, testCaseKey);
        
        break;
    case AlgorithmType::LineMutations_DeleteSequentialLines:
        DeleteSequentialLines(newEntry, size, buffer, minimumSeedIndex, testCaseKey);
        
        break;
    case AlgorithmType::LineMutations_DuplicateLine:
        DuplicateLine(newEntry, size, buffer, minimumSeedIndex, testCaseKey);
        
        break;
    case AlgorithmType::LineMutations_CopyLineCloseBy:
        CopyLineCloseBy(newEntry, size, buffer, minimumSeedIndex, testCaseKey);
        
        break;
    case AlgorithmType::LineMutations_RepeatLine:
        RepeatLine(newEntry, size, buffer, minimumSeedIndex, testCaseKey);
        
        break;
    case AlgorithmType::LineMutations_SwapLine:
        SwapLine(newEntry, size, buffer, minimumSeedIndex, testCaseKey);
        
        break;
    default:
        throw RuntimeException("Invalid RadamsaMutator algorithm type", RuntimeException::UNEXPECTED_ERROR);

        break;
    }
}

vmf::modules::radamsa::RadamsaMutator::AlgorithmType vmf::modules::radamsa::RadamsaMutator::stringToType(std::string type)
{
    if(type.compare("ByteMutations_DropByte") == 0)
        return AlgorithmType::ByteMutations_DropByte;
    else if(type.compare("ByteMutations_FlipByte") == 0)
        return AlgorithmType::ByteMutations_FlipByte;
    else if(type.compare("ByteMutations_InsertByte") == 0)
        return AlgorithmType::ByteMutations_InsertByte;
    else if(type.compare("ByteMutations_RepeatByte") == 0)
        return AlgorithmType::ByteMutations_RepeatByte;
    else if(type.compare("ByteMutations_PermuteByte") == 0)
        return AlgorithmType::ByteMutations_PermuteByte;
    else if(type.compare("ByteMutations_IncrementByte") == 0)
        return AlgorithmType::ByteMutations_IncrementByte;
    else if(type.compare("ByteMutations_DecrementByte") == 0)
        return  AlgorithmType::ByteMutations_DecrementByte;
    else if(type.compare("ByteMutations_RandomizeByte") == 0)
        return AlgorithmType::ByteMutations_RandomizeByte;
    else if(type.compare("LineMutations_DeleteLine") == 0)
        return AlgorithmType::LineMutations_DeleteLine;
    else if(type.compare("LineMutations_DeleteSequentialLines") == 0)
        return AlgorithmType::LineMutations_DeleteSequentialLines;
    else if(type.compare("LineMutations_DuplicateLine") == 0)
        return AlgorithmType::LineMutations_DuplicateLine;
    else if(type.compare("LineMutations_CopyLineCloseBy") == 0)
        return AlgorithmType::LineMutations_CopyLineCloseBy;
    else if(type.compare("LineMutations_RepeatLine") == 0)
        return AlgorithmType::LineMutations_RepeatLine;
    else if(type.compare("LineMutations_SwapLine") == 0)
        return AlgorithmType::LineMutations_SwapLine;
    else
        return AlgorithmType::Unknown;
}

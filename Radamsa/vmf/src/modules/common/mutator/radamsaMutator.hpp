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
#pragma once

// VMF Includes
#include "MutatorModule.hpp"
#include "StorageEntry.hpp"
#include "RuntimeException.hpp"
#include "byteMutations.hpp"
#include "lineMutations.hpp"


namespace vmf::modules::radamsa
{
/**
 * @brief This module is draws heavily upon the libAFL mutator.c
 * 
 * Uses the specified AFL-style mutation algorithm to mutate the provided
 * input.  mutateTestCase is the main mutation method.
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
class RadamsaMutator: public MutatorModule,
                      public vmf::radamsa::mutations::ByteMutations,
                      public vmf::radamsa::mutations::LineMutations
{
public:
    enum class AlgorithmType : uint8_t
    {
        ByteMutations_DropByte = 0u,
        ByteMutations_FlipByte,
        ByteMutations_InsertByte,
        ByteMutations_RepeatByte,
        ByteMutations_PermuteByte,
        ByteMutations_IncrementByte,
        ByteMutations_DecrementByte,
        ByteMutations_RandomizeByte,
        LineMutations_DeleteLine,
        LineMutations_DeleteSequentialLines,
        LineMutations_DuplicateLine,
        LineMutations_CopyLineCloseBy,
        LineMutations_RepeatLine,
        LineMutations_SwapLine,
        Unknown
    };

    RadamsaMutator() = delete;
    virtual ~RadamsaMutator() = default;

    RadamsaMutator(std::string name) noexcept : MutatorModule{name},
                                                vmf::radamsa::mutations::ByteMutations{RANDOM_NUMBER_GENERATOR_},
                                                vmf::radamsa::mutations::LineMutations{RANDOM_NUMBER_GENERATOR_}
                                                
    {}

    /////////////////////////////
    // MutatorModule Interface //
    /////////////////////////////
    virtual void init(ConfigInterface& config) { SetAlgorithmType(stringToType(config.getStringParam(getModuleName(), "algType"))); }

    virtual void registerStorageNeeds(StorageRegistry& registry);
    
    virtual void mutateTestCase(StorageModule& storage, StorageEntry* baseEntry, StorageEntry* newEntry, int testCaseKey);

    static Module* build(std::string name);

protected:
    ////////////////////////////
    // RadamsaMutator Utility //
    ////////////////////////////
    void SetAlgorithmType(const AlgorithmType algorithmType);

    AlgorithmType GetAlgorithmType() const noexcept { return algorithmType_; }

    static AlgorithmType stringToType(std::string type);

    static constexpr int INVALID_TEST_CASE_KEY_{std::numeric_limits<int>::min()};
    static constexpr int INVALID_NORMAL_TAG_{INVALID_TEST_CASE_KEY_};

    int normalTag_{INVALID_NORMAL_TAG_};
    AlgorithmType algorithmType_{AlgorithmType::ByteMutations_DropByte};

    std::default_random_engine RANDOM_NUMBER_GENERATOR_;

private:
};
}

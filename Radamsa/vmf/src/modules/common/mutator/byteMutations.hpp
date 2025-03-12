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

#include "StorageEntry.hpp"
#include "RuntimeException.hpp"
#include "mutationBase.hpp"


namespace vmf::radamsa::mutations
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
class ByteMutations: public vmf::radamsa::mutations::MutationBase
{
public:
    ByteMutations() = delete;
    virtual ~ByteMutations() = default;

    ByteMutations(const ByteMutations&) = delete;
    ByteMutations(ByteMutations&&) = delete;

    ByteMutations& operator=(const ByteMutations&) = delete;
    ByteMutations& operator=(ByteMutations&&) = delete;

    void DropByte(
            StorageEntry* newEntry,
            const size_t originalBufferSize,
            const char* originalBuffer,
            const size_t minimumSeedIndex,
            const int testCaseKey);

    void FlipByte(
            StorageEntry* newEntry,
            const size_t originalBufferSize,
            const char* originalBuffer,
            const size_t minimumSeedIndex,
            const int testCaseKey);

    void InsertByte(
            StorageEntry* newEntry,
            const size_t originalBufferSize,
            const char* originalBuffer,
            const size_t minimumSeedIndex,
            const int testCaseKey);

    void RepeatByte(
            StorageEntry* newEntry,
            const size_t originalBufferSize,
            const char* originalBuffer,
            const size_t minimumSeedIndex,
            const int testCaseKey);

    void PermuteByte(
            StorageEntry* newEntry,
            const size_t originalBufferSize,
            const char* originalBuffer,
            const size_t minimumSeedIndex,
            const int testCaseKey);

    void IncrementByte(
            StorageEntry* newEntry,
            const size_t originalBufferSize,
            const char* originalBuffer,
            const size_t minimumSeedIndex,
            const int testCaseKey);

    void DecrementByte(
            StorageEntry* newEntry,
            const size_t originalBufferSize,
            const char* originalBuffer,
            const size_t minimumSeedIndex,
            const int testCaseKey);

    void RandomizeByte(
            StorageEntry* newEntry,
            const size_t originalBufferSize,
            const char* originalBuffer,
            const size_t minimumSeedIndex,
            const int testCaseKey);

protected:
    ByteMutations(std::default_random_engine& randomNumberGenerator) : MutationBase{randomNumberGenerator} {}

private:
};
}

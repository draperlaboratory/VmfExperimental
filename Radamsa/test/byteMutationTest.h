/* =============================================================================
* Vader Modular Fuzzer
* Copyright (c) 2021-2023 The Charles Stark Draper Laboratory, Inc.
* <vader@draper.com>
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
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
* @license GPL-3.0-or-later <https://spdx.org/licenses/GPL-3.0-or-later>
* ===========================================================================*/

#pragma once

#ifndef GTEST_DECORATOR
#define GTEST_DECORATOR std::cout << "\033[32m[          ] \033[37m[ INFO ] "
#endif

// C/C++ Includes
#include <tuple>
#include <map>
#include <functional>

// Google Test Includes
#include "gtest/gtest.h"

// VMF Includes
#include "SimpleStorage.hpp"
#include "byteMutations.hpp"

namespace vader::test::modules::radamsa::mutations
{
class ByteMutationTest : public ::testing::Test,
                         public ::vader::radamsa::mutations::ByteMutations
{
public:
    virtual ~ByteMutationTest() = default;

    ByteMutationTest() : ::vader::radamsa::mutations::ByteMutations{randomNumberGenerator_} {}

protected:
    typedef std::function<void(vader::StorageEntry*, const size_t, const char*, const size_t, const int)> Byte_Mutation_Callback;

    static constexpr size_t inputBufferSize_{5u};

    std::tuple<int, std::unique_ptr<vader::SimpleStorage>, unsigned long> RunByteMutationCallback(
                                                                                    const char* inputBuffer,
                                                                                    const int size,
                                                                                    const int minimumSeedIndex,
                                                                                    const Byte_Mutation_Callback& callback) const
    {
        // Subtest prologue - Get testcase key and storage entry

        std::unique_ptr<vader::SimpleStorage> storage{std::make_unique<vader::SimpleStorage>("storage")};
        std::unique_ptr<vader::StorageRegistry> registry{
                                            std::make_unique<vader::StorageRegistry>(
                                                                        "TEST_INT",
                                                                        vader::StorageRegistry::INT,
                                                                        vader::StorageRegistry::ASCENDING)};
        std::unique_ptr<vader::StorageRegistry> metadata{std::make_unique<vader::StorageRegistry>()};

        const int testCaseKey{
                        registry->registerKey(
                                        "TEST_CASE",
                                        vader::StorageRegistry::BUFFER,
                                        vader::StorageRegistry::READ_WRITE)};

        storage->configure(registry.get(), metadata.get());

        vader::StorageEntry* storageEntryPtr{storage->createNewEntry()};

        storage->saveEntry(storageEntryPtr);

        // Execute the subtest against the desired callback.

        callback(
            storageEntryPtr,
            size,
            inputBuffer,
            minimumSeedIndex,
            testCaseKey);

        return std::make_tuple(testCaseKey, std::move(storage), storageEntryPtr->getID());
    }

    template<size_t N>
    void RunSubtest(
                const std::map<std::pair<size_t, size_t>, const std::array<char, N>>& expectedOutput,
                const Byte_Mutation_Callback& callback) const
    {
        try
        {
            // Execute the callback 10 times per valid minimum seed index.

            for (const auto& minimumSeedIndex : minimumSeedIndices_)
            {
                constexpr size_t numberOfRandomDraws{10u};

                for (size_t it{0u}; it < numberOfRandomDraws; ++it)
                {
                    std::tuple<int, std::unique_ptr<SimpleStorage>, unsigned long> testCaseStorageTuple{
                                                                                                    RunByteMutationCallback(
                                                                                                                    inputBuffer_.data(),
                                                                                                                    inputBuffer_.size(),
                                                                                                                    minimumSeedIndex,
                                                                                                                    callback)};

                    const int testCaseKey{std::get<0u>(testCaseStorageTuple)};
                    const unsigned long entryId{std::get<2u>(testCaseStorageTuple)};
                    StorageEntry* storageEntryPtr{std::get<1u>(testCaseStorageTuple)->getEntryByID(entryId)};

                    const int outputBufferSize{storageEntryPtr->getBufferSize(testCaseKey)};
                    const char* const outputBuffer{storageEntryPtr->getBufferPointer(testCaseKey)};

                    const std::array<char, N>& expectedBuffer{expectedOutput.at(std::make_pair(minimumSeedIndex, it))};

                    ASSERT_EQ(outputBufferSize, N);
                    EXPECT_EQ(outputBuffer[outputBufferSize - 1u], 0u);
                    EXPECT_EQ(memcmp(outputBuffer, expectedBuffer.data(), outputBufferSize), 0);
                }
            }

            {
                // Execute callback with an invalid minimum seed index.

                EXPECT_THROW(
                        RunByteMutationCallback(
                                        inputBuffer_.data(),
                                        inputBuffer_.size(),
                                        inputBuffer_.size(), // This minimum seed index is invalid
                                        callback),
                        RuntimeException);
            }

            {
                // Execute callback with an invalid buffer size.

                constexpr int minimumSeedIndex{0u};

                EXPECT_THROW(
                        RunByteMutationCallback(
                                        inputBuffer_.data(),
                                        0u, // This size is invalid
                                        minimumSeedIndex,
                                        callback),
                        RuntimeException);
            }

            {
                // Execute callback with an invalid buffer.

                constexpr int minimumSeedIndex{0u};

                EXPECT_THROW(
                        RunByteMutationCallback(
                                        nullptr, // This pointer is invalid
                                        inputBuffer_.size(),
                                        minimumSeedIndex,
                                        callback),
                        RuntimeException);
            }
        }
        catch(...)
        {
            GTEST_DECORATOR << "Unknown Error occurred" << std::endl;

            EXPECT_TRUE(false);
        }
    }

private:
    static constexpr std::array<size_t, inputBufferSize_> minimumSeedIndices_{0u, 1u, 2u, 3u, 4u};
    static constexpr std::array<char, inputBufferSize_> inputBuffer_{0x01u, 0x02u, 0x03u, 0x04u, 0x05u};

    std::default_random_engine randomNumberGenerator_;
};
}
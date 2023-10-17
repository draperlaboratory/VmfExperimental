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
#include "lineMutations.hpp"

namespace vader::test::modules::radamsa::mutations
{
class LineMutationTest : public ::testing::Test,
                         public ::vader::radamsa::mutations::LineMutations
{
public:
    virtual ~LineMutationTest() = default;

    LineMutationTest() : ::vader::radamsa::mutations::LineMutations{randomNumberGenerator_} {}

protected:
    typedef size_t character_index, random_draw_index, expected_buffer_size;

    typedef std::function<void(vader::StorageEntry*, const size_t, const char*, const size_t, const int)> Line_Mutation_Callback;

    std::tuple<int, std::unique_ptr<vader::SimpleStorage>, unsigned long> RunLineMutationCallback(
                                                                                    const char* inputBuffer,
                                                                                    const int size,
                                                                                    const int characterIndex,
                                                                                    const Line_Mutation_Callback& callback) const
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
            characterIndex,
            testCaseKey);

        return std::make_tuple(testCaseKey, std::move(storage), storageEntryPtr->getID());
    }

    void RunSubtest(
                const char* const inputBuffer,
                const size_t inputBufferSize,
                const std::map<std::pair<character_index, random_draw_index>, std::pair<const char* const, expected_buffer_size>>& expectedOutput,
                const Line_Mutation_Callback& lineMutationCallback) const
    {
        try
        {
            // Execute the callback 10 times per valid character index.

            for (const auto& characterIndex : characterIndices_)
            {
                constexpr size_t numberOfRandomDraws{10u};

                for (size_t randomDrawIndex{0u}; randomDrawIndex < numberOfRandomDraws; ++randomDrawIndex)
                {
                    std::tuple<int, std::unique_ptr<SimpleStorage>, unsigned long> testCaseStorageTuple{
                                                                                                    RunLineMutationCallback(
                                                                                                                    inputBuffer,
                                                                                                                    inputBufferSize,
                                                                                                                    characterIndex,
                                                                                                                    lineMutationCallback)};

                    const int testCaseKey{std::get<0u>(testCaseStorageTuple)};
                    const unsigned long entryId{std::get<2u>(testCaseStorageTuple)};
                    StorageEntry* storageEntryPtr{std::get<1u>(testCaseStorageTuple)->getEntryByID(entryId)};

                    const int outputBufferSize{storageEntryPtr->getBufferSize(testCaseKey)};
                    const char* const outputBuffer{storageEntryPtr->getBufferPointer(testCaseKey)};

                    std::pair<const char* const, expected_buffer_size> expectedBufferData{
                                                                                    expectedOutput.at(
                                                                                                std::make_pair(
                                                                                                        characterIndex,
                                                                                                        randomDrawIndex))};

                    const char* const expectedBuffer{expectedBufferData.first};
                    const size_t expectedBufferSize{expectedBufferData.second};

                    ASSERT_EQ(outputBufferSize, expectedBufferSize);
                    ASSERT_EQ(outputBuffer[outputBufferSize - 1u], 0u);
                    ASSERT_EQ(memcmp(outputBuffer, expectedBuffer, outputBufferSize), 0);
                }
            }

            {
                // Execute callback with an invalid character index.

                EXPECT_THROW(
                        RunLineMutationCallback(
                                        inputBuffer,
                                        inputBufferSize,
                                        inputBufferSize, // This character index is invalid
                                        lineMutationCallback),
                        RuntimeException);
            }

            {
                // Execute callback with an invalid buffer size.

                constexpr int characterIndex{0u};

                EXPECT_THROW(
                        RunLineMutationCallback(
                                        inputBuffer,
                                        0u, // This size is invalid
                                        characterIndex,
                                        lineMutationCallback),
                        RuntimeException);
            }

            {
                // Execute callback with an invalid buffer.

                constexpr int characterIndex{0u};

                EXPECT_THROW(
                        RunLineMutationCallback(
                                        nullptr, // This pointer is invalid
                                        inputBufferSize,
                                        characterIndex,
                                        lineMutationCallback),
                        RuntimeException);
            }
        }
        catch(const RuntimeException& e)
        {
            GTEST_DECORATOR << "\n" << e.getReason();
            EXPECT_TRUE(false);
        }
        catch(const std::exception& e)
        {
            GTEST_DECORATOR << "\n" << e.what();
            EXPECT_TRUE(false);
        }
        catch(...)
        {
            GTEST_DECORATOR << "Unknown Error occurred" << std::endl;
            EXPECT_TRUE(false);
        }
    }

    static constexpr char asciiInputBuffer_[]{"Line0\nLine1\nLine2\nLine3\nLine4\0"};
    static constexpr char utf8InputBuffer_[]{u8"🤣0\n🤣1\n🤣2\n🤣3\n🤣4\0"};

    static constexpr std::array<size_t, sizeof(asciiInputBuffer_)> characterIndices_{
                                                                            0u, 1u, 2u, 3u, 4u, 5u,
                                                                            6u, 7u, 8u, 9u, 10u,
                                                                            11u, 12u, 13u, 14u, 15u,
                                                                            16u, 17u, 18u, 19u, 20u,
                                                                            21u, 22u, 23u, 24u, 25u,
                                                                            26u, 27u, 28u, 29u, 30u};

private:
    std::default_random_engine randomNumberGenerator_;
};
}
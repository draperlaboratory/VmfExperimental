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

// Google Test Includes
#include "gtest/gtest.h"

// VMF Includes
#include "radamsaMutatorTest.hpp"

namespace vmf::test::modules::radamsa
{
TEST_F(UninitializedRadamsaMutatorTest, TestDefaultConstructor)
{
    ASSERT_EQ(RANDOM_NUMBER_GENERATOR_, std::default_random_engine{});
    ASSERT_EQ(algorithmType_, AlgorithmType::ByteMutations_DropByte);
    ASSERT_EQ(testCaseKey_, INVALID_TEST_CASE_KEY_);
    ASSERT_EQ(normalTag_, INVALID_NORMAL_TAG_);
}

TEST_F(UninitializedRadamsaMutatorTest, TestInit)
{
    auto runInitMethod{
                [&](std::string&& fileStream, const AlgorithmType expectedAlgorithmType)
                {
                    std::vector<std::string> configurationFiles;

                    configurationFiles.emplace_back(std::move(fileStream));

                    std::unique_ptr<ConfigInterface> configurationManager{std::make_unique<MockConfigurationManager>(configurationFiles)};
                    
                    init(*configurationManager.get());

                    ASSERT_EQ(algorithmType_, expectedAlgorithmType);
                }};

    // Valid Input - This subtest should update the algorithm type to ByteMutations_DropByte and execute successfuly.

    runInitMethod(
                std::string{
                        std::move(
                            std::string{"modules:\n"} +
                                std::move("    - name: TestMutator\n") +
                                std::move("      className: \"vmf::modules::radamsa::RadamsaMutator\"\n") +
                                std::move("TestMutator:\n") + 
                                std::move("  algType: ByteMutations_DropByte"))},
                AlgorithmType::ByteMutations_DropByte);

    // Valid Input - This subtest should update the algorithm type to ByteMutations_FlipByte and execute successfuly.

    runInitMethod(
                std::string{
                        std::move(
                            std::string{"modules:\n"} +
                                std::move("    - name: TestMutator\n") +
                                std::move("      className: \"vmf::modules::radamsa::RadamsaMutator\"\n") +
                                std::move("TestMutator:\n") + 
                                std::move("  algType: ByteMutations_FlipByte"))},
                AlgorithmType::ByteMutations_FlipByte);

    // Valid Input - This subtest should update the algorithm type to ByteMutations_InsertByte and execute successfuly.

    runInitMethod(
                std::string{
                        std::move(
                            std::string{"modules:\n"} +
                                std::move("    - name: TestMutator\n") +
                                std::move("      className: \"vmf::modules::radamsa::RadamsaMutator\"\n") +
                                std::move("TestMutator:\n") + 
                                std::move("  algType: ByteMutations_InsertByte"))},
                AlgorithmType::ByteMutations_InsertByte);

    // Valid Input - This subtest should update the algorithm type to ByteMutations_RepeatByte and execute successfuly.

    runInitMethod(
                std::string{
                        std::move(
                            std::string{"modules:\n"} +
                                std::move("    - name: TestMutator\n") +
                                std::move("      className: \"vmf::modules::radamsa::RadamsaMutator\"\n") +
                                std::move("TestMutator:\n") + 
                                std::move("  algType: ByteMutations_RepeatByte"))},
                AlgorithmType::ByteMutations_RepeatByte);

    // Valid Input - This subtest should update the algorithm type to ByteMutations_PermuteByte and execute successfuly.

    runInitMethod(
                std::string{
                        std::move(
                            std::string{"modules:\n"} +
                                std::move("    - name: TestMutator\n") +
                                std::move("      className: \"vmf::modules::radamsa::RadamsaMutator\"\n") +
                                std::move("TestMutator:\n") + 
                                std::move("  algType: ByteMutations_PermuteByte"))},
                AlgorithmType::ByteMutations_PermuteByte);

    // Valid Input - This subtest should update the algorithm type to ByteMutations_IncrementByte and execute successfuly.

    runInitMethod(
                std::string{
                        std::move(
                            std::string{"modules:\n"} +
                                std::move("    - name: TestMutator\n") +
                                std::move("      className: \"vmf::modules::radamsa::RadamsaMutator\"\n") +
                                std::move("TestMutator:\n") + 
                                std::move("  algType: ByteMutations_IncrementByte"))},
                AlgorithmType::ByteMutations_IncrementByte);

    // Valid Input - This subtest should update the algorithm type to ByteMutations_DecrementByte and execute successfuly.

    runInitMethod(
                std::string{
                        std::move(
                            std::string{"modules:\n"} +
                                std::move("    - name: TestMutator\n") +
                                std::move("      className: \"vmf::modules::radamsa::RadamsaMutator\"\n") +
                                std::move("TestMutator:\n") + 
                                std::move("  algType: ByteMutations_DecrementByte"))},
                AlgorithmType::ByteMutations_DecrementByte);

    // Valid Input - This subtest should update the algorithm type to LineMutations_DeleteLine and execute successfuly.

    runInitMethod(
                std::string{
                        std::move(
                            std::string{"modules:\n"} +
                                std::move("    - name: TestMutator\n") +
                                std::move("      className: \"vmf::modules::radamsa::RadamsaMutator\"\n") +
                                std::move("TestMutator:\n") + 
                                std::move("  algType: LineMutations_DeleteLine"))},
                AlgorithmType::LineMutations_DeleteLine);

    runInitMethod(
                std::string{
                        std::move(
                            std::string{"modules:\n"} +
                                std::move("    - name: TestMutator\n") +
                                std::move("      className: \"vmf::modules::radamsa::RadamsaMutator\"\n") +
                                std::move("TestMutator:\n") + 
                                std::move("  algType: LineMutations_DeleteSequentialLines"))},
                AlgorithmType::LineMutations_DeleteSequentialLines);

    runInitMethod(
                std::string{
                        std::move(
                            std::string{"modules:\n"} +
                                std::move("    - name: TestMutator\n") +
                                std::move("      className: \"vmf::modules::radamsa::RadamsaMutator\"\n") +
                                std::move("TestMutator:\n") + 
                                std::move("  algType: LineMutations_DuplicateLine"))},
                AlgorithmType::LineMutations_DuplicateLine);

    runInitMethod(
                std::string{
                        std::move(
                            std::string{"modules:\n"} +
                                std::move("    - name: TestMutator\n") +
                                std::move("      className: \"vmf::modules::radamsa::RadamsaMutator\"\n") +
                                std::move("TestMutator:\n") + 
                                std::move("  algType: LineMutations_CopyLineCloseBy"))},
                AlgorithmType::LineMutations_CopyLineCloseBy);

    runInitMethod(
                std::string{
                        std::move(
                            std::string{"modules:\n"} +
                                std::move("    - name: TestMutator\n") +
                                std::move("      className: \"vmf::modules::radamsa::RadamsaMutator\"\n") +
                                std::move("TestMutator:\n") + 
                                std::move("  algType: LineMutations_RepeatLine"))},
                AlgorithmType::LineMutations_RepeatLine);

    runInitMethod(
                std::string{
                        std::move(
                            std::string{"modules:\n"} +
                                std::move("    - name: TestMutator\n") +
                                std::move("      className: \"vmf::modules::radamsa::RadamsaMutator\"\n") +
                                std::move("TestMutator:\n") + 
                                std::move("  algType: LineMutations_SwapLine"))},
                AlgorithmType::LineMutations_SwapLine);

    // Erroneous Input - This subtest should trigger a runtime exception since the algorithm type is Unknown.

    EXPECT_THROW(
            runInitMethod(
                    std::string{
                            std::move(
                                std::string{"modules:\n"} +
                                    std::move("    - name: TestMutator\n") +
                                    std::move("      className: \"vmf::modules::radamsa::RadamsaMutator\"\n") +
                                    std::move("TestMutator:\n") + 
                                    std::move("  algType: Unknown"))},
                    AlgorithmType::Unknown),
            RuntimeException);

    // Erroneous Input - This subtest should trigger a runtime exception since the algorithm type is Unmapped.

    EXPECT_THROW(
            runInitMethod(
                    std::string{
                            std::move(
                                std::string{"modules:\n"} +
                                    std::move("    - name: TestMutator\n") +
                                    std::move("      className: \"vmf::modules::radamsa::RadamsaMutator\"\n") +
                                    std::move("TestMutator:\n") + 
                                    std::move("  algType: Unmapped"))},
                    AlgorithmType::Unknown),
            RuntimeException);
}

TEST_F(UninitializedRadamsaMutatorTest, TestRegisterStorageNeeds)
{
    StorageRegistry storageRegistry{
                                "TEST_FLOAT",
                                StorageRegistry::storageTypes::FLOAT,
                                StorageRegistry::sortOrder::DESCENDING};

    registerStorageNeeds(storageRegistry);

    ASSERT_NE(testCaseKey_, INVALID_TEST_CASE_KEY_);
    ASSERT_NE(normalTag_, INVALID_NORMAL_TAG_);
}

TEST_F(UninitializedRadamsaMutatorTest, TestBuild)
{
    std::unique_ptr<vmf::Module> module{build("TestMutator")};

    ASSERT_EQ(module->getModuleName(), "TestMutator");
    ASSERT_EQ(module->getModuleType(), MUTATOR);
}

TEST_F(UninitializedRadamsaMutatorTest, TestGetAlgorithmType)
{
    auto runGetAlgorithmTypeMethod{
                                [&](const AlgorithmType expectedAlgorithmType)
                                {
                                    algorithmType_ = expectedAlgorithmType;

                                    ASSERT_EQ(GetAlgorithmType(), expectedAlgorithmType);
                                }};

    runGetAlgorithmTypeMethod(AlgorithmType::ByteMutations_DropByte);
    runGetAlgorithmTypeMethod(AlgorithmType::ByteMutations_FlipByte);
    runGetAlgorithmTypeMethod(AlgorithmType::ByteMutations_InsertByte);
    runGetAlgorithmTypeMethod(AlgorithmType::ByteMutations_RepeatByte);
    runGetAlgorithmTypeMethod(AlgorithmType::ByteMutations_PermuteByte);
    runGetAlgorithmTypeMethod(AlgorithmType::ByteMutations_IncrementByte);
    runGetAlgorithmTypeMethod(AlgorithmType::ByteMutations_DecrementByte);
    runGetAlgorithmTypeMethod(AlgorithmType::ByteMutations_RandomizeByte);
    runGetAlgorithmTypeMethod(AlgorithmType::LineMutations_DeleteLine);
    runGetAlgorithmTypeMethod(AlgorithmType::LineMutations_DeleteSequentialLines);
    runGetAlgorithmTypeMethod(AlgorithmType::LineMutations_DuplicateLine);
    runGetAlgorithmTypeMethod(AlgorithmType::LineMutations_CopyLineCloseBy);
    runGetAlgorithmTypeMethod(AlgorithmType::LineMutations_RepeatLine);
    runGetAlgorithmTypeMethod(AlgorithmType::LineMutations_SwapLine);
    runGetAlgorithmTypeMethod(AlgorithmType::Unknown);
}

TEST_F(InitializedRadamsaMutatorTest, TestCreateTestCase_ByteMutations)
{
    {
        StorageEntry* baseEntry{GetBaseEntry(asciiInput_, sizeof(asciiInput_))};

        {
            // Valid Input - This subtest should update the algorithm type to ByteMutations_DropByte and execute successfuly.

            constexpr int expectedBufferSize{sizeof(asciiInput_)};

            RunSetTestCaseMethod(AlgorithmType::ByteMutations_DropByte, expectedBufferSize, baseEntry);
        }

        {
            // Valid Input - This subtest should update the algorithm type to ByteMutations_FlipByte and execute successfuly.

            constexpr int expectedBufferSize{sizeof(asciiInput_) + 1};

            RunSetTestCaseMethod(AlgorithmType::ByteMutations_FlipByte, expectedBufferSize, baseEntry);
        }

        {
            // Valid Input - This subtest should update the algorithm type to ByteMutations_InsertByte and execute successfuly.

            constexpr int expectedBufferSize{sizeof(asciiInput_) + 2};

            RunSetTestCaseMethod(AlgorithmType::ByteMutations_InsertByte, expectedBufferSize, baseEntry);
        }

        {
            // Valid Input - This subtest should update the algorithm type to ByteMutations_RepeatByte and execute successfuly.
            
            // The expected output size for this subtest was gathered during a previous run using the default random seed.
            // If the random seed is changed or new calls to the subtests are added prior to this statement,
            // the output size will also change and the unit tests will fail.

            constexpr int expectedBufferSize{sizeof(asciiInput_) + 2};

            RunSetTestCaseMethod(AlgorithmType::ByteMutations_RepeatByte, expectedBufferSize, baseEntry);
        }

        {
            // Valid Input - This subtest should update the algorithm type to ByteMutations_PermuteByte and execute successfuly.

            constexpr int expectedBufferSize{sizeof(asciiInput_) + 1};

            RunSetTestCaseMethod(AlgorithmType::ByteMutations_PermuteByte, expectedBufferSize, baseEntry);
        }

        {
            // Valid Input - This subtest should update the algorithm type to ByteMutations_IncrementByte and execute successfuly.

            constexpr int expectedBufferSize{sizeof(asciiInput_) + 1};

            RunSetTestCaseMethod(AlgorithmType::ByteMutations_IncrementByte, expectedBufferSize, baseEntry);
        }

        {
            // Valid Input - This subtest should update the algorithm type to ByteMutations_DecrementByte and execute successfuly.

            constexpr int expectedBufferSize{sizeof(asciiInput_) + 1};

            RunSetTestCaseMethod(AlgorithmType::ByteMutations_DecrementByte, expectedBufferSize, baseEntry);
        }

        {
            // Valid Input - This subtest should update the algorithm type to ByteMutations_RandomizeByte and execute successfuly.

            constexpr int expectedBufferSize{sizeof(asciiInput_) + 1};

            RunSetTestCaseMethod(AlgorithmType::ByteMutations_RandomizeByte, expectedBufferSize, baseEntry);
        }
    }
}

TEST_F(InitializedRadamsaMutatorTest, TestCreateTestCase_LineMutations_AsciiInput)
{
    {
        StorageEntry* baseEntry{GetBaseEntry(asciiInput_, sizeof(asciiInput_))};

        {
            // Valid Input - This subtest should update the algorithm type to LineMutations_DeleteLine and execute successfuly.

            constexpr int expectedBufferSize{1};

            RunSetTestCaseMethod(AlgorithmType::LineMutations_DeleteLine, expectedBufferSize, baseEntry);
        }

        {
            // Valid Input - This subtest should update the algorithm type to LineMutations_DeleteSequentialLines and execute successfuly.

            constexpr int expectedBufferSize{1};

            RunSetTestCaseMethod(AlgorithmType::LineMutations_DeleteSequentialLines, expectedBufferSize, baseEntry);
        }

        {
            // Valid Input - This subtest should update the algorithm type to LineMutations_DuplicateLine and execute successfuly.

            constexpr int expectedBufferSize{sizeof(asciiInput_) + 1};

            RunSetTestCaseMethod(AlgorithmType::LineMutations_DuplicateLine, expectedBufferSize, baseEntry);
        }

        {
            // Valid Input - This subtest should update the algorithm type to LineMutations_CopyLineCloseBy and execute successfuly.

            constexpr int expectedBufferSize{sizeof(asciiInput_) + 1};

            RunSetTestCaseMethod(AlgorithmType::LineMutations_CopyLineCloseBy, expectedBufferSize, baseEntry);
        }

        {
            // Valid Input - This subtest should update the algorithm type to LineMutations_RepeatLine and execute successfuly.

            constexpr int expectedBufferSize{sizeof(asciiInput_) + 1};

            RunSetTestCaseMethod(AlgorithmType::LineMutations_RepeatLine, expectedBufferSize, baseEntry);
        }

        {
            // Valid Input - This subtest should update the algorithm type to LineMutations_SwapLine and execute successfuly.

            constexpr int expectedBufferSize{sizeof(asciiInput_) + 1};

            RunSetTestCaseMethod(AlgorithmType::LineMutations_SwapLine, expectedBufferSize, baseEntry);
        }
    }
}

TEST_F(InitializedRadamsaMutatorTest, TestCreateTestCase_LineMutations_Utf8Input)
{
    {
        StorageEntry* baseEntry{GetBaseEntry(utf8Input_, sizeof(utf8Input_))};

        {
            // Valid Input - This subtest should update the algorithm type to LineMutations_DeleteLine and execute successfuly.

            constexpr int expectedBufferSize{sizeof(utf8Input_) + 1};

            RunSetTestCaseMethod(AlgorithmType::LineMutations_DeleteLine, expectedBufferSize, baseEntry);
        }

        {
            // Valid Input - This subtest should update the algorithm type to LineMutations_DeleteSequentialLines and execute successfuly.

            constexpr int expectedBufferSize{sizeof(utf8Input_) + 1};

            RunSetTestCaseMethod(AlgorithmType::LineMutations_DeleteSequentialLines, expectedBufferSize, baseEntry);
        }

        {
            // Valid Input - This subtest should update the algorithm type to LineMutations_DuplicateLine and execute successfuly.

            constexpr int expectedBufferSize{sizeof(utf8Input_) * 2 + 1};

            RunSetTestCaseMethod(AlgorithmType::LineMutations_DuplicateLine, expectedBufferSize, baseEntry);
        }

        {
            // Valid Input - This subtest should update the algorithm type to LineMutations_CopyLineCloseBy and execute successfuly.

            constexpr int expectedBufferSize{sizeof(utf8Input_) * 2 + 1};

            RunSetTestCaseMethod(AlgorithmType::LineMutations_CopyLineCloseBy, expectedBufferSize, baseEntry);
        }

        {
            // Valid Input - This subtest should update the algorithm type to LineMutations_RepeatLine and execute successfuly.

            // The expected output size for this subtest was gathered during a previous run using the default random seed.
            // If the random seed is changed or new calls to the subtests are added prior to this statement,
            // the output size will also change and the unit tests will fail.

            constexpr int expectedBufferSize{sizeof(utf8Input_) * 2 + 1};

            RunSetTestCaseMethod(AlgorithmType::LineMutations_RepeatLine, expectedBufferSize, baseEntry);
        }

        {
            // Valid Input - This subtest should update the algorithm type to LineMutations_SwapLine and execute successfuly.

            constexpr int expectedBufferSize{sizeof(utf8Input_) + 1};

            RunSetTestCaseMethod(AlgorithmType::LineMutations_SwapLine, expectedBufferSize, baseEntry);
        }
    }
}

TEST_F(InitializedRadamsaMutatorTest, TestCreateTestCase_ErroneousInputs)
{
    {
        // Erroneous Input - This subtest should trigger a runtime exception since the base entry is null.

        EXPECT_THROW(mutateTestCase(storage_, nullptr), RuntimeException);
    }

    {
        // Erroneous Input - This subtest should trigger a runtime exception since the algorithm type is Unknown.

        StorageEntry* baseEntry{GetBaseEntry(asciiInput_, sizeof(asciiInput_))};

        constexpr int expectedBufferSize_noop{0};

        EXPECT_THROW(RunSetTestCaseMethod(AlgorithmType::Unknown, expectedBufferSize_noop, baseEntry), RuntimeException);
    }
}
}

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

#include "gtest/gtest.h"
#include "ModuleTestHelper.hpp"
#include "SimpleStorage.hpp"
#include "RadamsaInsertUnicodeMutator.hpp"
#include "RuntimeException.hpp"

using vmf::StorageModule;
using vmf::StorageRegistry;
using vmf::ModuleTestHelper;
using vmf::TestConfigInterface;
using vmf::SimpleStorage;
using vmf::StorageEntry;
using vmf::RadamsaInsertUnicodeMutator;
using vmf::BaseException;
using vmf::RuntimeException;

class RadamsaInsertUnicodeMutatorTest : public ::testing::Test {
  protected:
    RadamsaInsertUnicodeMutatorTest() 
    {
      storage = new SimpleStorage("storage");
      registry = new StorageRegistry("TEST_INT", StorageRegistry::INT, StorageRegistry::ASCENDING);
      metadata = new StorageRegistry();
      testHelper = new ModuleTestHelper();
      theMutator = new RadamsaInsertUnicodeMutator("RadamsaInsertUnicodeMutator");
      config = testHelper -> getConfig();
    }

    ~RadamsaInsertUnicodeMutatorTest() override {}

    void SetUp() override {
      testCaseKey = registry->registerKey(
          "TEST_CASE", 
          StorageRegistry::BUFFER, 
          StorageRegistry::READ_WRITE
      );
      // int_key = registry->registerKey(
      //     "TEST_INT",
      //     StorageRegistry::INT,
      //     StorageRegistry::READ_WRITE
      // );
      // normalTag = registry->registerTag(
      //     "RAN_SUCCESSFULLY",
      //     StorageRegistry::WRITE_ONLY
      // );
      // // registry->validateRegistration();
      storage->configure(registry, metadata);
      theMutator->init(*config);
      theMutator->registerStorageNeeds(*registry);
      theMutator->registerMetadataNeeds(*metadata);
    }

    void TearDown() override {
      delete registry;
      delete metadata;
      delete storage;
    }

    RadamsaInsertUnicodeMutator* theMutator;
    StorageModule* storage;
    StorageRegistry* registry;
    StorageRegistry* metadata;
    ModuleTestHelper* testHelper;
    TestConfigInterface* config;
    int testCaseKey;
};

/* NOTE
 * Due to the shear amount of cases added by funnyUnicode,
 * and the fact that we can't currently control values
 * returned by VmfRand, these tests will be simplified.
 */

/*TEST_F(RadamsaInsertUnicodeMutatorTest, BufferNotNull)
{
    // no way to test this without mocks
}*/

TEST_F(RadamsaInsertUnicodeMutatorTest, OneByte)
{   
    std::string buffString = "g";

    StorageEntry* baseEntry = storage->createNewEntry();
    StorageEntry* modEntry = storage->createNewEntry();
    char* modBuff;

    const size_t buff_len = buffString.length();
    char* buff = baseEntry->allocateBuffer(testCaseKey, buff_len);
    for(size_t i{0}; i < buff_len; ++i) {
        buff[i] = buffString[i];
    }
    try{
        theMutator->mutateTestCase(*storage, baseEntry, modEntry, testCaseKey);
        modBuff = modEntry->getBufferPointer(testCaseKey);
    } 
    catch (BaseException e)
    {
        FAIL() << "Exception thrown: " << e.getReason();
    }

    size_t modBuff_len = modEntry->getBufferSize(testCaseKey);

    EXPECT_GT(modBuff_len, buff_len + 1);
    EXPECT_TRUE(
        modBuff[0] == buff[0] || 
        modBuff[modBuff_len - 2] == buff[0]
    ) << "modBuff[0]: " + std::to_string(modBuff[0]) + 
    ", modBuff[modBuff_len - 2]: " + std::to_string(modBuff[modBuff_len - 2]);
}

TEST_F(RadamsaInsertUnicodeMutatorTest, TwoBytes)
{   
    std::string buffString = "gh";

    StorageEntry* baseEntry = storage->createNewEntry();
    StorageEntry* modEntry = storage->createNewEntry();
    char* modBuff;

    const size_t buff_len = buffString.length();
    char* buff = baseEntry->allocateBuffer(testCaseKey, buff_len);
    for(size_t i{0}; i < buff_len; ++i) {
        buff[i] = buffString[i];
    }
    try{
        theMutator->mutateTestCase(*storage, baseEntry, modEntry, testCaseKey);
        modBuff = modEntry->getBufferPointer(testCaseKey);
    } 
    catch (BaseException e)
    {
        FAIL() << "Exception thrown: " << e.getReason();
    }

    size_t modBuff_len = modEntry->getBufferSize(testCaseKey);

    EXPECT_GT(modBuff_len, buff_len + 1);
    if (modBuff[0] == buff[0]) {    // "ghFOO" or "gFOOh"
        EXPECT_TRUE(
            modBuff[1] == buff[1] || 
            modBuff[modBuff_len - 2] == buff[1]
        ) << "modBuff[1]: " + std::to_string(modBuff[1]) + 
        ", modBuff[modBuff_len - 2]: " + std::to_string(modBuff[modBuff_len - 2]);
    }
    else  { // "FOOgh"
        EXPECT_EQ(modBuff[modBuff_len - 2], buff[buff_len - 1]);
        EXPECT_EQ(modBuff[modBuff_len - 3], buff[buff_len - 2]);
    }
}
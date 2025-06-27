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
#include "RadamsaDeleteByteSequenceMutator.hpp"
#include "RuntimeException.hpp"

using vmf::StorageModule;
using vmf::StorageRegistry;
using vmf::ModuleTestHelper;
using vmf::TestConfigInterface;
using vmf::SimpleStorage;
using vmf::StorageEntry;
using vmf::RadamsaDeleteByteSequenceMutator;
using vmf::BaseException;
using vmf::RuntimeException;

class RadamsaDeleteByteSequenceMutatorTest : public ::testing::Test {
  protected:
    RadamsaDeleteByteSequenceMutatorTest() 
    {
      storage = new SimpleStorage("storage");
      registry = new StorageRegistry("TEST_INT", StorageRegistry::INT, StorageRegistry::ASCENDING);
      metadata = new StorageRegistry();
      testHelper = new ModuleTestHelper();
      theMutator = new RadamsaDeleteByteSequenceMutator("RadamsaDeleteByteSequenceMutator");
      config = testHelper -> getConfig();
    }

    ~RadamsaDeleteByteSequenceMutatorTest() override {}

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

    RadamsaDeleteByteSequenceMutator* theMutator;
    StorageModule* storage;
    StorageRegistry* registry;
    StorageRegistry* metadata;
    ModuleTestHelper* testHelper;
    TestConfigInterface* config;
    int testCaseKey;
};

/*TEST_F(RadamsaDeleteByteSequenceMutatorTest, BufferNotNull)
{
    // no way to test this without mocks
}*/

TEST_F(RadamsaDeleteByteSequenceMutatorTest, BufferSizeGEOne)
{    
    StorageEntry* baseEntry = storage->createNewEntry();
    StorageEntry* modEntry = storage->createNewEntry();

    // char* buff = baseEntry->allocateBuffer(testCaseKey, 1);
    /* By not allocating the buffer, we're forcing 
    StorageEntry::getBufferSize() to return '-1'.
    */

    try{
        theMutator->mutateTestCase(*storage, baseEntry, modEntry, testCaseKey);
        ADD_FAILURE() << "No exception thrown";
    } 
    catch (RuntimeException e)
    {
        EXPECT_EQ(e.getErrorCode(), e.USAGE_ERROR);
    }
    catch (BaseException e)
    {
        FAIL() << "Unexpected Exception thrown: " << e.getReason();
    }
}

TEST_F(RadamsaDeleteByteSequenceMutatorTest, BufferSizeGETwo)
{   
    StorageEntry* baseEntry = storage->createNewEntry();
    StorageEntry* modEntry = storage->createNewEntry();

    size_t buff_len = 1;
    char* buff = baseEntry->allocateBuffer(testCaseKey, buff_len);
    buff[0] = '4';

    try{
        theMutator->mutateTestCase(*storage, baseEntry, modEntry, testCaseKey);
        ADD_FAILURE() << "No exception thrown";
    }
    catch (RuntimeException e)
    {
        EXPECT_EQ(e.getErrorCode(), e.USAGE_ERROR);
    }
    catch (BaseException e)
    {
        FAIL() << "Unexpected Exception thrown: " << e.getReason();
    }
}

TEST_F(RadamsaDeleteByteSequenceMutatorTest, TwoBytes)
{   
    StorageEntry* baseEntry = storage->createNewEntry();
    StorageEntry* modEntry = storage->createNewEntry();

    const size_t buff_len = 2;
    char* modBuff;
    char* buff = baseEntry->allocateBuffer(testCaseKey, buff_len);
    buff[0] = '4';
    buff[1] = '5';

    try{
        theMutator->mutateTestCase(*storage, baseEntry, modEntry, testCaseKey);
        modBuff = modEntry->getBufferPointer(testCaseKey);
    } 
    catch (BaseException e)
    {
        FAIL() << "Exception thrown: " << e.getReason();
    }

    size_t modBuff_len = modEntry->getBufferSize(testCaseKey);
    std::string modString = std::string(modBuff);
    size_t occ[buff_len] = {};

    for(size_t i = 0; i < modBuff_len; ++i) {
        if(modBuff[i] == '4') {
            occ[0]++;
        }
        else if(modBuff[i] == '5') {
            occ[1]++;
        }
    }

    // test buff ne
    // ASSERT_FALSE(std::equal(buff,       buff + buff_len, 
    //                         modBuff,    modBuff + modBuff_len - 1)
    //             );
    // test buff len
    EXPECT_LT(modBuff_len, buff_len + 1);
    // test buff contents
    EXPECT_LT(occ[0], 2);
    EXPECT_LT(occ[1], 2);
    EXPECT_FALSE(occ[0] == 1 && occ[1] == 1);
}

TEST_F(RadamsaDeleteByteSequenceMutatorTest, ThreeBytes)
{   
    StorageEntry* baseEntry = storage->createNewEntry();
    StorageEntry* modEntry = storage->createNewEntry();

    const size_t buff_len = 3;
    char* modBuff;
    char* buff = baseEntry->allocateBuffer(testCaseKey, buff_len);
    buff[0] = '4';
    buff[1] = '5';
    buff[2] = '6';

    try{
        theMutator->mutateTestCase(*storage, baseEntry, modEntry, testCaseKey);
        modBuff = modEntry->getBufferPointer(testCaseKey);
    } 
    catch (BaseException e)
    {
        FAIL() << "Exception thrown: " << e.getReason();
    }

    size_t modBuff_len = modEntry->getBufferSize(testCaseKey);
    std::string modString = std::string(modBuff);
    size_t occ[buff_len] = {};

    for(size_t i = 0; i < modBuff_len; ++i) {
        if(modBuff[i] == '4') {
            occ[0]++;
        }
        else if(modBuff[i] == '5') {
            occ[1]++;
        }
        else if(modBuff[i] == '6') {
            occ[2]++;
        }
    }

    // test buff ne
    // ASSERT_FALSE(std::equal(buff,       buff + buff_len, 
    //                         modBuff,    modBuff + modBuff_len - 1)
    //             );
    // test buff len
    EXPECT_LT(modBuff_len, buff_len + 1);
    // test buff contents
    EXPECT_LT(occ[0], 2);
    EXPECT_LT(occ[1], 2);
    EXPECT_LT(occ[2], 2);
    EXPECT_FALSE(occ[0] == 1 && occ[1] == 1 && occ[2] == 1);
}

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
#include "RadamsaDeleteLineMutator.hpp"
#include "RuntimeException.hpp"

using vmf::StorageModule;
using vmf::StorageRegistry;
using vmf::ModuleTestHelper;
using vmf::TestConfigInterface;
using vmf::SimpleStorage;
using vmf::StorageEntry;
using vmf::RadamsaDeleteLineMutator;
using vmf::BaseException;
using vmf::RuntimeException;

class RadamsaDeleteLineMutatorTest : public ::testing::Test {
  protected:
    RadamsaDeleteLineMutatorTest() 
    {
      storage = new SimpleStorage("storage");
      registry = new StorageRegistry("TEST_INT", StorageRegistry::INT, StorageRegistry::ASCENDING);
      metadata = new StorageRegistry();
      testHelper = new ModuleTestHelper();
      theMutator = new RadamsaDeleteLineMutator("RadamsaDeleteLineMutator");
      config = testHelper -> getConfig();
    }

    ~RadamsaDeleteLineMutatorTest() override {}

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

    RadamsaDeleteLineMutator* theMutator;
    StorageModule* storage;
    StorageRegistry* registry;
    StorageRegistry* metadata;
    ModuleTestHelper* testHelper;
    TestConfigInterface* config;
    int testCaseKey;
};

/*TEST_F(RadamsaDeleteLineMutatorTest, BufferNotNull)
{
    // no way to test this without mocks
}*/

TEST_F(RadamsaDeleteLineMutatorTest, BufferSizeGEOne)
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

TEST_F(RadamsaDeleteLineMutatorTest, OneLine)
{    
    StorageEntry* baseEntry = storage->createNewEntry();
    StorageEntry* modEntry = storage->createNewEntry();

    size_t buff_len = 2;
    size_t line_len = 2;
    char* modBuff;
    char* buff = baseEntry->allocateBuffer(testCaseKey, buff_len);
    buff[0] = '4';
    buff[1] = '\n';

    try{
        theMutator->mutateTestCase(*storage, baseEntry, modEntry, testCaseKey);
        modBuff = modEntry->getBufferPointer(testCaseKey);
    } 
    catch (BaseException e)
    {
        FAIL() << "Exception thrown: " << e.getReason();
    }

    std::string modString = std::string(modBuff);
    size_t modBuff_len = modEntry->getBufferSize(testCaseKey);

    EXPECT_FALSE(std::equal(buff,       buff + buff_len, 
                            modBuff,    modBuff + modBuff_len - 1)
                ) << "Modified buffer must not be equal to original buffer";

    EXPECT_EQ(buff_len / line_len - 1, 
              std::count(modBuff, modBuff + buff_len, '\n')
              ) << "Number of lines in modified buffer must be one less than those in the original buffer";

    EXPECT_EQ(buff_len - line_len + 1, modBuff_len
             ) << "Modified buffer length must be equal to the original buffer less one line plus one";
    
    EXPECT_EQ(modString, "\0");
}

TEST_F(RadamsaDeleteLineMutatorTest, TwoLines)
{    
    StorageEntry* baseEntry = storage->createNewEntry();
    StorageEntry* modEntry = storage->createNewEntry();

    size_t buff_len = 4;
    size_t line_len = 2;
    char* modBuff;
    char* buff = baseEntry->allocateBuffer(testCaseKey, buff_len);
    buff[0] = '4';
    buff[1] = '\n';
    buff[2] = '5';
    buff[3] = '\n';

    try{
        theMutator->mutateTestCase(*storage, baseEntry, modEntry, testCaseKey);
        modBuff = modEntry->getBufferPointer(testCaseKey);
    } 
    catch (BaseException e)
    {
        FAIL() << "Exception thrown: " << e.getReason();
    }

    // test buff ne
    ASSERT_FALSE(std::equal(buff,       buff + buff_len, 
                            modBuff,    modBuff + modEntry->getBufferSize(testCaseKey) - 1));
    // test number of lines in buff
    EXPECT_EQ(buff_len / line_len - 1, 
               std::count(modBuff, modBuff + buff_len, '\n'));
    // test buff len
    EXPECT_EQ(buff_len - line_len + 1, modEntry->getBufferSize(testCaseKey));
    // test buff contents
    std::string modString = std::string(modBuff);
    EXPECT_TRUE(modString == "4\n\0" | 
                modString == "5\n\0");
}

TEST_F(RadamsaDeleteLineMutatorTest, ThreeLines)
{    
    StorageEntry* baseEntry = storage->createNewEntry();
    StorageEntry* modEntry = storage->createNewEntry();

    size_t buff_len = 6;
    size_t line_len = 2;
    char* modBuff;
    char* buff = baseEntry->allocateBuffer(testCaseKey, buff_len);
    buff[0] = '4';
    buff[1] = '\n';
    buff[2] = '5';
    buff[3] = '\n';
    buff[4] = '6';
    buff[5] = '\n';

    try{
        theMutator->mutateTestCase(*storage, baseEntry, modEntry, testCaseKey);
        modBuff = modEntry->getBufferPointer(testCaseKey);
    } 
    catch (BaseException e)
    {
        FAIL() << "Exception thrown: " << e.getReason();
    }

    // test buff ne
    ASSERT_FALSE(std::equal(buff,       buff + buff_len, 
                            modBuff,    modBuff + modEntry->getBufferSize(testCaseKey) - 1));
    // test number of lines in buff
    EXPECT_EQ(buff_len / line_len - 1, 
               std::count(modBuff, modBuff + buff_len, '\n'));
    // test buff len
    EXPECT_EQ(buff_len - line_len + 1, modEntry->getBufferSize(testCaseKey));
    // test buff contents
    std::string modString = std::string(modBuff);
    EXPECT_TRUE(modString == "4\n5\n\0" | 
                modString == "5\n6\n\0" | 
                modString == "4\n6\n\0");
}
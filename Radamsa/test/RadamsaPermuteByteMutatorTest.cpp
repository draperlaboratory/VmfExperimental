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
#include "RadamsaPermuteByteMutator.hpp"

using vmf::StorageModule;
using vmf::StorageRegistry;
using vmf::ModuleTestHelper;
using vmf::TestConfigInterface;
using vmf::SimpleStorage;
using vmf::StorageEntry;
using vmf::RadamsaPermuteByteMutator;
using vmf::BaseException;

class RadamsaPermuteByteMutatorTest : public ::testing::Test {
  protected:
    RadamsaPermuteByteMutatorTest() 
    {
      storage = new SimpleStorage("storage");
      registry = new StorageRegistry("TEST_INT", StorageRegistry::INT, StorageRegistry::ASCENDING);
      metadata = new StorageRegistry();
      testHelper = new ModuleTestHelper();
      theMutator = new RadamsaPermuteByteMutator("RadamsaPermuteByteMutator");
      config = testHelper -> getConfig();
    }

    ~RadamsaPermuteByteMutatorTest() override {}

    void SetUp() override {
      testCaseKey = registry->registerKey(
          "TEST_CASE", 
          StorageRegistry::BUFFER, 
          StorageRegistry::READ_WRITE
      );
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

    RadamsaPermuteByteMutator* theMutator;
    StorageModule* storage;
    StorageRegistry* registry;
    StorageRegistry* metadata;
    ModuleTestHelper* testHelper;
    TestConfigInterface* config;
    int testCaseKey;
};

//TODO: flip byte in this case?
TEST_F(RadamsaPermuteByteMutatorTest, TestPermuteSingleByte)
{
  StorageEntry* baseEntry = storage->createNewEntry();
  StorageEntry* modEntry = storage->createNewEntry();

  int buff_len = 1;
  char* buff = baseEntry->allocateBuffer(testCaseKey, buff_len);
  buff[0] = '4';

  try{
      theMutator->mutateTestCase(*storage, baseEntry, modEntry, testCaseKey);
  } 
  catch (BaseException e)
  {
    FAIL() << "Exception thrown: " << e.getReason();
  }

  char* modBuff = modEntry->getBufferPointer(testCaseKey);
  // ASSERT_FALSE(std::equal(buff,       buff + buff_len, 
  //                         modBuff,    modBuff + modEntry->getBufferSize(testCaseKey) - 1));
  EXPECT_EQ(buff_len + 1, modEntry->getBufferSize(testCaseKey));
  EXPECT_EQ(modBuff[0], '4');
}

TEST_F(RadamsaPermuteByteMutatorTest, TestPermuteTwoBytes)
{
  StorageEntry* baseEntry = storage->createNewEntry();
  StorageEntry* modEntry = storage->createNewEntry();

  int buff_len = 2;
  char* buff = baseEntry->allocateBuffer(testCaseKey, buff_len);
  buff[0] = '4';
  buff[1] = '5';

  try{
      theMutator->mutateTestCase(*storage, baseEntry, modEntry, testCaseKey);
  } 
  catch (BaseException e)
  {
    FAIL() << "Exception thrown: " << e.getReason();
  }

  char* modBuff = modEntry->getBufferPointer(testCaseKey);
  // ASSERT_FALSE(std::equal(buff,       buff + buff_len, 
  //                         modBuff,    modBuff + modEntry->getBufferSize(testCaseKey) - 1));
  EXPECT_EQ(buff_len + 1, modEntry->getBufferSize(testCaseKey));
  EXPECT_TRUE(std::is_permutation(buff, buff+buff_len, modBuff));
}

TEST_F(RadamsaPermuteByteMutatorTest, TestPermuteThreeBytes)
{
  StorageEntry* baseEntry = storage->createNewEntry();
  StorageEntry* modEntry = storage->createNewEntry();

  int buff_len = 3;
  char* buff = baseEntry->allocateBuffer(testCaseKey, buff_len);
  buff[0] = '4';
  buff[1] = '5';
  buff[2] = '6';

  try{
      theMutator->mutateTestCase(*storage, baseEntry, modEntry, testCaseKey);
  } 
  catch (BaseException e)
  {
    FAIL() << "Exception thrown: " << e.getReason();
  }

  char* modBuff = modEntry->getBufferPointer(testCaseKey);
  // ASSERT_FALSE(std::equal(buff,       buff + buff_len, 
  //                         modBuff,    modBuff + modEntry->getBufferSize(testCaseKey) - 1));
  EXPECT_EQ(buff_len + 1, modEntry->getBufferSize(testCaseKey));
  EXPECT_TRUE(std::is_permutation(buff, buff+buff_len, modBuff));
}
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
#include "RadamsaReplaceNodeMutator.hpp"
#include "RuntimeException.hpp"

using vmf::StorageModule;
using vmf::StorageRegistry;
using vmf::ModuleTestHelper;
using vmf::TestConfigInterface;
using vmf::SimpleStorage;
using vmf::StorageEntry;
using vmf::RadamsaReplaceNodeMutator;
using vmf::BaseException;
using vmf::RuntimeException;

class RadamsaReplaceNodeMutatorTest : public ::testing::Test {
  protected:
    RadamsaReplaceNodeMutatorTest() 
    {
      storage = new SimpleStorage("storage");
      registry = new StorageRegistry("TEST_INT", StorageRegistry::INT, StorageRegistry::ASCENDING);
      metadata = new StorageRegistry();
      testHelper = new ModuleTestHelper();
      theMutator = new RadamsaReplaceNodeMutator("RadamsaReplaceNodeMutator");
      config = testHelper -> getConfig();
    }

    ~RadamsaReplaceNodeMutatorTest() override {}

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

    RadamsaReplaceNodeMutator* theMutator;
    StorageModule* storage;
    StorageRegistry* registry;
    StorageRegistry* metadata;
    ModuleTestHelper* testHelper;
    TestConfigInterface* config;
    int testCaseKey;
};

/*TEST_F(RadamsaReplaceNodeMutatorTest, BufferNotNull)
{
    // no way to test this without mocks
}*/

TEST_F(RadamsaReplaceNodeMutatorTest, ThreeBytes)
{   
    std::string buffString = "GHI";

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

TEST_F(RadamsaReplaceNodeMutatorTest, JustRoot)
{   
    std::string buffString = "GHIJ";

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

TEST_F(RadamsaReplaceNodeMutatorTest, OneChild)
{   
    std::string buffString = "GH(IJ)";

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
    std::string modString = std::string(modBuff);

    // test buff len
    EXPECT_EQ(modBuff_len, buff_len + 1);
    // test buff contents
    EXPECT_TRUE(
        modString == "IJ(IJ)\0" ||
        modString == "GH(GH)\0"
    );
}

TEST_F(RadamsaReplaceNodeMutatorTest, TwoChildren)
{   
    std::string buffString = "GH(IJ)(KL)";

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
    std::string modString = std::string(modBuff);

    // test buff len
    EXPECT_EQ(modBuff_len, buff_len + 1);
    // test buff contents
    EXPECT_TRUE(
        modString == "GH(IJ)(KL)" ||    // toCopy == toReplace
        modString == "GH(GH)(KL)" ||    // toCopy == root
        modString == "GH(IJ)(GH)" ||
        modString == "IJ(IJ)(KL)" ||    // toCopy == left
        modString == "GH(IJ)(IJ)" ||
        modString == "KL(IJ)(KL)" ||    // toCopy == right
        modString == "GH(KL)(KL)"
    );
}

TEST_F(RadamsaReplaceNodeMutatorTest, TwoChildren_OneGrandchild)
{   
    std::string buffString = "GH(IJ(KL))(MN)";

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
    std::string modString = std::string(modBuff);

    // test buff len
    EXPECT_EQ(modBuff_len, buff_len + 1);
    // test buff contents
    EXPECT_TRUE(
        modString == "GH(IJ(KL))(MN)" ||    // toCopy == toReplace
        modString == "GH(GH(KL))(MN)" ||    // toCopy == root
        modString == "GH(IJ(GH))(MN)" ||    
        modString == "GH(IJ(KL))(GH)" ||    
        modString == "IJ(IJ(KL))(MN)" ||    // toCopy == left
        modString == "GH(IJ(IJ))(MN)" ||    
        modString == "GH(IJ(KL))(IJ)" ||
        modString == "MN(IJ(KL))(MN)" ||    // toCopy == right
        modString == "GH(MN(KL))(MN)" ||
        modString == "GH(IJ(MN))(MN)" ||
        modString == "KL(IJ(KL))(MN)" ||    // toCopy == grandchild
        modString == "GH(KL(KL))(MN)" ||
        modString == "GH(IJ(KL))(KL)"
    );
}
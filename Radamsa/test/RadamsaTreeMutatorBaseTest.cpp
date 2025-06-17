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
#include "RadamsaTreeMutatorBase.hpp"
#include "RuntimeException.hpp"

using vmf::StorageModule;
using vmf::StorageRegistry;
using vmf::ModuleTestHelper;
using vmf::TestConfigInterface;
using vmf::SimpleStorage;
using vmf::StorageEntry;
using vmf::RadamsaTreeMutatorBase;
using vmf::BaseException;
using vmf::RuntimeException;

class RadamsaTreeMutatorBaseTest : public ::testing::Test {
  protected:
    RadamsaTreeMutatorBase::Tree tr;

    RadamsaTreeMutatorBaseTest() = default;
    ~RadamsaTreeMutatorBaseTest() = default;
};

TEST_F(RadamsaTreeMutatorBaseTest, EmptyTreeStr)
{   
    std::string treeStr = "";

    try{
        tr = RadamsaTreeMutatorBase::Tree(treeStr);
        ADD_FAILURE() << "No exception thrown";
    }
    catch (RuntimeException e)
    {
        EXPECT_EQ(e.getErrorCode(), e.UNEXPECTED_ERROR);
    }
    catch (BaseException e)
    {
        FAIL() << "Unexpected Exception thrown: " << e.getReason();
    }
}

TEST_F(RadamsaTreeMutatorBaseTest, NoRoot)
{   
    std::string treeStr = "(G)";

    try{
        tr = RadamsaTreeMutatorBase::Tree(treeStr);
        ADD_FAILURE() << "No exception thrown";
    }
    catch (RuntimeException e)
    {
        EXPECT_EQ(e.getErrorCode(), e.UNEXPECTED_ERROR);
    }
    catch (BaseException e)
    {
        FAIL() << "Unexpected Exception thrown: " << e.getReason();
    }
}

TEST_F(RadamsaTreeMutatorBaseTest, DanglingCloseBracket)
{   
    std::string treeStr = "G)";

    try{
        tr = RadamsaTreeMutatorBase::Tree(treeStr);
        ADD_FAILURE() << "No exception thrown";
    }
    catch (RuntimeException e)
    {
        EXPECT_EQ(e.getErrorCode(), e.UNEXPECTED_ERROR);
    }
    catch (BaseException e)
    {
        FAIL() << "Unexpected Exception thrown: " << e.getReason();
    }
}

TEST_F(RadamsaTreeMutatorBaseTest, UnmatchedOpenBracket)
{   
    std::string treeStr = "G(";

    try{
        tr = RadamsaTreeMutatorBase::Tree(treeStr);
        ADD_FAILURE() << "No exception thrown";
    }
    catch (RuntimeException e)
    {
        EXPECT_EQ(e.getErrorCode(), e.UNEXPECTED_ERROR);
    }
    catch (BaseException e)
    {
        FAIL() << "Unexpected Exception thrown: " << e.getReason();
    }
}

TEST_F(RadamsaTreeMutatorBaseTest, JustRoot)
{   
    const std::string treeStr = "G";

    try{
        this->tr = RadamsaTreeMutatorBase::Tree(treeStr);
    }
    catch (BaseException e)
    {
        FAIL() << "Exception thrown: " << e.getReason();
    }

    EXPECT_EQ(treeStr, tr.toString(tr.root));
}

TEST_F(RadamsaTreeMutatorBaseTest, OneChild)
{   
    const std::string treeStr = "GH(IJ)";

    try{
        this->tr = RadamsaTreeMutatorBase::Tree(treeStr);
    }
    catch (BaseException e)
    {
        FAIL() << "Exception thrown: " << e.getReason();
    }

    EXPECT_EQ(treeStr, tr.toString(tr.root));
}

TEST_F(RadamsaTreeMutatorBaseTest, TwoChildren)
{   
    const std::string treeStr = "GH(IJ)(KL)";

    try{
        this->tr = RadamsaTreeMutatorBase::Tree(treeStr);
    }
    catch (BaseException e)
    {
        FAIL() << "Exception thrown: " << e.getReason();
    }

    EXPECT_EQ(treeStr, tr.toString(tr.root));
}

TEST_F(RadamsaTreeMutatorBaseTest, TwoChildren_OneGrandchild)
{   
    const std::string treeStr = "GH(IJ(KL))(MN)";

    try{
        this->tr = RadamsaTreeMutatorBase::Tree(treeStr);
    }
    catch (BaseException e)
    {
        FAIL() << "Exception thrown: " << e.getReason();
    }

    EXPECT_EQ(treeStr, tr.toString(tr.root));
}
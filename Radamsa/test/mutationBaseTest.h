/* =============================================================================
* Vader Modular Fuzzer
* Copyright (c) 2021-2023 The Charles Stark Draper Laboratory, Inc.
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

// Google Test Includes
#include "gtest/gtest.h"

// VMF Includes
#include "mutationBase.hpp"

namespace vmf::test::modules::radamsa::mutations
{
class MutationBaseTest : public ::testing::Test,
                         public ::vmf::radamsa::mutations::MutationBase
{
public:
    virtual ~MutationBaseTest() = default;

    MutationBaseTest() : ::vmf::radamsa::mutations::MutationBase{randomNumberGenerator_} {}

protected:

private:
    std::default_random_engine randomNumberGenerator_;
};
}

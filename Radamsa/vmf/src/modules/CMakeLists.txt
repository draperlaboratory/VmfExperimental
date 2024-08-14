#===============================================================================
# Vader Modular Fuzzer (VMF)
# Copyright (c) 2021-2023 The Charles Stark Draper Laboratory, Inc.
# <vader@draper.com>
#  
# Effort sponsored by the U.S. Government under Other Transaction number
# W9124P-19-9-0001 between AMTC and the Government. The U.S. Government
# Is authorized to reproduce and distribute reprints for Governmental purposes
# notwithstanding any copyright notation thereon.
#  
# The views and conclusions contained herein are those of the authors and
# should not be interpreted as necessarily representing the official policies
# or endorsements, either expressed or implied, of the U.S. Government.
#  
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 (only) as 
# published by the Free Software Foundation.
#  
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#  
# @license GPL-2.0-only <https://spdx.org/licenses/GPL-2.0-only.html>
#===============================================================================

# Create Radamsa library
add_library(Radamsa SHARED
#  common/mutator/byteMutations.cpp
#  common/mutator/radamsaMutator.cpp
#  common/mutator/lineMutations.cpp
  common/mutator/RadamsaDropByteMutator.cpp
  common/mutator/RadamsaFlipByteMutator.cpp
  common/mutator/RadamsaInsertByteMutator.cpp
)

# Build-time dependencies for Radamsa
link_directories(Radamsa PRIVATE
)

# Build-time dependencies for Radamsa
target_link_libraries(Radamsa PRIVATE
)

# Build-time dependencies for Radamsa
target_include_directories(Radamsa PRIVATE
  ${VMF_INSTALL}/include
  ${VMF_INSTALL}/include/vmf
  ${VMF_INSTALL}/include/plog
  ${PROJECT_SOURCE_DIR}/src/module
)

# Install Radamsa library in VMF plugins directory
install(TARGETS Radamsa
  LIBRARY DESTINATION "${VMF_INSTALL}/plugins")


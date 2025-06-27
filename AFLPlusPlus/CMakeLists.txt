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

# Create AFLPlusPlus library
add_library(AFLPlusPlus SHARED
  src/module/AFLCloneMutator.cpp
  src/module/AFLDeleteMutator.cpp
  src/module/AFLDWordAddSubMutator.cpp
  src/module/AFLFlip2BitMutator.cpp
  src/module/AFLFlip2ByteMutator.cpp
  src/module/AFLFlip4BitMutator.cpp
  src/module/AFLFlip4ByteMutator.cpp
  src/module/AFLFlipBitMutator.cpp
  src/module/AFLFlipByteMutator.cpp
  src/module/AFLInteresting8Mutator.cpp
  src/module/AFLInteresting16Mutator.cpp
  src/module/AFLInteresting32Mutator.cpp
  src/module/AFLOverwriteCopyMutator.cpp
  src/module/AFLOverwriteFixedMutator.cpp
  src/module/AFLRandomByteAddSubMutator.cpp
  src/module/AFLRandomByteMutator.cpp
  src/module/AFLSpliceMutator.cpp
  src/module/AFLWordAddSubMutator.cpp
)

# Build-time dependencies for AFLPlusPlus
link_directories(AFLPlusPlus PRIVATE
)

# Build-time dependencies for AFLPlusPlus
target_link_libraries(AFLPlusPlus PRIVATE
  # ${CMAKE_INSTALL_PREFIX}/bin/vader
  vmf_framework
  # ${CMAKE_INSTALL_PREFIX}/../../submodules/LibAFL-legacy
)

# Build-time dependencies for AFLPlusPlus
target_include_directories(AFLPlusPlus PRIVATE
  ${CMAKE_INSTALL_PREFIX}/include
  ${CMAKE_INSTALL_PREFIX}/include/vmf
  ${CMAKE_INSTALL_PREFIX}/include/plog
  ${PROJECT_SOURCE_DIR}/src/module
)

# Install AFLPlusPlus library in VMF plugins directory
install(TARGETS AFLPlusPlus
  LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/plugins")


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

cmake_minimum_required(VERSION 3.10.2)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Specify project related variables.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER g++)

project(VmfExtension VERSION 1.0 LANGUAGES CXX)

# Check that VMF_INSTALL directory is properly defined, exit with error if not
if (NOT IS_DIRECTORY ${VMF_INSTALL})
  message( FATAL_ERROR "CMake variable VMF_INSTALL must be defined as full path to a VMF install tree, please use cmake -DVMF_INSTALL=/full/path/to/VMF" )
endif()

# Bring in VMF support variables and utility functions
list(APPEND CMAKE_MODULE_PATH "${VMF_INSTALL}/cmake")
include(vmf_imports)
include(vmf)

# ---- TAILOR SPECIFIC EXTENSION PACKAGES HERE ----

# Add in extension package directories
add_subdirectory(${PROJECT_SOURCE_DIR}/SamplePackage)


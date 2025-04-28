#===============================================================================
# Vader Modular Fuzzer (VMF)
# Copyright (c) 2021-2025 The Charles Stark Draper Laboratory, Inc.
# <vmf@draper.com>
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
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER g++)

project(VmfExtension VERSION 1.0 LANGUAGES CXX)

# Check that CMAKE_INSTALL_PREFIX directory is properly defined, exit with error if not
if (NOT IS_DIRECTORY ${CMAKE_INSTALL_PREFIX})
  message( FATAL_ERROR "CMake variable CMAKE_INSTALL_PREFIX must be defined as full path to a VMF install tree, please use cmake -DCMAKE_INSTALL_PREFIX=/full/path/to/VMF" )
endif()

# Bring in VMF support variables and utility functions
list(APPEND CMAKE_MODULE_PATH "${CMAKE_INSTALL_PREFIX}/cmake")
include(vmf_imports)
include(vmf)

# ---- TAILOR SPECIFIC EXTENSION PACKAGES HERE ----

# Add in extension package directories
add_subdirectory(${PROJECT_SOURCE_DIR}/Determinism)
add_subdirectory(${PROJECT_SOURCE_DIR}/Radamsa)
#add_subdirectory(${PROJECT_SOURCE_DIR}/SamplePackage)


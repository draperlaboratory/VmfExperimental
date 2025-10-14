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

# --- VMF workaround patch ---
# The vmf_framework target imported from the installed VMF tree incorrectly sets:
#   - INTERFACE_INCLUDE_DIRECTORIES to "/include"
#   - IMPORTED_LOCATION to "/lib/libVMFFramework.so"
# These paths are invalid or conflict with the actual installed VMF location.
# Since VMF cannot be modified directly, we override the target's include path and library location here.
# This ensures correct compilation and linking against the local VMF install tree.
get_target_property(_vmf_includes vmf_framework INTERFACE_INCLUDE_DIRECTORIES)
list(REMOVE_ITEM _vmf_includes "/include")
list(APPEND _vmf_includes "${CMAKE_INSTALL_PREFIX}/include")
set_target_properties(vmf_framework PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${_vmf_includes}"
  IMPORTED_LOCATION "${CMAKE_INSTALL_PREFIX}/lib/libVMFFramework.so"
)
# -----------------------------

# Configure testing
include(GoogleTest)
enable_testing()
add_subdirectory(${PROJECT_SOURCE_DIR}/test)

# ---- TAILOR SPECIFIC EXTENSION PACKAGES HERE ----

# Add in extension package directories
add_subdirectory(${PROJECT_SOURCE_DIR}/Determinism)
add_subdirectory(${PROJECT_SOURCE_DIR}/AFLPlusPlus)
add_subdirectory(${PROJECT_SOURCE_DIR}/Radamsa)
#add_subdirectory(${PROJECT_SOURCE_DIR}/SamplePackage)


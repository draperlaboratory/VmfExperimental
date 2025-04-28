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

# Create Determinism library
add_library(Determinism SHARED
  common/feedback/AFLDeterministicFeedback.cpp
  common/output/DeterminismTesterOutput.cpp
)

#Set flag to export all symbols for windows builds
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# windows needs an additional import to make the logger work
if(WIN32)
  target_compile_definitions(Determinism PRIVATE PLOG_IMPORT)
endif()

# Build-time dependencies for Determinism
link_directories(Determinism PRIVATE
)

# Build-time dependencies for Determinism
target_link_libraries(Determinism PRIVATE
  vmf_framework
)

# Build-time dependencies for Determinism
target_include_directories(Determinism PRIVATE
  ${CMAKE_INSTALL_PREFIX}/include
  ${CMAKE_INSTALL_PREFIX}/include/vmf
  ${CMAKE_INSTALL_PREFIX}/include/plog
  ${PROJECT_SOURCE_DIR}/src/module
)

# Install Determinism library in VMF plugins directory
install(TARGETS Determinism
  LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/plugins")

#On windows the /plugins directory above is ignored, and everything ends up in /lib and /bin
if(WIN32)
  cmake_path(SET WIN_LIB_FILE ${CMAKE_INSTALL_PREFIX}/lib/Determinism.lib)
  cmake_path(SET WIN_DLL_FILE ${CMAKE_INSTALL_PREFIX}/bin/Determinism.dll)
  install(FILES ${WIN_LIB_FILE} ${WIN_DLL_FILE}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/plugins)
endif()


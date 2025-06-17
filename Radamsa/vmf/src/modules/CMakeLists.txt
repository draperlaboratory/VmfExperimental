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

# Create Radamsa library
add_library(Radamsa SHARED
  common/mutator/RadamsaDropByteMutator.cpp
  common/mutator/RadamsaFlipByteMutator.cpp
  common/mutator/RadamsaInsertByteMutator.cpp
  common/mutator/RadamsaRepeatByteMutator.cpp
  common/mutator/RadamsaPermuteByteMutator.cpp
  common/mutator/RadamsaIncrementByteMutator.cpp
  common/mutator/RadamsaDecrementByteMutator.cpp
  common/mutator/RadamsaRandomizeByteMutator.cpp
  common/mutator/RadamsaDeleteLineMutator.cpp
  common/mutator/RadamsaDeleteSequentialLinesMutator.cpp
  common/mutator/RadamsaDuplicateLineMutator.cpp
  common/mutator/RadamsaCopyLineCloseByMutator.cpp
  common/mutator/RadamsaRepeatLineMutator.cpp
  common/mutator/RadamsaSwapLineMutator.cpp
  common/mutator/RadamsaRepeatByteSequenceMutator.cpp       # -sr
  common/mutator/RadamsaDeleteByteSequenceMutator.cpp       # -sd
  common/mutator/RadamsaPermuteLinesMutator.cpp             # -lp
  common/mutator/RadamsaInsertLineMutator.cpp               # -lis
  common/mutator/RadamsaReplaceLineMutator.cpp              # -lrs
  common/mutator/RadamsaDeleteNodeMutator.cpp               # -td
  common/mutator/RadamsaDuplicateNodeMutator.cpp            # -tr2
  common/mutator/RadamsaReplaceNodeMutator.cpp              # -ts1
  common/mutator/RadamsaSwapNodesMutator.cpp                # -ts2
  common/mutator/RadamsaRepeatPathMutator.cpp               # -tr
  common/mutator/RadamsaWidenCodePointMutator.cpp           # -uw
  common/mutator/RadamsaInsertUnicodeMutator.cpp            # -ui
  common/mutator/RadamsaModifyTextNumberMutator.cpp         # -num
  common/mutator/RadamsaFuseThisMutator.cpp                 # -ft
  common/mutator/RadamsaFuseNextMutator.cpp                 # -fn
  common/mutator/RadamsaFuseOldMutator.cpp                  # -fo
  common/mutator/RadamsaAsciiBadMutator.cpp                 # -ab
)

#Set flag to export all symbols for windows builds
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# windows needs an additional import to make the logger work
if(WIN32)
   target_compile_definitions(Radamsa PRIVATE PLOG_IMPORT)
endif()

# Build-time dependencies for Radamsa
link_directories(Radamsa PRIVATE
)

# Build-time dependencies for Radamsa
target_link_libraries(Radamsa PRIVATE
	vmf_framework
)

# Build-time dependencies for Radamsa
target_include_directories(Radamsa PRIVATE
  ${CMAKE_INSTALL_PREFIX}/include
  ${CMAKE_INSTALL_PREFIX}/include/vmf
  ${CMAKE_INSTALL_PREFIX}/include/plog
  ${PROJECT_SOURCE_DIR}/src/module
)

# Install Radamsa library in VMF plugins directory
install(TARGETS Radamsa
  LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/plugins")

#On windows the /plugins directory above is ignored, and everything ends up in /lib and /bin
if(WIN32)
  cmake_path(SET WIN_LIB_FILE ${CMAKE_INSTALL_PREFIX}/lib/Radamsa.lib)
  cmake_path(SET WIN_DLL_FILE ${CMAKE_INSTALL_PREFIX}/bin/Radamsa.dll)
  install(FILES ${WIN_LIB_FILE} ${WIN_DLL_FILE}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/plugins)
endif()

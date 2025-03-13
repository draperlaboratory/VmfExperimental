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

# Build-time dependencies for Determinism
link_directories(Determinism PRIVATE
)

# Build-time dependencies for Determinism
target_link_libraries(Determinism PRIVATE
)

# Build-time dependencies for Determinism
target_include_directories(Determinism PRIVATE
  ${VMF_INSTALL}/include
  ${VMF_INSTALL}/include/vmf
  ${VMF_INSTALL}/include/plog
  ${PROJECT_SOURCE_DIR}/src/module
)

# Install Determinism library in VMF plugins directory
install(TARGETS Determinism
  LIBRARY DESTINATION "${VMF_INSTALL}/plugins")


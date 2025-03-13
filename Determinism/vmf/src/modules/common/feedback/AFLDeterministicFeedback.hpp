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
#pragma once

#include "FeedbackModule.hpp"

namespace vmf
{

/**
 * @brief Variant of AFLFeedback for achieving determinism (eg for regression tests).
 * It eliminates runtime from the fitness calculation and doesn't save hangs.
 * Not actually a child of AFLFeedback so that it can be built as a standalone module.
 */
class AFLDeterministicFeedback : public FeedbackModule {
public:

    static Module* build(std::string name);
    virtual void init(ConfigInterface& config);

    virtual void registerStorageNeeds(StorageRegistry& registry);
    virtual void evaluateTestCaseResults(StorageModule& storage, std::unique_ptr<Iterator>& entries);

    /**
     * @brief Construct a new AFLDeterministicFeedback object
     * 
     * @param name the module name
     */
    AFLDeterministicFeedback(std::string name);

    virtual ~AFLDeterministicFeedback();

protected:
    virtual float computeFitness(StorageModule& storage, StorageEntry* e);
    uint getExecTimeMs(StorageEntry* e);
    std::string outputDir; ///< Location of output directory

    int testCaseKey; ///< Handle for the "TEST_CASE" field
    int coverageByteCountKey; ///< Handle for the "COVERAGE_COUNT" field
    int fitnessKey; ///< Handle for the "FITNESS" field
    int hasNewCoverageTag; ///< Handle for the "HAS_NEW_COVERAGE" tag
    int hungTag; ///< Handle for the "HUNG" tag

    float avgTestCaseSize; ///< The average size (for all test cases that have been evaluated)
    float maxTestCaseSize; ///< The maximum size (for all test cases that have been evaluated)
    float sizeFitnessWeight; ///< A configurable weight to apply to the size factor in computing fitness. Must be >=0.0
    int numTestCases; ///< The total number of test cases that have been evaluated

    bool useCustomWeights; ///< Whether or not custom weights are enabled    
};
}

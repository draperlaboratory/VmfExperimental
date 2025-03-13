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
#include "AFLDeterministicFeedback.hpp"
#include "Logging.hpp"
#include "VmfUtil.hpp"
#include <cmath>

using namespace vmf;

#include "ModuleFactory.hpp"
REGISTER_MODULE(AFLDeterministicFeedback);

/**
 * @brief Builder method to support the ModuleFactory
 * Constructs an instance of this class
 * @return Module* 
 */
Module* AFLDeterministicFeedback::build(std::string name)
{
    return new AFLDeterministicFeedback(name);
}

/**
 * @brief Initialization method
 * Reads in all configuration options for this class
 * 
 * @param config 
 */
void AFLDeterministicFeedback::init(ConfigInterface& config)
{
    outputDir = config.getOutputDir();
    useCustomWeights = config.getBoolParam(getModuleName(),"useCustomWeights", false);
    sizeFitnessWeight = config.getFloatParam(getModuleName(), "sizeWeight", 1.0);

    if(useCustomWeights) 
    {
        if(sizeFitnessWeight < 0.0) 
        {
            throw RuntimeException("One or more Custom Fitness Weights for feedback is invalid",
                    RuntimeException::USAGE_ERROR);
        }
        LOG_INFO << "Fitness weights: size = " << sizeFitnessWeight;
    }
    else   
        LOG_INFO << "Using AFL++ style Fitness algorithm";

    // To hold determinisim, we require a speed weight of 0
    useCustomWeights = true;
}

AFLDeterministicFeedback::AFLDeterministicFeedback(std::string name) :
    FeedbackModule(name)
{
    maxTestCaseSize = 0;
    numTestCases = 0;    
}

AFLDeterministicFeedback::~AFLDeterministicFeedback()
{
}

void AFLDeterministicFeedback::registerStorageNeeds(StorageRegistry& registry)
{
    //Inputs
    testCaseKey = registry.registerKey("TEST_CASE", StorageRegistry::BUFFER, StorageRegistry::READ_ONLY);
    coverageByteCountKey = registry.registerKey("COVERAGE_COUNT", StorageRegistry::UINT, StorageRegistry::READ_ONLY);
    hungTag = registry.registerTag("HUNG", StorageRegistry::READ_ONLY);
    hasNewCoverageTag = registry.registerTag("HAS_NEW_COVERAGE", StorageRegistry::READ_ONLY);

    //Outputs
    fitnessKey = registry.registerKey("FITNESS", StorageRegistry::FLOAT, StorageRegistry::WRITE_ONLY);
}

/* Same as AFLFeedback evaluateTestCaseResults, but doesn't save hangs */
void AFLDeterministicFeedback::evaluateTestCaseResults(StorageModule& storage, std::unique_ptr<Iterator>& entries)
{
    while (entries->hasNext())
    {
        StorageEntry* e = entries->getNext();

        //Compute average metrics
        int size = e->getBufferSize(testCaseKey);
        avgTestCaseSize = ((avgTestCaseSize * numTestCases) + size)/(numTestCases + 1);
        if (size > maxTestCaseSize)
            maxTestCaseSize = size;

        numTestCases++;

	    bool hung = e->hasTag(hungTag);
	
        // Then check to see if any new paths were uncovered by this test case.
	    // For determinism, we save testcases that have new coverage and *didn't* hang
        if (e->hasTag(hasNewCoverageTag) && !hung)
        {
            //Compute the fitness
            float fitness = computeFitness(storage, e);
            if (fitness > 0)
            {
                e->setValue(fitnessKey, fitness);

                //Then save the entry
                storage.saveEntry(e);
            }
        }
    }
}

float AFLDeterministicFeedback::computeFitness(StorageModule& storage, StorageEntry* e)
{
    uint coverage = e->getUIntValue(coverageByteCountKey); 
    int size = e->getBufferSize(testCaseKey);

    float fitness = 0;
    if(useCustomWeights)
    {
        fitness = log10(coverage) + 1;

        // Compute normalized size; use 1 minus the value because they are inversely related to fitness
        float normalizedSize = 1.0 - size / maxTestCaseSize;

        // Apply size weights to fitness
        fitness *= (1.0 + normalizedSize * sizeFitnessWeight);
    }
    else
    {
        //Use an algorithm that is closer to what AFL++ uses
        fitness = 1.0; 
        // Prioritize testcases with high coverage 
        fitness *= log10(coverage) + 1; 
        // Adjust weight based on size of this testcase compared to average
        fitness *= (avgTestCaseSize / size); 

    }

    if (fitness < 0.0)
    {
        //TODO(VADER-1298): Negative fitness values should not happen, but have been observed
        //This code will at least prevent the fuzzer from shutting down if this occurs,
        //as well as log the underlying test case to disk for further analysis.
        LOG_ERROR << "Negative fitness value (this should not be possible) " << fitness;  
        LOG_ERROR << "Inputs were: coverage=" << coverage << ", size=" << size 
                  << " (avg " << avgTestCaseSize << ")";
        char* buffer = e->getBufferPointer(testCaseKey);
        unsigned long id = e->getID();

        // create a file name with id
        std::string filename = std::to_string(id) + "_NegativeFitnessValue";
        VmfUtil::writeBufferToFile(outputDir, filename, buffer, size);
        LOG_ERROR << "Test case logged to output directory with filename " << filename;
        LOG_ERROR << "This test case will be discarded.";
    }

    return fitness;
}
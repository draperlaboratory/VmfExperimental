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
#include "DeterminismTesterOutput.hpp"
#include "VmfUtil.hpp"

using namespace vmf;

#include "ModuleFactory.hpp"
REGISTER_MODULE(DeterminismTesterOutput);

/**
 * @brief Builder method to support the ModuleFactory
 * Constructs an instance of this class
 * @return Module* 
 */
Module* DeterminismTesterOutput::build(std::string name)
{
    return new DeterminismTesterOutput(name);
}

/**
 * @brief Initialization method
 * Reads in all configuration options for this class
 * 
 * @param config 
 */
void DeterminismTesterOutput::init(ConfigInterface& config)
{
}

/**
 * @brief Construct a new DeterminismTesterOutput module
 * 
 * @param name 
 */
DeterminismTesterOutput::DeterminismTesterOutput(std::string name):
    OutputModule(name)
{
    count = 0;
}

/**
 * @brief Destructor
 * 
 */
DeterminismTesterOutput::~DeterminismTesterOutput()
{

}

/**
 * @brief Registers the keys and tags for this module
 * This module needs to read:
 * "TEST_CASE": the test case for a module
 * 
 * @param registry 
 */
void DeterminismTesterOutput::registerStorageNeeds(StorageRegistry& registry)
{
    testCaseKey = registry.registerKey("TEST_CASE", StorageRegistry::BUFFER, StorageRegistry::READ_ONLY);
}

/**
 * @brief Writes all of the new entries with the "CRASHED" tag to disk
 * 
 * Only the binary test case is written to disk
 * 
 * @param storage 
 */
void DeterminismTesterOutput::run(StorageModule& storage)
{
    std::unique_ptr<Iterator> interestingEntries = storage.getNewEntriesThatWillBeSaved();
    while(interestingEntries->hasNext())
    {
        StorageEntry* entry = interestingEntries->getNext();

        int size = entry->getBufferSize(testCaseKey);
        char* buffer = entry->getBufferPointer(testCaseKey);
        unsigned long id = entry->getID();

        // New checksum calculation, plan to move to separate output module
        count++;
        checksum ^= VmfUtil::hashBuffer(buffer, size);
        checksum ^= id * count;
        if (count % 10 == 0)
        {
            LOG_INFO << "Checksum " << count << " = " << checksum;
        }
    }
}

void DeterminismTesterOutput::shutdown(StorageModule& storage)
{
    LOG_INFO << "Checksum " << count << " = " << checksum;
}

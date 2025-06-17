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

#include "RadamsaFuse_helpers.hpp"

using std::string;
using std::vector;

bool isSubset(const string& mod, const string& buff) {
    for (char c : mod) {
        if (buff.find(c) == string::npos) return false;
    }
    return true;
}

bool isValidSelfFuse(const string& mod, const string& buff) {
    // Returns true if you can combine two substrings of buffString to get modString

    for (size_t i = 0; i < buff.size(); ++i) {
        for(size_t j = 0; j < buff.size(); ++j) {
            const string prefix = buff.substr(0, i);
            const string suffix = buff.substr(j); // j to end of buffString
            const string fusion = prefix + suffix;
            if (mod == fusion) return true; 
        }
    }
    return false;
}

vector<string> getPrefixes(const string& data) {
    vector<string> prefixes;
    for (size_t i = 0; i < data.size(); ++i) {
        prefixes.push_back(data.substr(0, i));
    }
    return prefixes;
}

vector<string> getSuffixes(const string& data) {
    vector<string> suffixes;
    for (size_t i = 0; i < data.size(); ++i) {
        suffixes.push_back(data.substr(i));
    }
    return suffixes;
}

bool isValidDoubleFuse(const string& mod, const string& buff) {
    const size_t midpoint = buff.length() / 2;
    const string buff_firstHalf = buff.substr(0, midpoint);
    const string buff_secondHalf = buff.substr(midpoint);

    const vector<string> buff_firstHalf_prefixes = getPrefixes(buff_firstHalf);
    const vector<string> buff_secondHalf_suffixes = getSuffixes(buff_secondHalf);

    vector<string> fusions;
    for (string prefix : buff_firstHalf_prefixes) {
        for (string suffix : buff_secondHalf_suffixes) {
            fusions.push_back(prefix + suffix);
        }
    }

    for (string fusionA : fusions) {
        for (string fusionB : fusions) {
            string doubleFusion = fusionA + fusionB;
            if (mod == doubleFusion) return true;
        }
    }
    return false;
}

bool isValidTripleFuse(const string& mod, const string& buff) {
    // returns true if modString is a form of: prefix(prefix(buffer_firstHalf) + suffix(buffer)) + suffix(buffer_secondHalf)

    const size_t midpoint = buff.length() / 2;
    const string buff_firstHalf = buff.substr(0, midpoint);
    const string buff_secondHalf = buff.substr(midpoint);

    const vector<string> buff_firstHalf_prefixes = getPrefixes(buff_firstHalf);
    const vector<string> buff_suffixes = getSuffixes(buff);
    const vector<string> buff_secondHalf_suffixes = getSuffixes(buff_secondHalf);

    vector<string> ab_fusions;
    for (string prefix : buff_firstHalf_prefixes) {
        for (string suffix : buff_suffixes) {
            ab_fusions.push_back(prefix + suffix);
        }
    }

    vector<string> ab_fusions_prefixes;
    for (string fusion : ab_fusions) {
        vector<string> fusion_prefixes = getPrefixes(fusion);
        ab_fusions_prefixes.insert(
            ab_fusions_prefixes.end(), 
            fusion_prefixes.begin(), 
            fusion_prefixes.end()
        );
    }
    
    for (string prefix : ab_fusions_prefixes) {
        for (string suffix : buff_secondHalf_suffixes) {
            string fusion = prefix + suffix;
            if (mod == fusion) return true;
        }
    }
    return false;
}

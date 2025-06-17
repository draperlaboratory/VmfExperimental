/* =============================================================================
 * Vader Modular Fuzzer
 * Copyright (c) 2021-2023 The Charles Stark Draper Laboratory, Inc.
 * <vmf@draper.com>
 *
 * Effort sponsored by the U.S. Government under Other Transaction number
 * W9124P-19-9-0001 between AMTC and the Government. The U.S. Government
 * is authorized to reproduce and distribute reprints for Governmental purposes
 * notwithstanding any copyright notation thereon.
 *
 * The views and conclusions contained herein are those of the authors and
 * should not be interpreted as necessarily representing the official policies
 * or endorsements, either expressed or implied, of the U.S. Government.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * @license GPL-3.0-or-later <https://spdx.org/licenses/GPL-3.0-or-later>
 * ===========================================================================*/

#pragma once

#include "RadamsaMutatorBase.hpp"
#include <set>
#include <optional>

using std::vector;
using std::isdigit;
using std::pair;
using std::set;
using std::optional;
using std::nullopt;
using std::move;

namespace vmf
{
/**
 *
 */
class RadamsaByteMutatorBase: public RadamsaMutatorBase
{
public:
    struct NumInfo {
        unsigned int value = 0;
        size_t offset = 0;
        size_t length = 0;
    };

    static size_t GetRandomRepetitionLength(VmfRand* rand) noexcept
    {
        constexpr size_t MINIMUM_UPPER_LIMIT{0x2u};
        constexpr size_t MAXIMUM_UPPER_LIMIT{0x20000u};

        size_t randomStop{rand->randBetween(0u, MINIMUM_UPPER_LIMIT)};
        size_t randomUpperLimit{MINIMUM_UPPER_LIMIT};

        while(randomStop != 0u)
        {
            if(randomUpperLimit == MAXIMUM_UPPER_LIMIT)
                break;

            randomUpperLimit <<= 1u;
            randomStop = rand->randBetween(0u, MINIMUM_UPPER_LIMIT);
        }

        return rand->randBetween(0u, randomUpperLimit) + 1u; // We add one to the return value in order to account for the case where the random upper value is zero.
    }

    vector<uint8_t> encodeUtf8(char32_t cp) {
        // encodes 21-bit character code points into UTF-8 values of 1 to 4 bytes

        vector<uint8_t> result;
        if (cp <= 0x7F) {           // 1B case
            result.push_back(cp);       
        } 
        else if (cp <= 0x7FF) {     // 2B case
            result.push_back(0xC0 | (cp >> 6));     // 110xxxxx, top 5b
            result.push_back(0x80 | (cp & 0x3F));   // 10xxxxxx, bottom 6b
        } else if (cp <= 0xFFFF) {  // 3B case
            result.push_back(0xE0 | (cp >> 12));            // 1110xxxx, top 4b
            result.push_back(0x80 | ((cp >> 6) & 0x3F));    // 10xxxxxx, next 6b
            result.push_back(0x80 | (cp & 0x3F));
        } else {                    // 4B case
            result.push_back(0xF0 | (cp >> 18));            // 11110xxx, top 3b
            result.push_back(0x80 | ((cp >> 12) & 0x3F));   // 10xxxxxx, next 6b
            result.push_back(0x80 | ((cp >> 6) & 0x3F));
            result.push_back(0x80 | (cp & 0x3F));
        }
        return result;
    }

    vector<NumInfo> extractTextualNumbers(const vector<uint8_t>& data) {
        // Converts and extracts ASCII numbers given a vector of bytes

        vector<NumInfo> result;
        size_t i = 0;
        while (i < data.size()) {
            if (isdigit(data[i])) {
                size_t start = i;
                while (i < data.size() && isdigit(data[i])) ++i;   // find length of number

                std::string numStr(data.begin() + start, data.begin() + i);
                try {
                    unsigned long long val = std::stoull(numStr);
                    if (val <= std::numeric_limits<unsigned int>::max()) {
                        result.push_back({static_cast<unsigned int>(val), start, i - start});
                    }
                    // else: too large for ui, skip
                } 
                catch(const std::invalid_argument& e) {
                    // invalid number, skip
                }   
                catch(const std::out_of_range& e) {
                    // too large for ull, skip
                }
            }
            else ++i;
        }

        return result;
    }

    vector<unsigned int> generateInterestingNumbers() {
        vector<unsigned int> result;
        vector<unsigned int> shifts = {1, 7, 8, 15, 16, 31};    // truncating from original rust, as unsigned ints are only 32b

        for (unsigned int s : shifts) {
            unsigned int val = 1ULL << s;
            result.push_back(val);
            result.push_back(val - 1);
            result.push_back(val + 1);
        }

        return result;
    }

    template<typename T>
    pair<vector<vector<T>>, vector<vector<T>>> getAlternateSuffixes(
        const vector<T>& theList, 
        VmfRand* rand
    ) {
        // getSuffixes, but randomize which output list gets each suffix
        // NOTE: Very likely to return an empty pair for small buffer sizes

        vector<vector<T>> listA, listB;
        vector<T> subListA, subListB;
        for (size_t i = 0; i < theList.size(); ++i) {
            if (rand->randBetween(0, 1) == 0) {
                subListA.assign(theList.begin() + i, theList.end());
                if(!subListB.empty()) {
                    listB.push_back(move(subListB));
                    subListB.clear();
                }
            } else {
                subListB.assign(theList.begin() + i, theList.end());
                if(!subListA.empty()) {
                    listA.push_back(move(subListA));
                    subListA.clear();
                }
            }
        }
        return {listA, listB};
    }

    template<typename T>
    vector<vector<T>> getSuffixes(const vector<T>& theList) {
        // Grabs all possible slices that end at theList's end

        vector<vector<T>> result;
        for(size_t i = 0; i < theList.size(); ++i) {
            result.push_back(vector<T>(theList.begin() + i, theList.end()));
        }
        return result;
    }

    template<typename T>
    pair<vector<vector<T>>, vector<vector<T>>> getInitialSuffixes(
        const vector<T>& a, 
        const vector<T>& b, 
        VmfRand* rand
    ) {
        if (a == b) return getAlternateSuffixes(a, rand);
        return {getSuffixes(a), getSuffixes(b)};
    }

    template<typename T>
    optional<pair<vector<T>, vector<T>>> getAnyPositionPair(
        vector<vector<T>>& a, 
        vector<vector<T>>& b, 
        VmfRand* rand
    ) {
        if (a.empty() || b.empty()) return nullopt;

        size_t aIndex = rand->randBetween(0, a.size() - 1); // -1 because randBetween is max inclusive
        size_t bIndex = rand->randBetween(0, b.size() - 1);
        vector<T> aElem = a[aIndex];
        vector<T> bElem = b[bIndex];
        return pair<vector<T>, vector<T>>(aElem, bElem);
    }

    template<typename T>
    pair<vector<vector<T>>, vector<vector<T>>> splitPrefixes(
        vector<vector<T>>& prefixes, 
        vector<vector<T>>& suffixes
    ) {
        set<T> used;
        set<vector<T>> hashSuffix;
        vector<vector<T>> newPrefixes;
        for (vector<T> prefix : prefixes) {
            if(!prefix.empty() && used.find(prefix[0]) == used.end()) { // if first char of this prefix hasn't been seen yet...
                used.insert(prefix[0]);
                newPrefixes.push_back(prefix);
                suffixes.erase( // erase-remove idiom. moves all suffixes shorter than prefix to hashSuffix
                    std::remove_if( // shifts matching elements to the end
                        suffixes.begin(), 
                        suffixes.end(), 
                        [&](const vector<T>& suffix) {
                            if (suffix.size() < prefix.size()) {
                                hashSuffix.insert(suffix);  // stores them in hashSuffix prior to removal from suffixes
                                return true;
                            }
                            return false;
                        }
                    ),
                    suffixes.end()  // marks matching elements for erasure
                );
            }
        }
        return {
            newPrefixes, 
            vector<vector<T>>(hashSuffix.begin(), hashSuffix.end()) // convert set of slices to vector of slices
        };
    }

    template<typename T>
    pair<vector<T>, vector<T>> findJumpPoints(
        const vector<T>& a, 
        const vector<T>& b, 
        VmfRand* rand
    ) {
        // NOTE: Very likely to return a and b unmodified for small buffer sizes if a==b

        int fuel = 100000;
        const int searchStopIp = 8;

        auto [listA, listB] = getInitialSuffixes(a, b, rand);
        if (listA.empty() || listB.empty()) return {a, b};

        while (true) {
            if (fuel < 0 || rand->randBetween(0, searchStopIp) == 0) {
                if (auto result = getAnyPositionPair(listA, listB, rand)) return *result;
                return {a, b};
            } else {
                auto [nodeA, nodeB] = splitPrefixes(listA, listB);
                if (nodeA.empty() || nodeB.empty()) {
                    if (auto result = getAnyPositionPair(listA, listB, rand)) return *result;
                    return {a, b};
                } else {
                    listA = nodeA;
                    listB = nodeB;
                    fuel -= static_cast<int>(listA.size() + listB.size());
                }
            }
        }
    }

    template<typename T>
    vector<T> fuse(const vector<T>& a, const vector<T>& b, VmfRand* rand) {
        // Combines a prefix substring from "a" and a suffix substring from "b"
        // NOTE: Very likely to return input unmodified for small buffer sizes if a==b

        if (a.empty() || b.empty()) return a;

        auto [from, to] = findJumpPoints(a, b, rand);
        
        if (std::equal(from.begin(), from.end(), a.end() - from.size())) {
            vector<T> result(a.begin(), a.end() - from.size()); // keep prefix
            result.insert(result.end(), to.begin(), to.end());  // append suffix
            return result;
        }
        return a;
    }
};
}
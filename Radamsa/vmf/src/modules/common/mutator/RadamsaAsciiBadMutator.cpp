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
 /**
  *
  */
#include "RadamsaAsciiBadMutator.hpp"
#include "RuntimeException.hpp"
#include <random>
#include <algorithm>
#include <variant>

using namespace vmf;
using Byte = uint8_t;
using std::get;
using std::get_if;
using std::holds_alternative;
using std::string;
using std::variant;


#include "ModuleFactory.hpp"
REGISTER_MODULE(RadamsaAsciiBadMutator);

/**
 * @brief Builder method to support the ModuleFactory
 * Constructs an instance of this class
 * @return Module* - Pointer to the newly created instance
 */
Module* RadamsaAsciiBadMutator::build(std::string name)
{
    return new RadamsaAsciiBadMutator(name);
}

/**
 * @brief Initialization method
 *
 * @param config - Configuration object
 */
void RadamsaAsciiBadMutator::init(ConfigInterface& config)
{

}

/**
 * @brief Construct a new RadamsaAsciiBadMutator::RadamsaAsciiBadMutator object
 *
 * @param name The of the name module
 */
RadamsaAsciiBadMutator::RadamsaAsciiBadMutator(std::string name) : MutatorModule(name)
{
    // rand->randInit();
}

/**
 * @brief Destroy the RadamsaAsciiBadMutator::RadamsaAsciiBadMutator object
 *
 */
RadamsaAsciiBadMutator::~RadamsaAsciiBadMutator()
{

}

/**
 * @brief Register the storage needs for this module
 *
 * @param registry - StorageRegistry object
 */
void RadamsaAsciiBadMutator::registerStorageNeeds(StorageRegistry& registry)
{
    // This module does not register for a test case buffer key, because mutators are told which buffer to write in storage
    // by the input generator that calls them
}

// Helper stuff starts here
struct Delimited {
    // Chunk of Data, usually with delimiting quotes enclosing it

    Byte delim;
    vector<Byte> data;

    static Delimited make(char c, const vector<Byte>& d) {
        return Delimited{Byte(c), d};
    }

    void unlex(vector<Byte>& out) const {
        out.push_back(delim);
        out.insert(out.end(), data.begin(), data.end());
        out.push_back(delim);

        return;
    }
};

struct Text {
    // Raw text / delimited chunk
public: 
    variant<vector<Byte>, Delimited> value;

    static Text texty(const vector<Byte>& s) {
        return Text{s};
    }
    static Text delim(const Delimited& d) {
        return Text{d};
    }

    void mutate(VmfRand* rand) {
        vector<Byte>* targetData;
        if (vector<Byte>* p = get_if<vector<Byte>>(&value)) {
            targetData = p;
        } else {
            targetData = &get<Delimited>(value).data;
        }
        mutateTextData(*targetData, rand);

        return;
    }

    void unlex(vector<Byte>& out) const {
        if (holds_alternative<vector<Byte>>(value)) {
            const vector<Byte>& a = get<vector<Byte>>(value);
            out.insert(out.end(), a.begin(), a.end());
        } else {
            const Delimited& delimChunk = get<Delimited>(value);
            delimChunk.unlex(out);
        }

        return;
    }
private:
    explicit Text(const vector<Byte>& s) : value(s) {}
    explicit Text(const Delimited& d) : value(d) {}

    static const vector<vector<Byte>> getSillyStrings() {
        // XXX: extend this because many of these strings are incredibly Linux-specific
        // perhaps add a configurable wordlist
        static const vector<string> strList = {
            "%n", "%n", "%s", "%d", "%p", "%#x",
            "\\00", "aaaa%d%n",
            "`xcalc`", ";xcalc", "$(xcalc)", "!xcalc", "\"xcalc", "'xcalc",
            "\\x00", "\\r\\n", "\\r", "\\n", "\\x0a", "\\x0d",
            "NaN", "+inf",
            "$PATH",
            "$!!", "!!", "&#000;", "\\u0000",
            "$&", "$+", "$`", "$'", "$1"
        };
        static vector<vector<Byte>> list;
        if (list.empty()) {
            list.reserve(strList.size());
            for (const string& s : strList) {
                list.emplace_back(s.begin(), s.end());
            }
        }
        return list;
    };

    vector<Byte> randomBadness(VmfRand* rand) {
        // Randomly concatenate 1-19 "silly strings"

        const vector<vector<Byte>> sillyStrings = getSillyStrings();
        int repeatCount = rand->randBetween(1, 19);

        vector<Byte> out;
        out.reserve(repeatCount * 8);
        for (int i = 0; i < repeatCount; ++i) {
            const vector<Byte>& s = sillyStrings[rand->randBetween(0, sillyStrings.size() - 1)];
            out.insert(out.end(), s.begin(), s.end());
        }
        return out;
    }

    void mutateTextData(vector<Byte>& data, VmfRand* rand) {
        size_t byteIndex = rand->randBetween(0, data.size());
        int mutationType = rand->randBetween(0, 2);
        switch (mutationType) {
            case 0: {
                // insert badness
                vector<Byte> bad = randomBadness(rand);
                data.insert(data.begin() + byteIndex, bad.begin(), bad.end());
                break;
            }
            case 1: {
                // replace badness
                vector<Byte> bad = randomBadness(rand);
                data.resize(byteIndex);
                data.insert(data.end(), bad.begin(), bad.end());
                break;
            }
            case 2: {
                // push random number of newline characters
                int choice = rand->randBetween(0, 10);
                size_t newlineCount;
                switch (choice) {
                    case 0: newlineCount = 127;   break;
                    case 1: newlineCount = 128;   break;
                    case 2: newlineCount = 255;   break;
                    case 3: newlineCount = 256;   break;
                    case 4: newlineCount = 16383; break;
                    case 5: newlineCount = 16384; break;
                    case 6: newlineCount = 32767; break;
                    case 7: newlineCount = 32768; break;
                    case 8: newlineCount = 65535; break;
                    case 9: newlineCount = 65536; break;
                    default: newlineCount = rand->randBetween(0, 1023); break;
                }
                data.insert(data.begin() + byteIndex, newlineCount, Byte('\n'));
                break;
            }
        }

        return;
    }
};

struct Data {
    // Chunk data in two flavors: bytes, and texty
    variant<vector<Byte>, vector<Text>> value;

    void unlex(vector<Byte>& out) const {
        if (holds_alternative<vector<Byte>>(value)) {
            const vector<Byte>& a = get<vector<Byte>>(value);
            out.insert(out.end(), a.begin(), a.end());
        } else {
            const vector<Text>& texts = get<vector<Text>>(value);
            for (const Text& t : texts) {
                t.unlex(out);
            }
        }
    }
};

struct Ascii {
public:
    vector<Data> chunks;

    static optional<Ascii> parse(const vector<Byte>& data) {
        vector<Data> out;
        bool success = parseBytes(data, 6, out);
        if (!success) return nullopt;
        return Ascii{out};
    }

    void mutate(VmfRand* rand) {
        vector<size_t> textChunkIndices;
        for (size_t i = 0; i < chunks.size(); ++i) {
            if (holds_alternative<vector<Text>>(chunks[i].value))
                textChunkIndices.push_back(i);
        }
        if(textChunkIndices.empty()) return;

        const size_t chunkIndex = rand->randBetween(0, textChunkIndices.size() - 1);
        vector<Text>& textElems = get<vector<Text>>(
            chunks[textChunkIndices[chunkIndex]].value
        );
        const size_t elemIndex = rand->randBetween(0, textElems.size() - 1);    
        textElems[elemIndex].mutate(rand);

        return;
    }

    vector<Byte> unlex() const {
        vector<Byte> out;
        out.reserve(chunks.size() * 16);
        for (const Data& d : chunks) {
            d.unlex(out);
        }
        return out;
    }

private:
    static bool isTexty(Byte b) noexcept {
        return b == 9 || b == 10 || b == 13 || (b >= 32 && b <= 126);
    }
    
    static bool parseBytes(
        const vector<Byte>& input, 
        size_t minTexty, 
        vector<Data>& out
    ) {
        // Splits input into Data chunks
        // The first chunk must be a run of a least "minTexty" printable ASCII bytes

        size_t pos = 0;
        size_t start = pos;
        // min size check
        while (pos < input.size() && Ascii::isTexty(input[pos])) {
            ++pos;
        }
        if ((pos - start) < minTexty) return false;

        // Grab first text chunk
        vector<Byte> slice(input.begin(), input.begin() + pos);
        vector<Text> firstRun;
        firstRun.push_back(Text::texty(slice));
        out.insert(out.begin(), Data{firstRun});

        // Process remainder
        start = pos;
        while (pos < input.size()) {
            if (Ascii::isTexty(input[pos])) {
                ++pos;
            } else {
                // if we just finished a texty run [start, pos), capture it
                if (pos > start) {
                    vector<Byte> nextSlice(input.begin() + start, input.begin() + pos);
                    vector<Text> t;
                    t.push_back(Text::texty(nextSlice));
                    out.push_back(Data{t});
                }
                // treat the current non-text byte as its own Data chunk
                out.push_back(Data{vector<Byte>{input[pos]}});
                ++pos;
                start = pos; // reset start for next run
            }
        }

        // if input ends in the middle of a texty run [start, input.size()), capture the run
        if (pos > start) {
            vector<Byte> finalSlice(input.begin() + start, input.begin() + pos);
            vector<Text> finalTexty;
            finalTexty.push_back(Text::texty(finalSlice));
            out.push_back(Data{finalTexty});
        }

        return true;
    }
};

void RadamsaAsciiBadMutator::mutateTestCase(StorageModule& storage, StorageEntry* baseEntry, StorageEntry* newEntry, int testCaseKey)
{
    /* Mutate a single "chunk" of continuous printable ASCII by:
     * inserting a random combination of 1-19 "silly strings" at a random index,
     * replacing everything after a random index with a random combination of 1-19 "silly strings",
     * or appending between 0 and 65,536 newlines
     */

    const size_t minimumSize{1u};
    const size_t minimumSeedIndex{0u};
    const size_t originalSize = baseEntry->getBufferSize(testCaseKey);
    char* originalBuffer = baseEntry->getBufferPointer(testCaseKey);

    if (originalSize < minimumSize) {
        throw RuntimeException{"The buffer's minimum size must be greater than or equal to 1", RuntimeException::USAGE_ERROR};
    }
    if (minimumSeedIndex > originalSize - 1u) {
        throw RuntimeException{"Minimum seed index is out of bounds", RuntimeException::INDEX_OUT_OF_RANGE};
    }
    if (originalBuffer == nullptr) {
        throw RuntimeException{"Input buffer is null", RuntimeException::UNEXPECTED_ERROR};
    }

    vector<uint8_t> data(originalBuffer, originalBuffer + originalSize);

    optional<Ascii> parsedAscii = Ascii::parse(data);
    if (!parsedAscii) {
        throw RuntimeException{"Unable to parse ASCII from buffer", RuntimeException::USAGE_ERROR};
    }

    parsedAscii->mutate(this->rand);
    vector<Byte> mutatedBytes = parsedAscii->unlex();

    const size_t newBufferSize{mutatedBytes.size() + 1}; // +1 to implicitly append a null terminator
    char* newBuffer{newEntry->allocateBuffer(testCaseKey, newBufferSize)};
    memset(newBuffer, 0u, newBufferSize);
    memcpy(newBuffer, mutatedBytes.data(), mutatedBytes.size());
}
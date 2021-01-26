// Copyright (c) 2018-2021Vincenzo Palazzo vincenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt
#ifndef PARSINGBLOCKCHAIN_BLOCKHEADER_H
#define PARSINGBLOCKCHAIN_BLOCKHEADER_H

#include <glog/logging.h>
#include <rapidjson/writer.h>
#include <rapidjson/ostreamwrapper.h>
#include "../../util/uint256.h"
#include "../../util/serialize.h"

namespace spyCBlock {
    class BlockHeader {
    private:

        int32_t version;

        uint256 previousBlockHeaderHash;

        uint256 merkleRoot;

        int32_t time;

        uint32_t nBits;

        uint32_t nonce;

        std::string convertTimeStamp();

    public:

        int32_t getVersion() const;

        uint32_t getTime() const;

        uint32_t getNBits() const;

        uint32_t getNonce() const;

        const uint256 &getPreviousBlockHeaderHash() const;

        const uint256 &getMerkleRoot() const;

        bool operator==(const BlockHeader &rhs) const;

        bool operator!=(const BlockHeader &rhs) const;

        std::string toString();

        void decode(std::ifstream &stream);

        std::string toSerealizationForm();

        void toJson(rapidjson::Writer<rapidjson::OStreamWrapper> &writerJson);

    };
}

#endif //PARSINGBLOCKCHAIN_BLOCKHEADER_H

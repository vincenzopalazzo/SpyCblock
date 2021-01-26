// Copyright (c) 2018-2021Vincenzo Palazzo vincenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt
#ifndef PARSINGBLOCKCHAIN_BLOCK_H
#define PARSINGBLOCKCHAIN_BLOCK_H

#include <ostream>
#include <glog/logging.h>
#include <zlib.h>
#include "../../../include/spycblockrpc/src/core/graph/WrapperInformations.h"

#include "BlockHeader.h"
#include "../transaction/RawTransaction.h"
#include "../../persistence/SerializationUtil.h"

namespace spyCBlock {
    class Block {
    public:

        enum Type {
            NETWORK_MAIN = 3652501241, //0xD9B4BEF9
            NETWORK_TESTNET = 3669344250, //0xDAB5BFFA
            NETWORK_TESTNET3 = 118034699, //0x0709110B
            NETWORK_NAMECOIN = 4273258233 //0xFEB4BEF9
        };

        int32_t getMagicNum() const;

        int32_t getBlocksize() const;

        const BlockHeader &getBlockHeader() const;

        const DVarInt &getNumberRawTransaction() const;

        const vector<RawTransaction> &getRawTransactions() const;

        void setHeightBlock(int32_t heightBlock);

        std::string getHashBlock() const;

        bool operator==(const Block &rhs) const;

        bool operator!=(const Block &rhs) const;

        void decode(std::ifstream &stream);

        std::string toSerealizationForm();

        void toJson(rapidjson::Writer<rapidjson::OStreamWrapper> &writerJson);

        void toGraphForm(std::ofstream &outputStream, spyCBlockRPC::WrapperInformations &wrapper);

        void toTransactionsGraph(std::ofstream &outputStream, spyCBlockRPC::WrapperInformations &wrapper);

        void toCompressedTransactionsGraph(gzFile &file, spyCBlockRPC::WrapperInformations &wrapper);

        std::string toString();

    private:

        int32_t magicNum;

        int32_t blocksize;

        BlockHeader blockHeader;

        DVarInt numberRawTransaction;

        vector<RawTransaction> rawTransactions;

        string hashBlock;

        string convertMagicNumber();
    };
}

#endif //PARSINGBLOCKCHAIN_BLOCK_H

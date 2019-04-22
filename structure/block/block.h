#ifndef PARSINGBLOCKCHAIN_BLOCK_H
#define PARSINGBLOCKCHAIN_BLOCK_H

#include <ostream>
#include <glog/logging.h>

#include "blockHeader.h"
#include "../transaction/RawTransaction.h"
#include "../../persistence/SerializationUtil.h"

using namespace std;

/**
 * @author https://github.com/vincenzopalazzo
 */

namespace spyCBlock {

    enum typeBlock{
        NETWORK_MAIN = 3652501241, //0xD9B4BEF9
        NETWORK_TESTNET = 3669344250, //0xDAB5BFFA
        NETWORK_TESTNET3 = 118034699, //0x0709110B
        NETWORK_NAMECOIN = 4273258233 //0xFEB4BEF9
    };

    class Block {
    private:

        int32_t magicNum;
        int32_t blocksize;
        BlockHeader blockHeader;
        DVarInt numbarRawTransaction;
        vector<unique_ptr<RawTransaction>> rawTransactions;

        //Surplus information to the block
        //The value -1 indicate a value null because the value is setter to passer
        int32_t heightBlock = -1;
        string hashBlock;

        string convertMagicNumbar();

    public:

        virtual ~Block();

        int32_t getMagicNum() const;

        int32_t getBlocksize() const;

        const BlockHeader &getBlockHeader() const;

        const DVarInt &getNumbarRawTransaction() const;

        const vector<unique_ptr<RawTransaction>> &getRawTransactions() const;

        int32_t getHeightBlock() const;

        void setHeightBlock(int32_t heightBlock);

        string getHashBlock() const;

        bool operator==(const Block &rhs) const;

        bool operator!=(const Block &rhs) const;

        string toString();

        void decode(std::ifstream &stream);

        string toSerealizationForm();

        json toJsonLite();

        json toJsonFat();
    };
}

#endif //PARSINGBLOCKCHAIN_BLOCK_H

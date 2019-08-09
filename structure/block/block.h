#ifndef PARSINGBLOCKCHAIN_BLOCK_H
#define PARSINGBLOCKCHAIN_BLOCK_H

#include <ostream>
#include <glog/logging.h>

#include "../../include/spycblockrpc/core/graph/WrapperInformations.h"

#include "blockHeader.h"
#include "../transaction/RawTransaction.h"
#include "../../persistence/SerializationUtil.h"

/**
 * Created on 1/21/19.
 * @author https://github.com/vincenzopalazzo
 */
namespace spyCBlock {

    //TODO moved this enum inside the class and use the enum class
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

          vector<RawTransaction> rawTransactions;

          int32_t heightBlock = -1;

          string hashBlock;

          string convertMagicNumbar();

      public:

          int32_t getMagicNum() const;

          int32_t getBlocksize() const;

          const BlockHeader &getBlockHeader() const;

          const DVarInt &getNumbarRawTransaction() const;

          const vector<RawTransaction> &getRawTransactions() const;

          int32_t getHeightBlock() const;

          void setHeightBlock(int32_t heightBlock);

          std::string getHashBlock() const;

          bool operator==(const Block &rhs) const;

          bool operator!=(const Block &rhs) const;

          std::string toString();

          void decode(std::ifstream &stream);

          std::string toSerealizationForm();

          //can be remove
          nlohmann::json toJsonLite();

          nlohmann::json toJsonFat();

          void toJson(rapidjson::Writer<rapidjson::OStreamWrapper> &writerJson);

          void toGraphForm(std::ofstream &outputStream, spyCBlockRPC::WrapperInformations &wrapper);
    };
}

#endif //PARSINGBLOCKCHAIN_BLOCK_H

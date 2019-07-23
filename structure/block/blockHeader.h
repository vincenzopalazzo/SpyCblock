#ifndef PARSINGBLOCKCHAIN_BLOCKHEADER_H
#define PARSINGBLOCKCHAIN_BLOCKHEADER_H

#include <nlohmann/json.hpp>
#include <glog/logging.h>
#include <rapidjson/writer.h>
#include <rapidjson/ostreamwrapper.h>
#include "../../util/uint256.h"
#include "../../util/serialize.h"

/**
 * Created on 1/21/19.
 * @author https://github.com/vincenzopalazzo
 */
namespace spyCBlock
{
  class BlockHeader
  {
    private:

        int32_t version;
        uint256 previousBlockHeaderHash;
        uint256 merkleRoot;
        int32_t time;
        uint32_t nBits; // this whats corrisponde
        uint32_t nonce;

        std::string convertTimeStamp();

    public:

        BlockHeader();

        BlockHeader(int32_t version, uint256 previousBlockHeaderHash, uint256 merkleRoot, uint32_t time, uint32_t nBits, uint32_t nonce);

        int32_t getVersion() const ;

        uint32_t getTime() const;

        uint32_t getNBits() const;

        uint32_t getNonce() const;

        const uint256& getPreviousBlockHeaderHash() const;

        const uint256& getMerkleRoot() const;

        bool operator==(const BlockHeader &rhs) const;

        bool operator!=(const BlockHeader &rhs) const;

        std::string toString();

        void unserialize(std::ifstream &stream);

        std::string toSerealizationForm();

        nlohmann::json toJoson();

        void toJson(rapidjson::Writer<rapidjson::OStreamWrapper> &writerJson);

  };
}

#endif //PARSINGBLOCKCHAIN_BLOCKHEADER_H

#ifndef PARSINGBLOCKCHAIN_TXINNOCOINDBASE_H
#define PARSINGBLOCKCHAIN_TXINNOCOINDBASE_H

#include <cstdint>

#include <nlohmann/json.hpp>
#include <rapidjson/writer.h>
#include <rapidjson/ostreamwrapper.h>
#include "../type/Outpoint.h"
#include "../../include/spycblockrpc/core/graph/WrapperInformations.h"

#include "../type/DScript.h"

/**
 * Created on 1/21/19.
 * @author https://github.com/vincenzopalazzo
 */
namespace spyCBlock{
    //In the coindbase transaction, outpoint is standard, the hash id resiver si 0 and
    //the n is 2^32 - 1
    class TransactionInput
    {
    private:

        OutPoint outpoint;
        DScript script;
        uint32_t sequences;

        //Additional finformation
        std::string hashInputTransaction;

    public:

        const DScript& getScript() const;

        uint32_t getSequences() const;

        const OutPoint& getOutpoint() const;

        void setOutpoint(const OutPoint &outpoint);

        const std::string& getHashInputTransaction() const;

        std::string decodeIntoStringScriptSing() const; //TODO I added & because I like referiment but it is correct?

        std::string toString();

        void decode(std::ifstream &stream);

        std::string toSerealizationForm();

        bool isScriptNull();

        //TODO can be removed
        nlohmann::json toJson();

        void toJson(rapidjson::Writer<rapidjson::OStreamWrapper> &writerJson);

        void toGraphForm(std::ofstream &outputStream, spyCBlockRPC::WrapperInformations &wrapper);
    };
}

#endif //PARSINGBLOCKCHAIN_TXINNOCOINDBASE_H

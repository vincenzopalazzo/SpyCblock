//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//
#ifndef PARSINGBLOCKCHAIN_TXINNOCOINDBASE_H
#define PARSINGBLOCKCHAIN_TXINNOCOINDBASE_H

#include <nlohmann/json.hpp>
#include <cstdint>

#include "../type/Outpoint.h"
#include "../type/DScript.h"
//#include "../../persistence/serializationutil.h"


using namespace std;
using namespace nlohmann;
/*
 * In the coindbase transaction, outpoint is standard, the hash id resiver si 0 and
 * the n is 2^32 - 1*/

namespace spyCBlock{

    class TransactionInput
    {
    private:
        OutPoint outpoint;
        DScript script;
        uint32_t sequences;

    public:
        const DScript &getScript() const;

        uint32_t getSequences() const;

        const OutPoint &getOutpoint() const;

        void setOutpoint(const OutPoint &outpoint);

        string decodeIntoStringScriptSing();

        string toString();

        void decode(std::ifstream &stream);

        string toSerealizationForm();

        json toJson();
    };
}

#endif //PARSINGBLOCKCHAIN_TXINNOCOINDBASE_H

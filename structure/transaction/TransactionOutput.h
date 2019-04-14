//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//


#ifndef PARSINGBLOCKCHAIN_TRANSACTIONOUTPUT_H
#define PARSINGBLOCKCHAIN_TRANSACTIONOUTPUT_H

#include <cstdint>
#include <nlohmann/json.hpp>

#include "../type/DScript.h"
//#include "../../persistence/serializationutil.h"

using namespace std;
using namespace nlohmann;

namespace spyCBlock{

    class TransactionOutput{

    private:

        int64_t nValue;
        DScript script;

        //Addintiona information
        string hashOutputTransaction;

    public:
        const int64_t& getNValue() const;

        const DScript& getScript() const;

        const string& getHashOutputTransaction() const;

        string toString();

        void decode(ifstream &stream);

        string toSerealizationForm();

        json toJson();
    };
}
#endif //PARSINGBLOCKCHAIN_TRANSACTIONOUTPUT_H



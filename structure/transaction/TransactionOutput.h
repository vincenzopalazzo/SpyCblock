//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//


#ifndef PARSINGBLOCKCHAIN_TRANSACTIONOUTPUT_H
#define PARSINGBLOCKCHAIN_TRANSACTIONOUTPUT_H

#include <cstdint>
#include "../type/DScript.h"
//#include "../../persistence/serializationutil.h"

using namespace std;

namespace spyCBlock{

    class TransactionOutput{

    private:
        int64_t nValue;
        DScript script;

    public:
        int64_t getNValue() const;

        const DScript &getScript() const;

        string toString();

        void decode(ifstream &stream);

        string toSerealizationForm();

    };
}
#endif //PARSINGBLOCKCHAIN_TRANSACTIONOUTPUT_H



//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//


#ifndef PARSINGBLOCKCHAIN_TRANSACTIONOUTPUT_H
#define PARSINGBLOCKCHAIN_TRANSACTIONOUTPUT_H

#include <cstdint>
#include "../../type/DScript.h"

using namespace std;

class TransactionOutput{

private:
    int64_t nValue;
    DScript script;

public:
    int64_t getNValue() const;

    const DScript &getScript() const;

    string toString();

    void decode(ifstream &stream);

};
#endif //PARSINGBLOCKCHAIN_TRANSACTIONOUTPUT_H



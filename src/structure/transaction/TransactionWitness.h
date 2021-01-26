// Copyright (c) 2018-2021Vincenzo Palazzo vincenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef TRANSACTIONWITNESS_H
#define TRANSACTIONWITNESS_H

#include <vector>

#include "../type/DVarInt.h"
#include "../type/DScript.h"

namespace spyCBlock {
    class TransactionWitness {
    public:

        DVarInt getCompactSize() const;

        std::vector<DScript> getWitnessStack() const;

        void decode(std::ifstream &stream);

        std::string toSerealizationForm() const;

        std::string toString();

    private:

        DVarInt compactSize;

        std::vector<DScript> witnessStack;

    };

}

#endif // TRANSACTIONWITNESS_H

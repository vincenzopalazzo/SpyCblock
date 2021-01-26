// Copyright (c) 2018-2021Vincenzo Palazzo vincenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef TRANSACTIONSRAWGRAPH_H
#define TRANSACTIONSRAWGRAPH_H

#include <string>
#include <set>
#include <zlib.h>

#include "../../../../include/spycblockrpc/src/core/graph/ITransactionGraph.h"

namespace spyCBlock {
    class TransactionsRawGraph : spyCBlockRPC::ITransactionGraph {
    public:

        void serialize(std::ofstream &stream) override;

        void buildTransaction(spyCBlockRPC::WrapperInformations &wrapper) override;

        //TODO this could containt inside the interface?
        //I think yes
        void serialize(gzFile &file);

    private:

        std::string from;

        std::string to;

        std::set<std::string> linkInformations;

        std::string delimitator;
    };
}

#endif // TRANSACTIONSRAWGRAPH_H

#ifndef TRANSACTIONSRAWGRAPH_H
#define TRANSACTIONSRAWGRAPH_H

#include <string>
#include <vector>

#include "../../../../include/spycblockrpc/core/graph/ITransactionGraph.h"

namespace  spyCBlock
{
    class TransactionsRawGraph : spyCBlockRPC::ITransactionGraph
    {
        public:
            void serialize(std::ofstream &stream) override;

            void buildTransaction(spyCBlockRPC::WrapperInformations &wrapper) override;

        private:

            std::string from;

            std::string to;

            std::vector<std::string> linkInformations;

            std::string delimitator;
    };
}

#endif // TRANSACTIONSRAWGRAPH_H

// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef DAOTRANSACTIONSGRAPH_H
#define DAOTRANSACTIONSGRAPH_H


#include "../../IDAOBlockchain.h"

namespace spyCBlock {

    class DAOTransactionsGraph : IDAOBlockchain
    {
        public:

            bool saveBlock(const std::string &inputPath, const std::string &outputPath) override;

            bool saveBlockCompress(const string &inputPath, const string &outputPath) override;
    };

}

#endif // DAOTRANSACTIONSGRAPH_H

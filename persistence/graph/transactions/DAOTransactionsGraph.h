#ifndef DAOTRANSACTIONSGRAPH_H
#define DAOTRANSACTIONSGRAPH_H


#include "../../IDAOBlockchain.h"

namespace spyCBlock {

    class DAOTransactionsGraph : IDAOBlockchain
    {
        public:
            bool saveBlock(string inputPath, string outputPath, int &height) override;
    };

}

#endif // DAOTRANSACTIONSGRAPH_H

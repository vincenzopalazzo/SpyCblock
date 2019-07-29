#ifndef TRANSACTIONWITNESS_H
#define TRANSACTIONWITNESS_H

#include <vector>

#include "../type/DVarInt.h"
#include "../type/DScript.h"

namespace spyCBlock
{

    class TransactionWitness
    {
        public:

          DVarInt getCompactSize() const;

          std::vector<DScript> getWitnessStack() const;

          void decode(std::ifstream &stream);

        private:

          DVarInt compactSize;

          std::vector<DScript> witnessStack;

    };

}

#endif // TRANSACTIONWITNESS_H

#ifndef UTILCRYPTO_H
#define UTILCRYPTO_H

#include <string>
#include <vector>
#include <memory>

using namespace std;

namespace spyCBlock {

    class UtilCrypto
    {
     public:
        static vector<unsigned char> ToHexIntoVectorByte(string &hexData);
    };

}
#endif // UTILCRYPTO_H

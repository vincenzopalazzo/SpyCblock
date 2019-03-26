#ifndef UTILCRYPTO_H
#define UTILCRYPTO_H

#include <string>
#include <vector>

using namespace std;

namespace spyCBlock {

    class UtilCrypto
    {
     public:
        static char* ToHexIntoByte(string &hexData);

        static vector<unsigned char> ToHexIntoVectorByte(string &hexData);

    private:
        static char* ToVectorByteIntoArray(vector<char*> *vectorByte);
    };

}
#endif // UTILCRYPTO_H

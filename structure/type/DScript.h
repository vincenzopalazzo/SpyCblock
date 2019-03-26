//
// Created by https://github.com/vincenzopalazzo on 2/4/19.
//

#ifndef PARSINGBLOCKCHAIN_CSCRIPT_H
#define PARSINGBLOCKCHAIN_CSCRIPT_H


#include <vector>
#include <fstream>
#include "DVarInt.h"

using namespace std;

namespace spyCBlock{

    class DScript{
//TODO refactoring
    private:
        DVarInt scriptLenght;
        string scriptString;
        string rawScriptString;
    public:
        const string &getScriptString() const;


    public:

        virtual ~DScript();

        const char* getScriptRaw() const;

        const string &getRawScriptString() const;

        const DVarInt &getScriptLenght() const;

        string toString();

        void decode(std::ifstream &stream);
    };
}


#endif //PARSINGBLOCKCHAIN_CSCRIPT_H

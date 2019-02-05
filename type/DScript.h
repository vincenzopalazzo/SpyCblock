//
// Created by https://github.com/vincenzopalazzo on 2/4/19.
//

#ifndef PARSINGBLOCKCHAIN_CSCRIPT_H
#define PARSINGBLOCKCHAIN_CSCRIPT_H


#include <vector>
#include <bits/stl_bvector.h>
#include <fstream>
#include "DVarInt.cpp"

class DScript{

private:
    DVarInt scriptLenght;
    std::vector<unsigned char> script;

public:

    const std::vector<unsigned char> &getScript() const;

    const DVarInt &getScriptLenght() const;

    void decode(std::ifstream &stream);
};

#endif //PARSINGBLOCKCHAIN_CSCRIPT_H

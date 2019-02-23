//
// Created by https://github.com/vincenzopalazzo on 2/4/19.
//

#include <sstream>
#include "DScript.h"
#include "../util/serialize.h"

const std::vector<unsigned char> &DScript::getScript() const {
    return script;
}

void DScript::decode(std::ifstream &stream) {
    this->scriptLenght.decode(stream);
    for(int i = 0; i < this->scriptLenght.getValue(); i++){
        char value;
        Unserialize(stream, value);
        script.push_back(value);
    }
}

const DVarInt &DScript::getScriptLenght() const {
    return scriptLenght;
}

string DScript::toString() {
    stringstream *stream = new stringstream();
    *stream << "Length script: " << this->scriptLenght.getValue() << endl;
    *stream << "Script: ";
    for(int i = 0; i < script.size(); i++)
    {
        if(i == script.size() - 1)
        {
            *stream << script.at(i) << endl;
        }else{
            *stream << script.at(i);
        }
    }
    string result = stream->str();
    delete stream;
    return result;
}

DScript::~DScript() {
}

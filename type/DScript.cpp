//
// Created by https://github.com/vincenzopalazzo on 2/4/19.
//

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

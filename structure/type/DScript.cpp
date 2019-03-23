//
// Created by https://github.com/vincenzopalazzo on 2/4/19.
//

#include <sstream>
#include <glog/logging.h>
#include "DScript.h"
#include "../../util/serialize.h"
#include "../../util/strencodings.h"

using namespace spyCBlock;

const std::vector<unsigned char> &DScript::getScript() const {
    return script;
}

void DScript::decode(std::ifstream &stream) {
    this->scriptLenght.decode(stream);
/*    for(int i = 0; i < this->scriptLenght.getValue(); i++){
        char value;
        Unserialize(stream, value);
        script.push_back(value);
    }*/

    //apport change TODO CONTINUE TEST
    char *buffer = new char[scriptLenght.getValue()];
    LOG(INFO) << "Dimension script: " << scriptLenght.getValue();
    stream.read(buffer, scriptLenght.getValue());
    scriptString = string(buffer);
    LOG(INFO) << "The script is: " << scriptString;
}

const DVarInt &DScript::getScriptLenght() const {
    return scriptLenght;
}

string DScript::toString() {
    stringstream *stream = new stringstream();
    *stream << "Length script: " << this->scriptLenght.getValue() << endl;
    *stream << "Script: " << scriptString;
   /* for(int i = 0; i < script.size(); i++)
    {
        if(i == script.size() - 1)
        {
            *stream << script.at(i) << endl;
        }else{
            *stream << script.at(i);
        }
    }*/
    string result = stream->str();
    delete stream;
    return result;
}

DScript::~DScript() {
}

const string &DScript::getScriptString() const {
    return scriptString;
}

//
// Created by https://github.com/vincenzopalazzo on 2/4/19.
//

#include <sstream>
#include <glog/logging.h>
#include "DScript.h"
#include "../../util/serialize.h"
#include "../../util/strencodings.h"

using namespace spyCBlock;

void DScript::decode(std::ifstream &stream) {
    this->scriptLenght.decode(stream);
/*    for(int i = 0; i < this->scriptLenght.getValue(); i++){
        char value;
        Unserialize(stream, value);
        script.push_back(value);
    }*/

    //apport change TODO CONTINUE TEST
    //char *buffer = new char[scriptLenght.getValue()];
    char buffer[scriptLenght.getValue()];
    LOG(INFO) << "Dimension script: " << scriptLenght.getValue();
    stream.read(buffer, static_cast<long>(scriptLenght.getValue())); //TODO look this canged
    //Unserialize(stream, buffer);
    LOG_IF(ERROR, (sizeof (buffer) != scriptLenght.getValue())) << "Dimension script readed wrong";
    scriptString = string(buffer, scriptLenght.getValue());
    //TODO for protocol bitcoin, look a toStrign transaction
    //rawScriptString = HexStr(scriptString).substr(0, 24);
    rawScriptString = HexStr(scriptString);
    LOG(INFO) << "The hex script is: " << rawScriptString;
}

string DScript::toString() {
    stringstream *stream = new stringstream();
    *stream << "Length script: " << this->scriptLenght.getValue() << endl;
    *stream << "Script: " << scriptString;
    string result = stream->str();
    delete stream;
    return result;
}

DScript::~DScript() {
}

const DVarInt &DScript::getScriptLenght() const {
  return scriptLenght;
}

string DScript::getScriptToSerializationForm()
{
  if(rawScriptString.empty())
  {
      LOG(ERROR) << "The raw script is null";
      //TODO create a exception genral for all parser
      throw new exception();
  }
  return rawScriptString.substr(0, (this->scriptLenght.getValue() * 2));
}

const string &DScript::getRawScriptString() const
{
  return rawScriptString;
}

const string &DScript::getScriptString() const {
    return scriptString;
}

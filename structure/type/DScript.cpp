//
// Created by https://github.com/vincenzopalazzo on 2/4/19.
//

#include <sstream>
#include <glog/logging.h>
#include "DScript.h"
#include "../../util/serialize.h"
#include "../../util/strencodings.h"

using namespace spyCBlock;

DScript::~DScript()
{}

const DVarInt &DScript::getScriptLenght() const
{
  return scriptLenght;
}

string DScript::getScriptToSerializationForm()
{
  if(rawScriptString.empty())
  {
      LOG(ERROR) << "The raw script is null";
      //TODO create a exception genral for all parser
      throw  exception();
  }
  return rawScriptString.substr(0, (this->scriptLenght.getValue() * 2));
}

const string &DScript::getRawScriptString() const
{
  return rawScriptString;
}

const string &DScript::getScriptString() const
{
    return scriptString;
}

void DScript::decode(std::ifstream &stream)
{
    this->scriptLenght.decode(stream);

    char buffer[scriptLenght.getValue()];
    LOG(INFO) << "Dimension script: " << scriptLenght.getValue();

    stream.read(buffer, static_cast<long>(scriptLenght.getValue())); //TODO look this canged

    LOG_IF(ERROR, (sizeof (buffer) != scriptLenght.getValue())) << "Dimension script readed wrong";
    scriptString = string(buffer, scriptLenght.getValue());

    rawScriptString = HexStr(scriptString);
    LOG(INFO) << "The hex script is: " << rawScriptString;
}

string DScript::toString()
{
    string stringForm = "Length script: ";
    stringForm += to_string(this->scriptLenght.getValue());
    stringForm += "\n";
    stringForm += "Script: ";
    stringForm += scriptString;

    return stringForm;
}


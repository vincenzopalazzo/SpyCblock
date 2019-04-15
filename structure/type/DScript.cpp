//
// Created by https://github.com/vincenzopalazzo on 2/4/19.
//

#include <sstream>

#include <glog/logging.h>
#include "DScript.h"
#include "../../util/serialize.h"
#include "../../util/strencodings.h"

using namespace spyCBlock;
using namespace std;

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
      LOG(ERROR) << "The raw script is null " +  scriptString;
      //TODO create a exception genral for all parser
      //throw  exception();
      // I don't launch exception because some script are null
      //Look this example https://www.blockchain.com/it/btc/tx/c78854360663aa585b0400df7297afc458521bf858e6c93b34d4ca696ae30f29
      //and look te test NullDataTrasaction
      return scriptString;
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

    LOG_IF(WARNING, (scriptLenght.getValue() == 16)) << "readed a null data transaction The lenght is 16 byte";

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

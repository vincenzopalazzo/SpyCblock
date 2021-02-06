// Copyright (c) 2018-2021 Vincenzo Palazzo vincenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt
#include "DScript.h"

#include <glog/logging.h>

#include <sstream>

#include "../../util/serialize.h"
#include "../../util/strencodings.h"

using namespace spyCBlock;
using namespace std;

string DScript::getScriptToSerializationForm() const {
  if (rawScriptString.empty()) {
    // Before introducing the OP_RETURN some script was null.
    LOG(WARNING) << "The raw script is null " + rawScriptString;
    return rawScriptString;
  }
  return rawScriptString.substr(0, (this->scriptLenght.getValue() * 2));
}

void DScript::decode(std::ifstream &stream) {
  this->scriptLenght.decode(stream);

  char buffer[scriptLenght.getValue()];
  LOG(INFO) << "Dimension script: " << scriptLenght.getValue();

  stream.read(buffer, static_cast<long>(
                          scriptLenght.getValue()));  // TODO look this canged

  LOG_IF(ERROR, (sizeof(buffer) != scriptLenght.getValue()))
      << "Dimension script readed wrong";
  scriptString = string(buffer, scriptLenght.getValue());

  rawScriptString = HexStr(scriptString);
  LOG(INFO) << "The hex script is: " << rawScriptString;
}

string DScript::toString() {
  string stringForm = "Length script: ";
  stringForm += to_string(this->scriptLenght.getValue());
  stringForm += "\n";
  stringForm += "Script: ";
  stringForm += rawScriptString;

  return stringForm;
}

// getter and setter
const DVarInt &DScript::getScriptLength() const { return scriptLenght; }

const string &DScript::getRawScriptString() const { return rawScriptString; }

const string &DScript::getScriptString() const { return scriptString; }

// Copyright (c) 2018-2021Vincenzo Palazzo vincenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include "TransactionWitness.h"

#include <glog/logging.h>

#include "../../DefinitionMacro.h"
#include "../../persistence/SerializationUtil.h"

using namespace spyCBlock;
using namespace std;

void spyCBlock::TransactionWitness::decode(std::ifstream &stream) {
  assertf(stream.is_open(), "The stream is close");

  LOG(WARNING) << "FINDED TRANSACTION WITNESS";
  compactSize.decode(stream);
  LOG(INFO) << "Compact size is: " << compactSize.getValue();
  for (int i = 0; i < static_cast<int>(compactSize.getValue()); i++) {
    this->witnessStack.emplace_back(DScript{});
    DScript &script = witnessStack.back();
    script.decode(stream);
    LOG(INFO) << "The raw witness script is: " << script.getRawScriptString();
  }
}

std::string TransactionWitness::toSerealizationForm() const {
  string hexForm =
      SerializationUtil::toSerializeForm(this->compactSize.getValue());
  for (DScript script : witnessStack) {
    hexForm.append(
        SerializationUtil::toSerializeForm(script.getScriptLength()));
    hexForm.append(script.getScriptToSerializationForm());
  }
  return hexForm;
}

string TransactionWitness::toString() {
  string stringForm = "Dimension script:";
  stringForm += to_string(compactSize.getValue());
  stringForm += "\n";
  for (auto elementStack : witnessStack) {
    stringForm += elementStack.getScriptString();
    stringForm += "\n";
  }

  return stringForm;
}

// Getter and setter
DVarInt TransactionWitness::getCompactSize() const { return compactSize; }

std::vector<DScript> TransactionWitness::getWitnessStack() const {
  return witnessStack;
}

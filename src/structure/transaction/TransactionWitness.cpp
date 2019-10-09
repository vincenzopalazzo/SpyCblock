// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include <glog/logging.h>

#include "TransactionWitness.h"
#include "../../persistence/SerializationUtil.h"

using namespace spyCBlock;
using namespace std;

void spyCBlock::TransactionWitness::decode(std::ifstream &stream)
{
  if(!stream.is_open()){
    LOG(ERROR) << "The stream is close";
    //TODO Add exception
    return;
  }
  LOG(WARNING) << "FINDED TRANSACTION WITNESS";
  compactSize.decode(stream);
  LOG(INFO) << "Compact size is: " << compactSize.getValue();
  for(int i = 0; i < static_cast<int>(compactSize.getValue()); i++) {
      this->witnessStack.emplace_back(DScript{});
      DScript& script = witnessStack.back();
      script.decode(stream);
      LOG(INFO) << "The raw witness script is: " << script.getRawScriptString();
    }
}

std::string TransactionWitness::toSerealizationForm() const
{
  string hexForm = SerializationUtil::toSerealizeForm(this->compactSize.getValue());
  for(DScript script : witnessStack)
  {
      hexForm.append(SerializationUtil::toSerealizeForm(script.getScriptLenght()));
      hexForm.append(script.getScriptToSerializationForm());
  }
  return hexForm;
}

string TransactionWitness::toString()
{
  string stringForm =  "Dimension script:";
  stringForm += to_string(compactSize.getValue());
  stringForm += "\n";
  for(auto elementStack : witnessStack)
  {
      stringForm += elementStack.getScriptString();
      stringForm += "\n";
  }

  return stringForm;
}

//Getter and setter
DVarInt TransactionWitness::getCompactSize() const
{
    return compactSize;
}

std::vector<DScript> TransactionWitness::getWitnessStack() const
{
    return witnessStack;
}

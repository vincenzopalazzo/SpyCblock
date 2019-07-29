#include <glog/logging.h>

#include "TransactionWitness.h"
using namespace spyCBlock;

void spyCBlock::TransactionWitness::decode(std::ifstream &stream)
{
  if(!stream.is_open()){
    LOG(ERROR) << "The strema is close";
    //Add exception
    return;
  }
  LOG(ERROR) << "FINDED TRANSACTION WITNESS";
  compactSize.decode(stream);
  LOG(INFO) << "Compact size is: " << compactSize.getValue();
  for(int i = 0; i < static_cast<int>(compactSize.getValue()); i++) {
      this->witnessStack.emplace_back(DScript{});
      DScript& script = witnessStack.back();
      script.decode(stream);
      LOG(INFO) << "The raw witness script is: " << script.getRawScriptString();
  }
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

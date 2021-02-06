// Copyright (c) 2018-2021 Vincenzo Palazzo vincenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include "UTXOTransaction.h"

#include <glog/logging.h>

#include <iostream>
#include <string>

#include "../../DefinitionMacro.h"
#include "../../crypto/UtilCrypto.h"
#include "../../util/serialize.h"

using namespace std;

void spyCBlock::UTXOTransaction::decode(
    std::vector<unsigned char> const &dbKey,
    std::vector<unsigned char> const &dbValue) {
  auto prefix = dbKey[0];
  LOG(INFO) << "Prefix is " << prefix;
  if (prefix == 0x43 && dbKey.size() > 32) {
    this->txId = UtilCrypto::BytesLittleEndianToStringBigEndian(dbKey, 1, 32);
    LOG(INFO) << "Transaction ID " << this->txId;
    stringstream stream;
    stream << dbKey[33];
    this->vOut =
        ReadVarInt<stringstream, VarIntMode::NONNEGATIVE_SIGNED, int64_t>(
            stream);
    LOG(INFO) << "Vout in var in is: " << this->vOut;
  }
}

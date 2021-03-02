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
        std::vector<unsigned char> const &dbValue,
        std::string const &obfuscateKey) {
    auto prefix = dbKey[0];
    LOG(INFO) << "Prefix is " << prefix;
    if (prefix == 0x43 && dbKey.size() > 32) {
        this->txId = UtilCrypto::BytesLittleEndianToStringBigEndian(dbKey, 1, 32);
        LOG(INFO) << "Transaction ID " << this->txId;
        stringstream stream;
        for (std::size_t i = 33; i < dbKey.size(); i++)
            stream << dbKey[i];
        LOG(INFO) << stream.str();
        this->vOut = ReadVarInt<stringstream, VarIntMode::DEFAULT, uint64_t>(stream);
        LOG(INFO) << "Vout in var in is: " << this->vOut;

        auto exstendedObKey = extendObfuscateKey(obfuscateKey);
        LOG(INFO) << "Extended Obfuscated key is: " << exstendedObKey;
    }
}

//TODO: Working here: https://github.com/lightningamp/bitcoin-utxo-dump/blob/3377e131ae3aa54248142f0d2375da08c002a9bd/utxodump.go#L267
std::string spyCBlock::UTXOTransaction::extendObfuscateKey(std::string const &obfuscateKey) {
    std::string extended;
    return extended;
}

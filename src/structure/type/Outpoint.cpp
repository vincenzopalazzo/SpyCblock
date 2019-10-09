// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core developers
// Copyright (c) 2018-2019 Vincenzo Palazzo vincenzopalazzodev@gmail.com
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string>

#include "Outpoint.h"

using namespace std;
using namespace spyCBlock;

void OutPoint::setHash(const uint256 &hash) {
    this->hash = hash;
}

const uint256 &OutPoint::getHash() const {
    return this->hash;
}

uint32_t OutPoint::getN() const {
    return n;
}

bool operator<(const OutPoint &a, const OutPoint &b) {
    return false;
}

bool operator==(const OutPoint &a, const OutPoint &b) {
    return false;
}

bool operator!=(const OutPoint &a, const OutPoint &b) {
    return false;
}

std::string OutPoint::ToString() const {
    string stringForm = "Hash public key sender: ";
    stringForm += this->hash.ToString();
    stringForm += "N: ";
    stringForm += to_string(this->n);
    stringForm += "\n";
    return stringForm;
}


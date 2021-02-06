/*
 * Bitcoin cryptography library
 * Copyright (c) Project Nayuki
 *
 * https://www.nayuki.io/page/bitcoin-cryptography-library
 * https://github.com/nayuki/Bitcoin-Cryptography-Library
 */

#include "../cryptobitcoin/Sha256Hash.hpp"

#include <algorithm>
#include <cassert>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <string>

#include "../cryptobitcoin/Utils.hpp"

using std::size_t;
using std::uint8_t;

Sha256Hash::Sha256Hash(const uint8_t hash[HASH_LEN], size_t len) {
  assert(hash != nullptr && len == HASH_LEN);
  std::memcpy(value, hash, sizeof(value));
}

Sha256Hash::Sha256Hash(const char *str) : value() {
  assert(str != nullptr && std::strlen(str) == HASH_LEN * 2);
  for (int i = 0; i < HASH_LEN * 2; i++) {
    int digit = Utils::parseHexDigit(str[HASH_LEN * 2 - 1 - i]);
    assert(digit != -1);
    value[i >> 1] |= digit << ((i & 1) << 2);
  }
}

bool Sha256Hash::operator==(const Sha256Hash &other) const {
  int diff = 0;
  for (int i = 0; i < HASH_LEN; i++) diff |= value[i] ^ other.value[i];
  return diff == 0;
}

bool Sha256Hash::operator!=(const Sha256Hash &other) const {
  return !(*this == other);
}

//@author https://github.com/vincenzopalazzo
std::string Sha256Hash::ToString() {
  std::string hashResult;
  std::stringstream stream;

  for (int i = 0; i < HASH_LEN; i++) {
    unsigned int valueInt = static_cast<unsigned int>(value[i]);
    stream << std::hex << std::setfill('0') << std::setprecision(2)
           << std::setw(2) << valueInt;
  }
  hashResult = stream.str();
  return hashResult;
}

//@author https://github.com/vincenzopalazzo
std::string Sha256Hash::ToStringForProtocol() {
  // reverse array value
  uint8_t clone_has_raw[HASH_LEN];

  int position = 0;
  for (int i = HASH_LEN - 1; i >= 0; i--) {
    clone_has_raw[position] = value[i];
    position++;
  }

  std::string hashResult;
  std::stringstream stream;

  for (int i = 0; i < HASH_LEN; i++) {
    unsigned int valueInt = static_cast<unsigned int>(clone_has_raw[i]);
    stream << std::hex << std::setfill('0') << std::setprecision(2)
           << std::setw(2) << valueInt;
  }
  hashResult = stream.str();
  stream.clear();
  return hashResult;
}

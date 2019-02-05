//
// Created by https://github.com/vincenzopalazzo on 1/24/19.
//

#include "Outpoint.h"

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
    return std::__cxx11::string();
}

void OutPoint::SetNull() {

}

bool OutPoint::IsNull() {
    return false;
}

void OutPoint::setN(uint32_t n) {

}

void OutPoint::setHash(const uint256 &hash) {
    this->hash = hash;
}

const uint256 &OutPoint::getHash() const {
    return this->hash;
}

uint32_t OutPoint::getN() const {
    return n;
}

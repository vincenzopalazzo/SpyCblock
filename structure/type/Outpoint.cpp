//
// Created by https://github.com/vincenzopalazzo on 1/24/19.
//

#include <sstream>
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
    stringstream stream;
    stream << "Hash public key sender: " <<  this->hash.ToString() << endl;
    stream << "N: " << this->n << endl;
    return stream.str();
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

OutPoint::~OutPoint()
{

}

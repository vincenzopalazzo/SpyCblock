//
// Created by https://github.com/vincenzopalazzo on 1/24/19.
//
#include <string>

#include "Outpoint.h"

using namespace std;

OutPoint::~OutPoint()
{

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


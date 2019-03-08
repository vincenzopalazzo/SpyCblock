//
// Created by https://github.com/vincenzopalazzo on 3/7/19.
//

#include "DAOException.h"

const char *spyCBlock::DAOException::what() const noexcept  {
    string exceptionMessage = "DAOException Generated from ";
    exceptionMessage.append(cause);
    return exceptionMessage.c_str();
}

spyCBlock::DAOException::DAOException(const string &cause) : cause(cause) {
    exception();
    this->cause = cause;
}

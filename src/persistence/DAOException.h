// Copyright (c) 2018-2021Vincenzo Palazzo vincenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef SPYCBLOCK_DAOEXCEPTION_H
#define SPYCBLOCK_DAOEXCEPTION_H

#include <string>
#include <stdexcept>

namespace spyCBlock {

    class DAOException : public std::runtime_error {
    public:
        DAOException(const std::string &cause) throw(): std::runtime_error(cause) {};
    };
}


#endif //SPYCBLOCK_DAOEXCEPTION_H

//
// Created by https://github.com/vincenzopalazzo on 3/7/19.
//

#ifndef SPYCBLOCK_DAOEXCEPTION_H
#define SPYCBLOCK_DAOEXCEPTION_H

#include <string>
#include <stdexcept>

namespace spyCBlock{

    class DAOException : public std::runtime_error
    {
      public:
          DAOException(const std::string &cause) throw() : std::runtime_error(cause)
          {};
      };
}


#endif //SPYCBLOCK_DAOEXCEPTION_H

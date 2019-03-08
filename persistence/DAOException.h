//
// Created by https://github.com/vincenzopalazzo on 3/7/19.
//

#ifndef SPYCBLOCK_DAOEXCEPTION_H
#define SPYCBLOCK_DAOEXCEPTION_H


#include <exception>
#include <string>
#include <stdexcept>

using namespace std;

namespace spyCBlock{

    class DAOException : public exception{

    private:
        string cause;

    public:
        DAOException(const string &cause);

        const char* what() const noexcept override;
    };
}


#endif //SPYCBLOCK_DAOEXCEPTION_H

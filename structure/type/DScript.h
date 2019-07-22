#ifndef PARSINGBLOCKCHAIN_CSCRIPT_H
#define PARSINGBLOCKCHAIN_CSCRIPT_H


#include <vector>
#include <fstream>
#include "DVarInt.h"

/**
 * Created on 2/4/19.
 * @author https://github.com/vincenzopalazzo
 */
//TODO refactoring
namespace spyCBlock
{
    class DScript
    {
      private:

          DVarInt scriptLenght;

          std::string scriptString;

          std::string rawScriptString;

      public:

          const char* getScriptRaw() const;

          const std::string &getRawScriptString() const;

          const DVarInt &getScriptLenght() const;

          std::string getScriptToSerializationForm() const;

          std::string toString();

          const std::string &getScriptString() const;

          void decode(std::ifstream &stream);
      };
}


#endif //PARSINGBLOCKCHAIN_CSCRIPT_H

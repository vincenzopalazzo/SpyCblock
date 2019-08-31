#ifndef PARSINGBLOCKCHAIN_CSCRIPT_H
#define PARSINGBLOCKCHAIN_CSCRIPT_H

#include <vector>
#include <fstream>

#include "DVarInt.h"

// @author https://github.com/vincenzopalazzo
namespace spyCBlock
{
    class DScript
    {
      public:

          const char* getScriptRaw() const;

          const std::string &getRawScriptString() const;

          const DVarInt &getScriptLenght() const;

          std::string getScriptToSerializationForm() const;

          std::string toString();

          const std::string &getScriptString() const;

          void decode(std::ifstream &stream);

      private:

        DVarInt scriptLenght;

        std::string scriptString;

        std::string rawScriptString;
      };
}


#endif //PARSINGBLOCKCHAIN_CSCRIPT_H

#pragma once

#include <fstream>
#include <string>

namespace bc
{

    class Loader
    {
        std::ifstream *filein;
        char linebuffer[257];

      public:
        explicit Loader(std::string filein);
        ~Loader();
        char next();
        bool eof();
    };

} // namespace bc

#include "loader.h"
#include <stdlib.h>

namespace bc {
    Loader::Loader(std::string filename) {
        filein = new std::ifstream(filename.c_str());
        if (!filein->is_open()) {
            throw std::string("arquivo " + filename + " nao encontrado!");
        }
    }

    Loader::~Loader() {
        if (filein) {
            if (filein->is_open()) {
                filein->close();
            }

            delete filein;
        }
    }

    bool Loader::eof() {
        return filein->eof();
    }

    char Loader::next() {
        char temp;
        if (!eof()) {
            filein->get(temp);
        }
        return temp;
    }
}

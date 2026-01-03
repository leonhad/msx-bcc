#include "loader.h"
#include <stdlib.h>

namespace bc {
    Loader::Loader(string filename) {
        filein = new ifstream(filename.c_str());
        if (!filein->is_open()) {
            throw string("arquivo " + filename + " nao encontrado!");
        }
    }

    Loader::~Loader() {
        if (filein != NULL) {
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

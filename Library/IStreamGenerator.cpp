#include "IStreamGenerator.h"

namespace miit::algebra {

    IStreamGenerator::IStreamGenerator(std::istream& input) : in(input) { }

    int IStreamGenerator::generate()
    {
        int value = 0;
        in >> value;
        return value;
    }

}


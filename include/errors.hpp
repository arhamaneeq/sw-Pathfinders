#ifndef ERRORS_HPP
#define ERRORS_HPP

#include "types.hpp"

namespace Errors {
    void   outOfBoundingBox(int x, int y, int W, int H, int w = 0, int h = 0);
    void outOfBoundingRange(int x, int W);
}


#endif
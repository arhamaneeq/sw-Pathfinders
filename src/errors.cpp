#include "../include/errors.hpp"

void Errors::outOfBoundingBox(int x, int y, int W, int H, int w, int h) {
    std::ostringstream oss;
    oss << "Out of bounds. (x, y) must satisfy ";
    oss << w << " <= " << x << " < " << W;
    oss << " and ";
    oss << h << " <= " << y << " < " << H;
    oss << ". Got (" << x << " ," << y << ") instead.";

    throw std::out_of_range(oss.str());
}

void Errors::outOfBoundingRange(int x, int W) {
    std::ostringstream oss;
    oss << "Out of bounds. x must satisfy ";
    oss << "0 <= x < " << W;
    oss << ". Got x = " << x << " instead.";

    throw std::out_of_range(oss.str());
}
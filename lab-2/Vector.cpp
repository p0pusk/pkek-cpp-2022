#include "Vector.h"

Vector::Vector(float x, float y): x(x), y(y) {

}

Vector Vector::operator+(const Vector &v) const {
    return {x + v.x, y + v.y};
}

Vector Vector::operator-(const Vector &v) const {
    return {x - v.x, y - v.y};
}

bool Vector::operator==(const Vector &v) const {
    if (x == v.x && y == v.y) {
        return true;
    }
    else {
        return false;
    }
}

bool Vector::operator!=(const Vector &v) const {
    if (x == v.x && y == v.y) {
        return false;
    }
    else {
        return true;
    }
}

void Vector::operator+=(const Vector &v) {
    x += v.x;
    y += v.y;
}

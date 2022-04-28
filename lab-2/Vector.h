#pragma once
#include <iostream>


class Vector
{
  public:
    float x;
    float y;

    Vector(float, float);
    Vector operator+(const Vector&) const;
    void operator+=(const Vector&);
    Vector operator-(const Vector&) const;
    bool operator==(const Vector&) const;
    bool operator!=(const Vector & v) const;
};




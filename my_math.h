

#ifndef __MY_MATH_H_INCLUDED__
#define __MY_MATH_H_INCLUDED__

#include <array>
#include <stdlib.h>
#include <cmath>
#include <iostream>

using std::array;

//The first two values are what are being interpolated
//The third value is the proportion between the two (a small scale means that
//the first value is weighted heavily, a 1 scale means the second value)
float lerp(float, float, float);
array<float, 3> vertex_normalize(array<float, 3>);
float randf(float, float);

float magnitude(array<float, 3> in_vert);
float magnitude(array<float, 4> in_vert);
array<float, 3> cross(array<float, 3> u, array<float, 3> v);
float dot(array<float, 3> u, array<float, 3> v);

void dump_vector(array<float, 3> v);

int eucmod(int a, int modulus);

#endif
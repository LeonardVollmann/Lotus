#ifndef LOTUS_MATHS_HPP_INCLUDED
#define LOTUS_MATHS_HPP_INCLUDED

#define MATH_PI 3.1415926535897932384626433832795
#define toRadians(x) (float)(((x) * MATH_PI / 180.0f))
#define toDegrees(x) (float)(((x) * 180.0f / MATH_PI))

#include "lotus_vec2.hpp"
#include "lotus_vec3.hpp"
#include "lotus_vec4.hpp"
#include "lotus_mat4.hpp"
#include "lotus_quat.hpp"

#endif
#ifndef LOTUS_MATRIX_H
#define LOTUS_MATRIX_H

#include "vector.h"

#include <cmath>
#include <cassert>
#include <stdint.h>

namespace lotus { namespace maths {
    
    template <typename T, uint8_t D>
    class Matrix
    {
    private:
        T matrix[D][D];
    public:
        template<uint8_t N>
        Matrix<T, D>(const Matrix<T, N> &r);
        
        Matrix<T, D>() {}
        
        inline const T *operator[](uint8_t i) const { return matrix[i]; }
        inline T *operator[](uint8_t i) { return matrix[i]; }
        
        bool operator==(const Matrix<T, D> &r) const;
        inline bool operator!=(const Matrix<T, D> &r) const { return !operator==(r); }
        
        Matrix<T, D> initIdentity();
        Matrix<T, D> initTranslation(const Vector<T, D - 1> &r);
        Matrix<T, D> initScale(const Vector<T, D - 1> &r);
        Matrix<T, D> initRotation(const Vector3<T> &v, float angle);
        
        Matrix<T, 4> initOrthographicProjection(const T &left, const T &right,
                                                const T &top, const T &bottom,
                                                const T &near, const T &far);
        
        Matrix<T, 4> initPerspectiveProjection(const T &left, const T &right,
                                               const T &top, const T &bottom,
                                               const T &near, const T &far);
        
        Vector<T, D> getRow(uint8_t row) const;
        Vector<T, D> getCol(uint8_t col) const;
        
        void setRow(uint8_t row, const Vector<T, D> &r);
        void setCol(uint8_t col, const Vector<T, D> &r);
        inline void set(uint8_t x, uint8_t y, const T &val) { (*this)[x][y] = val; }
        
        Matrix<T, D> operator*(const Matrix<T, D> &r) const;
        Matrix<T, D> operator*=(const Matrix<T, D> &r);
        
        Matrix<T, D> transposed() const;
        
    };
    
    typedef Matrix<float,    3> mat3f;
    typedef Matrix<double,   3> mat3d;
    typedef Matrix<int8_t,   3> mat3i8;
    typedef Matrix<int16_t,  3> mat3i16;
    typedef Matrix<int32_t,  3> mat3i32;
    typedef Matrix<int64_t,  3> mat3i64;
    typedef Matrix<uint8_t,  3> mat3uint8;
    typedef Matrix<uint16_t, 3> mat3uint16;
    typedef Matrix<uint32_t, 3> mat3uint32;
    typedef Matrix<uint64_t, 3> mat3uint64;
    
    typedef Matrix<float,    4> mat4f;
    typedef Matrix<double,   4> mat4d;
    typedef Matrix<int8_t,   4> mat4i8;
    typedef Matrix<int16_t,  4> mat4i16;
    typedef Matrix<int32_t,  4> mat4i32;
    typedef Matrix<int64_t,  4> mat4i64;
    typedef Matrix<uint8_t,  4> mat4uint8;
    typedef Matrix<uint16_t, 4> mat4uint16;
    typedef Matrix<uint32_t, 4> mat4uint32;
    typedef Matrix<uint64_t, 4> mat4uint64;
    
} }

#include "matrix.inl"

#endif
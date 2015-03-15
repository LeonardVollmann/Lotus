#ifndef LOTUS_MATRIX_H
#define LOTUS_MATRIX_H

#include "vector.h"

#include <cmath>
#include <cassert>
#include <stdint.h>

namespace lotus { namespace maths {
    
    template <typename T, unsigned int D>
    class Matrix
    {
    private:
        T matrix[D][D];
    public:
        inline const T *operator[](unsigned int i) const { return matrix[i]; }
        inline T *operator[](unsigned int i) { return matrix[i]; }
        
        inline bool operator==(const Matrix<T, D> &r) const
        {
            for (unsigned int i = 0; i < D; i++) {
                for (unsigned int j = 0; j < D; j++) {
                    if ((*this)[i][j] != r[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }
        
        inline bool operator!=(const Matrix<T, D> &r) const { return !operator==(r); }
        
        inline Matrix<T, D> initIdentity()
        {
            for (unsigned int i = 0; i < D; i++) {
                for (unsigned int j = 0; j < D; j++) {
                    if (i == j) {
                        (*this)[i][j] = 1;
                    } else {
                        (*this)[i][j] = 0;
                    }
                }
            }
            return *this;
        }
        
        inline Matrix<T, D> initTranslation(const Vector<T, D - 1> &r)
        {
            for (unsigned int i = 0; i < D; i++) {
                for (unsigned int j = 0; j < D; j++) {
                    if (i < D - 1 && j == D - 1) {
                        (*this)[i][j] = r[i];
                    } else if (i == j) {
                        (*this)[i][j] = 1;
                    } else {
                        (*this)[i][j] = 0;
                    }
                }
            }
            return *this;
        }
        
        inline Matrix<T, D> initScale(const Vector<T, D - 1> &r)
        {
            for (unsigned int i = 0; i < D; i++) {
                for (unsigned int j = 0; j < D; j++) {
                    if (i == j && i < D - 1) {
                        (*this)[i][j] = r[i];
                    } else if (i == j && i == D - 1) {
                        (*this)[i][j] = 1;
                    } else {
                        (*this)[i][j] = 0;
                    }
                }
            }
            return *this;
        }
        
        inline Matrix<T, D> initRotation(const Vector3<T> &v, float angle)
        {
            assert(D > 2);
            
            const float sinAngle = sinf(angle);
            const float cosAngle = cosf(angle);
            
            const float xsqr = v.getX() * v.getX();
            const float ysqr = v.getY() * v.getY();
            const float zsqr = v.getZ() * v.getZ();
            
            (*this)[0][0] = cosAngle + xsqr * (1 - cosAngle); (*this)[0][1] = v.getX() * v.getY() * (1 - cosAngle) - v.getZ() * sinAngle; (*this)[0][2] = v.getX() * v.getZ() * (1 - cosAngle) + v.getY() * sinAngle;
            (*this)[1][0] = v.getY() * v.getX() * (1 - cosAngle) + v.getU() * sinAngle; (*this)[1][1] = cosAngle + ysqr * (1 - cosAngle); (*this)[1][2] = v.getY() * v.getZ() * (1 - cosAngle) - v.getX() * sinAngle;
            (*this)[2][0]  = v.getZ() * v.getX() * (1 - cosAngle) - v.getY() * sinAngle; (*this)[2][1] = v.getZ() * v.getY() * (1 - cosAngle) + v.getX() * sinAngle; (*this)[2][2] = cosAngle + zsqr * (1 - cosAngle);
            
            return *this;
        }
        
        inline Vector<T, D> getRow(unsigned int row) const
        {
            Vector<T, D> result;
            for (unsigned int i = 0; i < D; i++) {
                result[i] = (*this)[row][i];
            }
            return result;
        }
        
        inline Vector<T, D> getCol(unsigned int col) const
        {
            Vector<T, D> result;
            for (unsigned int i = 0; i < D; i++) {
                result[i] = (*this)[i][col];
            }
            return result;
        }
        
        inline void setRow(unsigned int row, const Vector<T, D> &r)
        {
            for (unsigned int i = 0; i < D; i++) {
                (*this)[row][i] = r[i];
            }
        }
        
        inline void setCol(unsigned int col, const Vector<T, D> &r)
        {
            for (unsigned int i = 0; i < D; i++) {
                (*this)[i][col] = r[i];
            }
        }
        
        inline void set(unsigned int x, unsigned int y, const T &val) { (*this)[x][y] = val; }
        
        inline Matrix<T, D> operator*(const Matrix<T, D> &r) const
        {
            Matrix<T, D> result;
            for (unsigned int i = 0; i < D; i++) {
                for (unsigned int j = 0; j < D; j++) {
                    result[i][j] = getRow(i).dot(r.getCol(j));
                }
            }
            return result;
        }
        
        inline Matrix<T, D> operator*=(const Matrix<T, D> &r)
        {
            *this = operator*(r);
            return *this;
        }
        
        inline Matrix<T, D> transposed() const
        {
            Matrix<T, D> result;
            for (unsigned int i = 0; i < D; i++) {
                for (unsigned int j = 0; j < D; j++) {
                    result[i][j] = (*this)[j][i];
                }
            }
            return result;
        }
    };
    
    template<typename T>
    class Matrix3 : public Matrix<T, 3>
    {
    public:
        Matrix3() {}
        
        template <unsigned int D>
        Matrix3(const Matrix<T, D> &r)
        {
            if (D < 3) {
                this->initIdentity();
                
                for (unsigned int i = 0; i < D; i++) {
                    for (unsigned int j = 0; j < D; j++)
                    {
                        (*this)[i][j] = r[i][j];
                    }
                }
            } else {
                for (unsigned int i = 0; i < 3; i++) {
                    for (unsigned int j = 0; j < 3; j++)
                    {
                        (*this)[i][j] = r[i][j];
                    }
                }
            }
        }
    };
    
    template <typename T>
    class Matrix4 : public Matrix<T, 4>
    {
    public:
        Matrix4() {}
        
        template <unsigned int D>
        Matrix4(const Matrix<T, D> &r)
        {
            if (D < 4) {
                this->initIdentity();
                
                for (unsigned int i = 0; i < D; i++) {
                    for (unsigned int j = 0; j < D; j++)
                    {
                        (*this)[i][j] = r[i][j];
                    }
                }
            } else {
                for (unsigned int i = 0; i < 4; i++) {
                    for (unsigned int j = 0; j < 4; j++)
                    {
                        (*this)[i][j] = r[i][j];
                    }
                }
            }
        }
    };
    
    typedef Matrix3<float>    mat3f;
    typedef Matrix3<double>    mat3d;
    typedef Matrix3<int8_t>   mat3i8;
    typedef Matrix3<int16_t>  mat3i16;
    typedef Matrix3<int32_t>  mat3i32;
    typedef Matrix3<int64_t>  mat3i64;
    typedef Matrix3<uint8_t>  mat3uint8;
    typedef Matrix3<uint16_t> mat3uint16;
    typedef Matrix3<uint32_t> mat3uint32;
    typedef Matrix3<uint64_t> mat3uint64;
    
    typedef Matrix4<float>    mat4f;
    typedef Matrix4<double>   mat4d;
    typedef Matrix4<int8_t>   mat4i8;
    typedef Matrix4<int16_t>  mat4i16;
    typedef Matrix4<int32_t>  mat4i32;
    typedef Matrix4<int64_t>  mat4i64;
    typedef Matrix4<uint8_t>  mat4uint8;
    typedef Matrix4<uint16_t> mat4uint16;
    typedef Matrix4<uint32_t> mat4uint32;
    typedef Matrix4<uint64_t> mat4uint64;
    
} }

#endif
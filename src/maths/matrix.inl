#include "matrix.h"

namespace lotus { namespace maths {
    
    template<typename T, uint8_t D>
    template<uint8_t N>
    Matrix<T, D>::Matrix(const Matrix<T, N> &r)
    {
        if (N < D) {
            initIdentity();
            
            for (uint8_t i = 0; i < N; i++)
            {
                for (uint8_t j = 0; j < N; j++)
                {
                    (*this)[i][j] = r[i][j];
                }
            }
        } else {
            for (uint8_t i = 0; i < D; i++)
            {
                for (uint8_t j = 0; j < D; j++)
                {
                    (*this)[i][j] = r[i][j];
                }
            }
        }
    }
    
    template<typename T, uint8_t D>
    bool Matrix<T, D>::operator==(const Matrix<T, D> &r) const
    {
        for (uint8_t i = 0; i < D; i++)
        {
            for (uint8_t j = 0; j < D; j++)
            {
                if ((*this)[i][j] != r[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
    
    template<typename T, uint8_t D>
    Matrix<T, D> Matrix<T, D>::initIdentity()
    {
        for (uint8_t i = 0; i < D; i++) {
            for (uint8_t j = 0; j < D; j++)
            {
                if (i == j)
                {
                    (*this)[i][j] = 1;
                }
                else
                 {
                    (*this)[i][j] = 0;
                }
            }
        }
        return *this;
    }
    
    template<typename T, uint8_t D>
    Matrix<T, D> Matrix<T, D>::initTranslation(const Vector<T, D - 1> &r)
    {
        for (uint8_t i = 0; i < D; i++)
        {
            for (uint8_t j = 0; j < D; j++)
            {
                if (i < D - 1 && j == D - 1)
                {
                    (*this)[i][j] = r[i];
                }
                else if (i == j)
                {
                    (*this)[i][j] = 1;
                }
                else
                {
                    (*this)[i][j] = 0;
                }
            }
        }
        return *this;
    }
    
    template<typename T, uint8_t D>
    Matrix<T, D> Matrix<T, D>::initScale(const Vector<T, D - 1> &r)
    {
        for (uint8_t i = 0; i < D; i++)
        {
            for (uint8_t j = 0; j < D; j++)
            {
                if (i == j && i < D - 1)
                {
                    (*this)[i][j] = r[i];
                }
                else if (i == j && i == D - 1)
                {
                    (*this)[i][j] = 1;
                }
                else
                {
                    (*this)[i][j] = 0;
                }
            }
        }
        return *this;
    }
    
    template<typename T, uint8_t D>
    Matrix<T, D> Matrix<T, D>::initRotation(const Vector3<T> &v, float angle)
    {
        assert(D > 2);
        
        const float sinAngle = sinf(angle);
        const float cosAngle = cosf(angle);
        
        const float xsqr = v.getX() * v.getX();
        const float ysqr = v.getY() * v.getY();
        const float zsqr = v.getZ() * v.getZ();
        
        (*this)[0][0] = cosAngle + xsqr * (1 - cosAngle);
        (*this)[0][1] = v.getX() * v.getY() * (1 - cosAngle) - v.getZ() * sinAngle;
        (*this)[0][2] = v.getX() * v.getZ() * (1 - cosAngle) + v.getY() * sinAngle;
        
        (*this)[1][0] = v.getY() * v.getX() * (1 - cosAngle) + v.getU() * sinAngle;
        (*this)[1][1] = cosAngle + ysqr * (1 - cosAngle);
        (*this)[1][2] = v.getY() * v.getZ() * (1 - cosAngle) - v.getX() * sinAngle;
        
        (*this)[2][0]  = v.getZ() * v.getX() * (1 - cosAngle) - v.getY() * sinAngle;
        (*this)[2][1] = v.getZ() * v.getY() * (1 - cosAngle) + v.getX() * sinAngle;
        (*this)[2][2] = cosAngle + zsqr * (1 - cosAngle);
        
        return *this;
    }
    
    template<typename T, uint8_t D>
    Vector<T, D> Matrix<T, D>::getRow(uint8_t row) const
    {
        Vector<T, D> result;
        for (uint8_t i = 0; i < D; i++)
        {
            result[i] = (*this)[row][i];
        }
        return result;
    }
    
    template<typename T, uint8_t D>
    Vector<T, D> Matrix<T, D>::getCol(uint8_t col) const
    {
        Vector<T, D> result;
        for (uint8_t i = 0; i < D; i++)
        {
            result[i] = (*this)[i][col];
        }
        return result;
    }
    
    template<typename T, uint8_t D>
    void Matrix<T, D>::setRow(uint8_t row, const Vector<T, D> &r)
    {
        for (uint8_t i = 0; i < D; i++)
        {
            (*this)[row][i] = r[i];
        }
    }
    
    template<typename T, uint8_t D>
    void Matrix<T, D>::setCol(uint8_t col, const Vector<T, D> &r)
    {
        for (uint8_t i = 0; i < D; i++)
        {
            (*this)[i][col] = r[i];
        }
    }
    
    template<typename T, uint8_t D>
    Matrix<T, D> Matrix<T, D>::operator*(const Matrix<T, D> &r) const
    {
        Matrix<T, D> result;
        for (uint8_t i = 0; i < D; i++)
        {
            for (uint8_t j = 0; j < D; j++)
            {
                result[i][j] = getRow(i).dot(r.getCol(j));
            }
        }
        return result;
    }
    
    template<typename T, uint8_t D>
    Matrix<T, D> Matrix<T, D>::operator*=(const Matrix<T, D> &r)
    {
        *this = operator*(r);
        return *this;
    }
    
    template<typename T, uint8_t D>
    Matrix<T, D> Matrix<T, D>::transposed() const
    {
        Matrix<T, D> result;
        for (uint8_t i = 0; i < D; i++)
        {
            for (uint8_t j = 0; j < D; j++)
            {
                result[i][j] = (*this)[j][i];
            }
        }
        return result;
    }
    
} }
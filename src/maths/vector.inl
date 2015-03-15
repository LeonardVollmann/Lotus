#include "vector.h"

namespace lotus { namespace maths {
    
    template<typename T, uint8_t D>
    bool Vector<T, D>::operator==(const Vector<T, D> &r) const
    {
        for (uint8_t i = 0; i < D; i++)
        {
            if ((*this)[i] != r[i])
            {
                return false;
            }
        }
        return true;
    }
    
    template<typename T, uint8_t D>
    Vector<T, D> Vector<T, D>::operator+(const Vector<T, D> &r) const
    {
        Vector<T, D> result;
        for (uint8_t i = 0; i < D; i++)
        {
            result[i] = (*this)[i] + r[i];
        }
        return result;
    }
    
    template<typename T, uint8_t D>
    Vector<T, D> Vector<T, D>::operator-(const Vector<T, D> &r) const
    {
        Vector<T, D> result;
        for (uint8_t i = 0; i < D; i++)
        {
            result[i] = (*this)[i] - r[i];
        }
        return result;
    }
    
    template<typename T, uint8_t D>
    Vector<T, D> Vector<T, D>::operator*(const T &r) const
    {
        Vector<T, D> result;
        for (uint8_t i = 0; i < D; i++)
        {
            result[i] = (*this)[i] * r;
        }
        return result;
    }
    
    template<typename T, uint8_t D>
    Vector<T, D> Vector<T, D>::operator/(const T &r) const
    {
        Vector<T, D> result;
        for (uint8_t i = 0; i < D; i++)
        {
            result[i] = (*this)[i] / r;
        }
        return result;
    }
    
    template<typename T, uint8_t D>
    Vector<T, D> Vector<T, D>::operator+=(const Vector<T, D> &r)
    {
        for (uint8_t i = 0; i < D; i++)
        {
            (*this)[i] += r[i];
        }
        return *this;
    }
    
    template<typename T, uint8_t D>
    Vector<T, D> Vector<T, D>::operator-=(const Vector<T, D> &r)
    {
        for (uint8_t i = 0; i < D; i++)
        {
            (*this)[i] -= r[i];
        }
        return *this;
    }
    
    template<typename T, uint8_t D>
    Vector<T, D> Vector<T, D>::operator*=(const T &r)
    {
        for (uint8_t i = 0; i < D; i++)
        {
            (*this)[i] *= r;
        }
        return *this;
    }
    
    template<typename T, uint8_t D>
    Vector<T, D> Vector<T, D>::operator/=(const T &r)
    {
        for (uint8_t i = 0; i < D; i++)
        {
            (*this)[i] /= r;
        }
        return *this;
    }
    
    template<typename T, uint8_t D>
    T Vector<T, D>::dot(const Vector<T, D> &r) const
    {
        T result = 0;
        for (uint8_t i = 0; i < D; i++)
        {
            result += (*this)[i] * r[i];
        }
        return result;
    }
    
    template<typename T, uint8_t D>
    Vector<T, D> Vector<T, D>::abs() const
    {
        Vector<T, D> result;
        for (uint8_t i = 0; i < D; i++)
        {
            result[i] = (T)fabs((*this)[i]);
        }
        return result;
    }
    
    template<typename T, uint8_t D>
    Vector<T, D> Vector<T, D>::lerp(const Vector<T, D> &r, const T &beta) const
    {
        Vector<T, D> result;
        for (uint8_t i = 0; i < D; i++)
        {
            result[i] = (1 - beta) * (*this)[i] + beta * r[i];
        }
        return result;
    }
    
    template<typename T>
    Vector2<T>::Vector2(const Vector2<T> &r)
    {
        (*this) = r;
    }
    
    template<typename T>
    Vector2<T>::Vector2(const T &x, const T &y)
    {
        (*this)[0] = x;
        (*this)[1] = y;
    }
    
    template<typename T>
    Vector3<T>::Vector3(const Vector3<T> &r)
    {
        (*this) = r;
    }
    
    template<typename T>
    Vector3<T>::Vector3(const T &x, const T &y, const T& z)
    {
        (*this)[0] = x;
        (*this)[1] = y;
        (*this)[2] = z;
    }
    
    template<typename T>
    Vector3<T> Vector3<T>::cross(const Vector3<T> &r)
    {
        Vector3<T> result;
        
        result[0] = ((*this)[1] * r[2]) - (((*this))[2] * r[1]);
        result[1] = ((*this)[2] * r[0]) - (((*this))[0] * r[2]);
        result[2] = ((*this)[0] * r[1]) - (((*this))[1] * r[0]);
        
        return result;
    }
    
    template<typename T>
    Vector4<T>::Vector4(const Vector4<T> &r)
    {
        (*this) = r;
    }
    
    template<typename T>
    Vector4<T>::Vector4(const T &x, const T &y, const T &z, const T &w)
    {
        (*this)[0] = x;
        (*this)[1] = y;
        (*this)[2] = z;
        (*this)[3] = w;
    }
    
} }
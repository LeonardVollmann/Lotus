#ifndef LOTUS_VECTOR_H
#define LOTUS_VECTOR_H

#include <stdint.h>

namespace lotus { namespace maths {
    
    template<typename T, unsigned int D>
    class Vector
    {
    private:
        T values[D];
    public:
        inline T operator[](unsigned int i) const { return values[i]; }
        inline T &operator[](unsigned int i) { return values[i]; }
        
        inline bool operator==(const Vector<T, D> &r) const
        {
            for (unsigned int i = 0; i < D; i++) {
                if ((*this)[i] != r[i]) {
                    return false;
                }
            }
            return true;
        }
        
        inline bool operator!=(const Vector<T, D> &r) const { return !this->operator==(r); }
        
        inline Vector<T, D> operator+(const Vector<T, D> &r) const
        {
            Vector<T, D> result;
            for (unsigned int i = 0; i < D; i++) {
                result[i] = (*this)[i] + r[i];
            }
            return result;
        }
        
        inline Vector<T, D> operator-(const Vector<T, D> &r) const
        {
            Vector<T, D> result;
            for (unsigned int i = 0; i < D; i++) {
                result[i] = (*this)[i] - r[i];
            }
            return result;
        }
        
        inline Vector<T, D> operator*(const T &r) const
        {
            Vector<T, D> result;
            for (unsigned int i = 0; i < D; i++) {
                result[i] = (*this)[i] * r;
            }
            return result;
        }
        
        inline Vector<T, D> operator/(const T &r) const
        {
            Vector<T, D> result;
            for (unsigned int i = 0; i < D; i++) {
                result[i] = (*this)[i] / r;
            }
            return result;
        }
        
        inline Vector<T, D> operator+=(const Vector<T, D> &r)
        {
            for (unsigned int i = 0; i < D; i++) {
                (*this)[i] += r[i];
            }
            return *this;
        }
        
        inline Vector<T, D> operator-=(const Vector<T, D> &r)
        {
            for (unsigned int i = 0; i < D; i++) {
                (*this)[i] -= r[i];
            }
            return *this;
        }
        
        inline Vector<T, D> operator*=(const T &r)
        {
            for (unsigned int i = 0; i < D; i++) {
                (*this)[i] *= r;
            }
            return *this;
        }
        
        inline Vector<T, D> operator/=(const T &r)
        {
            for (unsigned int i = 0; i < D; i++) {
                (*this)[i] /= r;
            }
            return *this;
        }
        
        inline T dot(const Vector<T, D> &r) const
        {
            T result = 0;
            for (unsigned int i = 0; i < D; i++) {
                result += (*this)[i] * r[i];
            }
            return result;
        }
        
        inline Vector<T, D> abs() const
        {
            Vector<T, D> result;
            for (unsigned int i = 0; i < D; i++)
            {
                result[i] = (T)fabs((*this)[i]);
            }
            return result;
        }
        
        inline T lengthSquared() const { return this->dot((*this)); }
        
        inline T length() const { return sqrt(this->lengthSquared()); }
        
        inline Vector<T, D> normalized() const
        {
            return *this / this->length();
        }
        
        inline Vector<T, D> lerp(const Vector<T, D> &r, const T &beta) const
        {
            Vector<T, D> result;
            for (unsigned int i = 0; i < D; i++) {
                result[i] = (1 - beta) * (*this)[i] + beta * r[i];
            }
            return result;
        }
    };
    
    template<typename T>
    class Vector2 : public Vector<T, 2>
    {
        Vector2<T>()
        {}
        
        Vector2<T>(const Vector2<T> &r)
        {
             (*this) = r;
        }
        
        Vector2<T>(const T &x, const T &y)
        {
            (*this)[0] = x;
            (*this)[1] = y;
        }
        
        inline T getX() const { return (*this)[0]; }
        inline T getY() const { return (*this)[1]; }
        
        inline void setX(const T &x) { (*this)[0] = x; }
        inline void setY(const T &y) { (*this)[1] = y; }
        
        inline void set(const T &x, const T &y)
        {
            setX(x);
            setY(y);
        }
    };
    
    template <typename T>
    class Vector3 : public Vector<T, 3>
    {
    public:
        Vector3<T>() {}
        
        Vector3<T>(const Vector3<T> &r)
        {
            (*this) = r;
        }
        
        Vector3<T>(const T &x, const T &y, const T& z)
        {
            (*this)[0] = x;
            (*this)[1] = y;
            (*this)[2] = z;
        }
        
        inline T getX() const { return ((*this))[0]; }
        inline T getY() const { return ((*this))[1]; }
        inline T getZ() const { return ((*this))[2]; }
        
        inline void setX(const T &x) { ((*this))[0] = x; }
        inline void setY(const T &y) { ((*this))[1] = y; }
        inline void setZ(const T &z) { ((*this))[2] = z; }
        
        inline void set(const T &x, const T &y, const T &z)
        {
            setX(x);
            setY(y);
            setZ(z);
        }
        
        Vector3<T> cross(const Vector3<T> &r)
        {
            Vector3<T> result;
            
            result[0] = ((*this)[1] * r[2]) - (((*this))[2] * r[1]);
            result[1] = ((*this)[2] * r[0]) - (((*this))[0] * r[2]);
            result[2] = ((*this)[0] * r[1]) - (((*this))[1] * r[0]);
            
            return result;
        }
    };
    
    template <typename T>
    class Vector4 : public Vector<T, 4>
    {
    public:
        Vector4<T>() {}
        
        Vector4<T>(const Vector4<T> &r)
        {
            (*this) = r;
        }
        
        Vector4<T>(const T &x, const T &y, const T &z, const T &w)
        {
            (*this)[0] = x;
            (*this)[1] = y;
            (*this)[2] = z;
            (*this)[3] = w;
        }
        
        inline T getX() const { return (*this)[0]; }
        inline T getY() const { return (*this)[1]; }
        inline T getZ() const { return (*this)[2]; }
        inline T getW() const { return (*this)[3]; }
        
        inline void setX(const T &x) { (*this)[0] = x; }
        inline void setY(const T &y) { (*this)[1] = y; }
        inline void setZ(const T &z) { (*this)[2] = z; }
        inline void setW(const T &w) { (*this)[3] = w; }
        
        inline void set(const T &x, const T &y, const T &z, const T &w)
        {
            setX(x);
            setY(y);
            setZ(z);
            setW(w);
        }
    };
    
    typedef Vector2<float>    vec2f;
    typedef Vector2<double>   vec2d;
    typedef Vector2<int8_t>   vec2i8;
    typedef Vector2<int16_t>  vec2i16;
    typedef Vector2<int32_t>  vec2i32;
    typedef Vector2<int64_t>  vec2i64;
    typedef Vector2<uint8_t>  vec2ui8;
    typedef Vector2<uint16_t> vec2ui16;
    typedef Vector2<uint32_t> vec2ui32;
    typedef Vector2<uint64_t> vec2ui64;
    
    typedef Vector3<float>    vec3f;
    typedef Vector3<double>   vec3d;
    typedef Vector3<int8_t>   vec3i8;
    typedef Vector3<int16_t>  vec3i16;
    typedef Vector3<int32_t>  vec3i32;
    typedef Vector3<int64_t>  vec3i64;
    typedef Vector3<uint8_t>  vec3ui8;
    typedef Vector3<uint16_t> vec3ui16;
    typedef Vector3<uint32_t> vec3ui32;
    typedef Vector3<uint64_t> vec3ui64;
    
    typedef Vector4<float>    vec4f;
    typedef Vector4<double>   vec4d;
    typedef Vector4<int8_t>   vec4i8;
    typedef Vector4<int16_t>  vec4i16;
    typedef Vector4<int32_t>  vec4i32;
    typedef Vector4<int64_t>  vec4i64;
    typedef Vector4<uint8_t>  vec4ui8;
    typedef Vector4<uint16_t> vec4ui16;
    typedef Vector4<uint32_t> vec4ui32;
    typedef Vector4<uint64_t> vec4ui64;
    
} }

#endif
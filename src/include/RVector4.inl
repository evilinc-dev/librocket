#include "RMatrix.h"
#include "RVector4.h"

namespace rocket
{

inline const RVector4 RVector4::operator+(const RVector4& v) const
{
    RVector4 result(*this);
    result.add(v);
    return result;
}

inline RVector4& RVector4::operator+=(const RVector4& v)
{
    add(v);
    return *this;
}

inline const RVector4 RVector4::operator-(const RVector4& v) const
{
    RVector4 result(*this);
    result.subtract(v);
    return result;
}

inline RVector4& RVector4::operator-=(const RVector4& v)
{
    subtract(v);
    return *this;
}

inline const RVector4 RVector4::operator-() const
{
    RVector4 result(*this);
    result.negate();
    return result;
}

inline const RVector4 RVector4::operator*(float x) const
{
    RVector4 result(*this);
    result.scale(x);
    return result;
}

inline RVector4& RVector4::operator*=(float x)
{
    scale(x);
    return *this;
}

inline const RVector4 RVector4::operator/(const float x) const
{
    return RVector4(this->x / x, this->y / x, this->z / x, this->w / x);
}

inline bool RVector4::operator<(const RVector4& v) const
{
    if (x == v.x)
    {
        if (y == v.y)
        {
            if (z == v.z)
            {
                return w < v.w;
            }
            return z < v.z;
        }
        return y < v.y;
    }
    return x < v.x;
}

inline bool RVector4::operator==(const RVector4& v) const
{
    return x==v.x && y==v.y && z==v.z && w==v.w;
}

inline bool RVector4::operator!=(const RVector4& v) const
{
    return x!=v.x || y!=v.y || z!=v.z || w!=v.w;
}

inline const RVector4 operator*(float x, const RVector4& v)
{
    RVector4 result(v);
    result.scale(x);
    return result;
}

}

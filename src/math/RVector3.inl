#include "RVector3.h"
#include "RMatrix.h"

namespace rocket
{

inline const RVector3 RVector3::operator+(const RVector3& v) const
{
    RVector3 result(*this);
    result.add(v);
    return result;
}

inline RVector3& RVector3::operator+=(const RVector3& v)
{
    add(v);
    return *this;
}

inline const RVector3 RVector3::operator-(const RVector3& v) const
{
    RVector3 result(*this);
    result.subtract(v);
    return result;
}

inline RVector3& RVector3::operator-=(const RVector3& v)
{
    subtract(v);
    return *this;
}

inline const RVector3 RVector3::operator-() const
{
    RVector3 result(*this);
    result.negate();
    return result;
}

inline const RVector3 RVector3::operator*(float x) const
{
    RVector3 result(*this);
    result.scale(x);
    return result;
}

inline RVector3& RVector3::operator*=(float x)
{
    scale(x);
    return *this;
}

inline const RVector3 RVector3::operator/(const float x) const
{
    return RVector3(this->x / x, this->y / x, this->z / x);
}

inline bool RVector3::operator<(const RVector3& v) const
{
    if (x == v.x)
    {
        if (y == v.y)
        {
            return z < v.z;
        }
        return y < v.y;
    }
    return x < v.x;
}

inline bool RVector3::operator==(const RVector3& v) const
{
    return x==v.x && y==v.y && z==v.z;
}

inline bool RVector3::operator!=(const RVector3& v) const
{
    return x!=v.x || y!=v.y || z!=v.z;
}

inline const RVector3 operator*(float x, const RVector3& v)
{
    RVector3 result(v);
    result.scale(x);
    return result;
}

}

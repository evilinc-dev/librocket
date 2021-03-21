#include "RVector2.h"

namespace rocket
{

inline const RVector2 RVector2::operator+(const RVector2& v) const
{
    RVector2 result(*this);
    result.add(v);
    return result;
}

inline RVector2& RVector2::operator+=(const RVector2& v)
{
    add(v);
    return *this;
}

inline const RVector2 RVector2::operator-(const RVector2& v) const
{
    RVector2 result(*this);
    result.subtract(v);
    return result;
}

inline RVector2& RVector2::operator-=(const RVector2& v)
{
    subtract(v);
    return *this;
}

inline const RVector2 RVector2::operator-() const
{
    RVector2 result(*this);
    result.negate();
    return result;
}

inline const RVector2 RVector2::operator*(float x) const
{
    RVector2 result(*this);
    result.scale(x);
    return result;
}

inline RVector2& RVector2::operator*=(float x)
{
    scale(x);
    return *this;
}

inline const RVector2 RVector2::operator/(const float x) const
{
    return RVector2(this->x / x, this->y / x);
}

inline bool RVector2::operator<(const RVector2& v) const
{
    if (x == v.x)
    {
        return y < v.y;
    }
    return x < v.x;
}

inline bool RVector2::operator==(const RVector2& v) const
{
    return x==v.x && y==v.y;
}

inline bool RVector2::operator!=(const RVector2& v) const
{
    return x!=v.x || y!=v.y;
}

inline const RVector2 operator*(float x, const RVector2& v)
{
    RVector2 result(v);
    result.scale(x);
    return result;
}

}

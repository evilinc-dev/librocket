#include "RMatrix.h"

namespace rocket
{

inline const RMatrix RMatrix::operator+(const RMatrix& m) const
{
    RMatrix result(*this);
    result.add(m);
    return result;
}

inline RMatrix& RMatrix::operator+=(const RMatrix& m)
{
    add(m);
    return *this;
}

inline const RMatrix RMatrix::operator-(const RMatrix& m) const
{
    RMatrix result(*this);
    result.subtract(m);
    return result;
}

inline RMatrix& RMatrix::operator-=(const RMatrix& m)
{
    subtract(m);
    return *this;
}

inline const RMatrix RMatrix::operator-() const
{
    RMatrix m(*this);
    m.negate();
    return m;
}

inline const RMatrix RMatrix::operator*(const RMatrix& m) const
{
    RMatrix result(*this);
    result.multiply(m);
    return result;
}

inline RMatrix& RMatrix::operator*=(const RMatrix& m)
{
    multiply(m);
    return *this;
}

inline RVector3& operator*=(RVector3& v, const RMatrix& m)
{
    m.transformVector(&v);
    return v;
}

inline const RVector3 operator*(const RMatrix& m, const RVector3& v)
{
    RVector3 x;
    m.transformVector(v, &x);
    return x;
}

inline RVector4& operator*=(RVector4& v, const RMatrix& m)
{
    m.transformVector(&v);
    return v;
}

inline const RVector4 operator*(const RMatrix& m, const RVector4& v)
{
    RVector4 x;
    m.transformVector(v, &x);
    return x;
}

}

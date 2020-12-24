#include "RQuaternion.h"

namespace rocket
{

inline const RQuaternion RQuaternion::operator*(const RQuaternion& q) const
{
    RQuaternion result(*this);
    result.multiply(q);
    return result;
}

inline RQuaternion& RQuaternion::operator*=(const RQuaternion& q)
{
    multiply(q);
    return *this;
}

}

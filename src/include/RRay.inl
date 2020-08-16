#include "common.h"
#include "RRay.h"

namespace rocket
{

API inline RRay& RRay::operator*=(const RMatrix& matrix)
{
    transform(matrix);
    return *this;
}

API inline const RRay operator*(const RMatrix& matrix, const RRay& ray)
{
    RRay r(ray);
    r.transform(matrix);
    return r;
}

}
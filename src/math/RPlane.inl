#include "common.h"
#include "RPlane.h"

namespace rocket
{

API inline RPlane& RPlane::operator*=(const RMatrix& matrix)
{
    transform(matrix);
    return *this;
}

API inline const RPlane operator*(const RMatrix& matrix, const RPlane& plane)
{
    RPlane p(plane);
    p.transform(matrix);
    return p;
}

}
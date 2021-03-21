#include "common.h"
#include "RBoundingSphere.h"

namespace rocket
{

API inline RBoundingSphere& RBoundingSphere::operator*=(const RMatrix& matrix)
{
    transform(matrix);
    return *this;
}

API inline const RBoundingSphere operator*(const RMatrix& matrix, const RBoundingSphere& sphere)
{
    RBoundingSphere s(sphere);
    s.transform(matrix);
    return s;
}

}
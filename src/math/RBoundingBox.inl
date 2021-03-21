#include "common.h"
#include "RBoundingBox.h"

namespace rocket
{

API inline RBoundingBox& RBoundingBox::operator*=(const RMatrix& matrix)
{
    transform(matrix);
    return *this;
}

API inline const RBoundingBox operator*(const RMatrix& matrix, const RBoundingBox& box)
{
    RBoundingBox b(box);
    b.transform(matrix);
    return b;
}

}
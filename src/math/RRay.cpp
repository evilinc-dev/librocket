#include "common.h"
#include "RRay.h"
#include "RPlane.h"
#include "RFrustum.h"
#include "RBoundingSphere.h"
#include "RBoundingBox.h"


namespace rocket
{

RRay::RRay()
    : _direction(0, 0, 1)
{
}

RRay::RRay(const RVector3& origin, const RVector3& direction)
{
    set(origin, direction);
}

RRay::RRay(float originX, float originY, float originZ, float dirX, float dirY, float dirZ)
{
    set(RVector3(originX, originY, originZ), RVector3(dirX, dirY, dirZ));
}

RRay::RRay(const RRay& copy)
{
    set(copy);
}

RRay::~RRay()
{
}

const RVector3& RRay::getOrigin() const
{
    return _origin;
}

void RRay::setOrigin(const RVector3& origin)
{
    _origin = origin;
}

void RRay::setOrigin(float x, float y, float z)
{
    _origin.set(x, y, z);
}

const RVector3& RRay::getDirection() const
{
    return _direction;
}

void RRay::setDirection(const RVector3& direction)
{
    _direction = direction;
    normalize();
}

void RRay::setDirection(float x, float y, float z)
{
    _direction.set(x, y, z);
    normalize();
}

float RRay::intersects(const RBoundingSphere& sphere) const
{
    return sphere.intersects(*this);
}

float RRay::intersects(const RBoundingBox& box) const
{
    return box.intersects(*this);
}

float RRay::intersects(const RFrustum& RFrustum) const
{
    RPlane n = RFrustum.getNear();
    float nD = intersects(n);
    float nOD = n.distance(_origin);

    RPlane f = RFrustum.getFar();
    float fD = intersects(f);
    float fOD = f.distance(_origin);

    RPlane l = RFrustum.getLeft();
    float lD = intersects(l);
    float lOD = l.distance(_origin);

    RPlane r = RFrustum.getRight();
    float rD = intersects(r);
    float rOD = r.distance(_origin);

    RPlane b = RFrustum.getBottom();
    float bD = intersects(b);
    float bOD = b.distance(_origin);

    RPlane t = RFrustum.getTop();
    float tD = intersects(t);
    float tOD = t.distance(_origin);

    // If the ray's origin is in the negative half-space of one of the RFrustum's planes
    // and it does not intersect that same plane, then it does not intersect the RFrustum.
    if ((nOD < 0.0f && nD < 0.0f) || (fOD < 0.0f && fD < 0.0f) ||
        (lOD < 0.0f && lD < 0.0f)  || (rOD < 0.0f && rD < 0.0f) ||
        (bOD < 0.0f && bD < 0.0f)  || (tOD < 0.0f && tD < 0.0f))
    {
        return RRay::INTERSECTS_NONE;
    }

    // Otherwise, the intersection distance is the minimum positive intersection distance.
    float d = (nD > 0.0f) ? nD : 0.0f;
    d = (fD > 0.0f) ? ((d == 0.0f) ? fD : std::min(fD, d)) : d;
    d = (lD > 0.0f) ? ((d == 0.0f) ? lD : std::min(lD, d)) : d;
    d = (rD > 0.0f) ? ((d == 0.0f) ? rD : std::min(rD, d)) : d;
    d = (tD > 0.0f) ? ((d == 0.0f) ? bD : std::min(bD, d)) : d;
    d = (bD > 0.0f) ? ((d == 0.0f) ? tD : std::min(tD, d)) : d;

    return d;
}

float RRay::intersects(const RPlane& plane) const
{
    const RVector3& normal = plane.getNormal();
    // If the origin of the ray is on the plane then the distance is zero.
    float alpha = (normal.dot(_origin) + plane.getDistance());
    if (fabs(alpha) < MATH_EPSILON)
    {
        return 0.0f;
    }

    float dot = normal.dot(_direction);
    
    // If the dot product of the plane's normal and this ray's direction is zero,
    // then the ray is parallel to the plane and does not intersect it.
    if (dot == 0.0f)
    {
        return INTERSECTS_NONE;
    }
    
    // Calculate the distance along the ray's direction vector to the point where
    // the ray intersects the plane (if it is negative the plane is behind the ray).
    float d = -alpha / dot;
    if (d < 0.0f)
    {
        return INTERSECTS_NONE;
    }
    return d;
}

void RRay::set(const RVector3& origin, const RVector3& direction)
{
    _origin = origin;
    _direction = direction;
    normalize();
}

void RRay::set(const RRay& ray)
{
    _origin = ray._origin;
    _direction = ray._direction;
    normalize();
}

void RRay::transform(const RMatrix& matrix)
{
    matrix.transformPoint(&_origin);
    matrix.transformVector(&_direction);
    _direction.normalize();
}

void RRay::normalize()
{
    if (_direction.isZero())
    {
        throw ("Invalid ray object; a ray's direction must be non-zero.");
        return;
    }

    // Normalize the ray's direction vector.
    float normalizeFactor = 1.0f / sqrt(_direction.x * _direction.x + _direction.y * _direction.y + _direction.z * _direction.z);
    if (normalizeFactor != 1.0f)
    {
        _direction.x *= normalizeFactor;
        _direction.y *= normalizeFactor;
        _direction.z *= normalizeFactor;
    }
}


}
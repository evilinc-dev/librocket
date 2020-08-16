#include <common.h>
#include <RPlane.h>
#include <RFrustum.h>
#include <RRay.h>
#include <RBoundingSphere.h>
#include <RBoundingBox.h>

namespace rocket
{

API RPlane::RPlane()
    : _normal(0, 1, 0), _distance(0)
{
}

API RPlane::RPlane(const RVector3& normal, float distance)
{
    set(normal, distance);
}

API RPlane::RPlane(float normalX, float normalY, float normalZ, float distance)
{
    set(RVector3(normalX, normalY, normalZ), distance);
}

API RPlane::RPlane(const RPlane& copy)
{
    set(copy);
}

API RPlane::~RPlane()
{
}

API const RVector3& RPlane::getNormal() const
{
    return _normal;
}

API void RPlane::setNormal(const RVector3& normal)
{
    _normal = normal;
    normalize();
}

API void RPlane::setNormal(float x, float y, float z)
{
    _normal.set(x, y, z);
    normalize();
}

API float RPlane::getDistance() const
{
    return _distance;
}

API void RPlane::setDistance(float distance)
{
    _distance = distance;
}

API float RPlane::distance(const RVector3& point) const
{
    return _normal.x * point.x + _normal.y * point.y + _normal.z * point.z + _distance;
}

API void RPlane::intersection(const RPlane& p1, const RPlane& p2, const RPlane& p3, Vector3* point)
{
    // The planes' normals must be all normalized (which we guarantee in the RPlane class).
    // Calculate the determinant of the matrix (i.e | n1 n2 n3 |).
    float det = p1._normal.x * (p2._normal.y * p3._normal.z -
                p2._normal.z * p3._normal.y) - p2._normal.x *(p1._normal.y * p3._normal.z -
                p1._normal.z * p3._normal.y) + p3._normal.x * (p1._normal.y * p2._normal.z - p1._normal.z * p2._normal.y);

    // If the determinant is zero, then the planes do not all intersect.
    if (fabs(det) <= MATH_EPSILON)
        return;

    // Create 3 points, one on each plane.
    // (We just pick the point on the plane directly along its normal from the origin).
    float p1x = -p1._normal.x * p1._distance;
    float p1y = -p1._normal.y * p1._distance;
    float p1z = -p1._normal.z * p1._distance;
    float p2x = -p2._normal.x * p2._distance;
    float p2y = -p2._normal.y * p2._distance;
    float p2z = -p2._normal.z * p2._distance;
    float p3x = -p3._normal.x * p3._distance;
    float p3y = -p3._normal.y * p3._distance;
    float p3z = -p3._normal.z * p3._distance;

    // Calculate the cross products of the normals.
    float c1x = (p2._normal.y * p3._normal.z) - (p2._normal.z * p3._normal.y);
    float c1y = (p2._normal.z * p3._normal.x) - (p2._normal.x * p3._normal.z);
    float c1z = (p2._normal.x * p3._normal.y) - (p2._normal.y * p3._normal.x);
    float c2x = (p3._normal.y * p1._normal.z) - (p3._normal.z * p1._normal.y);
    float c2y = (p3._normal.z * p1._normal.x) - (p3._normal.x * p1._normal.z);
    float c2z = (p3._normal.x * p1._normal.y) - (p3._normal.y * p1._normal.x);
    float c3x = (p1._normal.y * p2._normal.z) - (p1._normal.z * p2._normal.y);
    float c3y = (p1._normal.z * p2._normal.x) - (p1._normal.x * p2._normal.z);
    float c3z = (p1._normal.x * p2._normal.y) - (p1._normal.y * p2._normal.x);

    // Calculate the point of intersection using the formula:
    // x = (| n1 n2 n3 |)^-1 * [(x1 * n1)(n2 x n3) + (x2 * n2)(n3 x n1) + (x3 * n3)(n1 x n2)]
    float s1 = p1x * p1._normal.x + p1y * p1._normal.y + p1z * p1._normal.z;
    float s2 = p2x * p2._normal.x + p2y * p2._normal.y + p2z * p2._normal.z;
    float s3 = p3x * p3._normal.x + p3y * p3._normal.y + p3z * p3._normal.z;
    float detI = 1.0f / det;
    point->x = (s1 * c1x + s2 * c2x + s3 * c3x) * detI;
    point->y = (s1 * c1y + s2 * c2y + s3 * c3y) * detI;
    point->z = (s1 * c1z + s2 * c2z + s3 * c3z) * detI;
}

API float RPlane::intersects(const RBoundingSphere& sphere) const
{
    return sphere.intersects(*this);
}

API float RPlane::intersects(const RBoundingBox& box) const
{
    return box.intersects(*this);
}

API float RPlane::intersects(const RFrustum& RFrustum) const
{
    // Get the corners of the RFrustum.
    RVector3 corners[8];
    RFrustum.getCorners(corners);

    // Calculate the distances from all of the corners to the plane.
    // If all of the distances are positive, then the RFrustum is in the
    // positive half-space of this plane; if all the distances are negative,
    // then the RFrustum is in the negative half-space of this plane; if some of
    // the distances are positive and some are negative, the RFrustum intersects.
    float d = distance(corners[0]);
    if (d > 0.0f)
    {
        if (distance(corners[1]) <= 0.0f ||
            distance(corners[2]) <= 0.0f ||
            distance(corners[3]) <= 0.0f ||
            distance(corners[4]) <= 0.0f ||
            distance(corners[5]) <= 0.0f ||
            distance(corners[6]) <= 0.0f ||
            distance(corners[7]) <= 0.0f)
        {
            return RPlane::INTERSECTS_INTERSECTING;
        }

        return RPlane::INTERSECTS_FRONT;
    }
    else if (d < 0.0f)
    {
        if (distance(corners[1]) >= 0.0f ||
            distance(corners[2]) >= 0.0f ||
            distance(corners[3]) >= 0.0f ||
            distance(corners[4]) >= 0.0f ||
            distance(corners[5]) >= 0.0f ||
            distance(corners[6]) >= 0.0f ||
            distance(corners[7]) >= 0.0f)
        {
            return RPlane::INTERSECTS_INTERSECTING;
        }

        return RPlane::INTERSECTS_BACK;
    }
    else
    {
        return RPlane::INTERSECTS_INTERSECTING;
    }
}

API float RPlane::intersects(const RPlane& plane) const
{
    // Check if the planes intersect.
    if ((_normal.x == plane._normal.x && _normal.y == plane._normal.y && _normal.z == plane._normal.z) || !isParallel(plane))
    {
        return RPlane::INTERSECTS_INTERSECTING;
    }

    // Calculate the point where the given plane's normal vector intersects the given plane.
    RVector3 point(plane._normal.x * -plane._distance, plane._normal.y * -plane._distance, plane._normal.z * -plane._distance);

    // Calculate whether the given plane is in the positive or negative half-space of this plane
    // (corresponds directly to the sign of the distance from the point calculated above to this plane).
    if (distance(point) > 0.0f)
    {
        return RPlane::INTERSECTS_FRONT;
    }
    else
    {
        return RPlane::INTERSECTS_BACK;
    }
}

API float RPlane::intersects(const RRay& ray) const
{
    // Calculate the distance from the ray's origin to the plane.
    float d = distance(ray.getOrigin());

    // If the origin of the ray lies in the plane, then it intersects.
    if (d == 0.0f)
    {
        return RPlane::INTERSECTS_INTERSECTING;
    }
    else
    {
        RVector3 rayDirection = ray.getDirection();
        // If the dot product of this plane's normal and the ray's direction is positive, and
        // if the distance from this plane to the ray's origin is negative -> intersection, OR
        // if the dot product of this plane's normal and the ray's direction is negative, and
        // if the distance from this plane to the ray's origin is positive -> intersection.
        if (_normal.x * rayDirection.x + _normal.y * rayDirection.y + _normal.z * rayDirection.z > 0.0f)
        {
            if (d < 0.0f)
            {
                return RPlane::INTERSECTS_INTERSECTING;
            }
            else
            {
                return RPlane::INTERSECTS_FRONT;
            }
        }
        else
        {
            if (d > 0.0f)
            {
                return RPlane::INTERSECTS_INTERSECTING;
            }
            else
            {
                return RPlane::INTERSECTS_BACK;
            }
        }
    }
}

API bool RPlane::isParallel(const RPlane& plane) const
{
    return (_normal.y * plane._normal.z) - (_normal.z * plane._normal.y) == 0.0f &&
           (_normal.z * plane._normal.x) - (_normal.x * plane._normal.z) == 0.0f &&
           (_normal.x * plane._normal.y) - (_normal.y * plane._normal.x) == 0.0f;
}

API void RPlane::set(const RVector3& normal, float distance)
{
    _normal = normal;
    _distance = distance;
    normalize();
}

API void RPlane::set(const RPlane& plane)
{
    _normal = plane._normal;
    _distance = plane._distance;
}

API void RPlane::transform(const RMatrix& matrix)
{
    RMatrix inverted;
    if (matrix.invert(&inverted))
    {
        // Treat the plane as a four-tuple and multiply by the inverse transpose of the matrix to get the transformed plane.
        // Then we normalize the plane by dividing both the normal and the distance by the length of the normal.
        float nx = _normal.x * inverted.m[0] + _normal.y * inverted.m[1] + _normal.z * inverted.m[2] + _distance * inverted.m[3];
        float ny = _normal.x * inverted.m[4] + _normal.y * inverted.m[5] + _normal.z * inverted.m[6] + _distance * inverted.m[7];
        float nz = _normal.x * inverted.m[8] + _normal.y * inverted.m[9] + _normal.z * inverted.m[10] + _distance * inverted.m[11];
        float d = _normal.x * inverted.m[12]+ _normal.y * inverted.m[13] + _normal.z * inverted.m[14] + _distance * inverted.m[15];
        float divisor = sqrt(nx * nx + ny * ny + nz * nz);
        float factor = 1.0f / divisor;

        _normal.x = nx * factor;
        _normal.y = ny * factor;
        _normal.z = nz * factor;
        _distance = d * factor;
    }
}

API void RPlane::normalize()
{
    if (_normal.isZero())
        return;

    // Normalize the plane's normal.
    float normalizeFactor = 1.0f / sqrt(_normal.x * _normal.x + _normal.y * _normal.y + _normal.z * _normal.z);

    if (normalizeFactor != 1.0f)
    {
        _normal.x *= normalizeFactor;
        _normal.y *= normalizeFactor;
        _normal.z *= normalizeFactor;
        _distance *= normalizeFactor;
    }
}

}
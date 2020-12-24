#include <common.h>
#include <RBoundingBox.h>
#include <RBoundingSphere.h>
#include <RPlane.h>

namespace rocket
{

API RBoundingBox::RBoundingBox()
{
}

API RBoundingBox::RBoundingBox(const RVector3& min, const RVector3& max)
{
    set(min, max);
}

API RBoundingBox::RBoundingBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
{
    set(minX, minY, minZ, maxX, maxY, maxZ);
}

API RBoundingBox::RBoundingBox(const RBoundingBox& copy)
{
    set(copy);
}

API RBoundingBox::~RBoundingBox()
{
}

API const RBoundingBox& RBoundingBox::empty()
{
    static RBoundingBox b;
    return b;
}

API void RBoundingBox::getCorners(RVector3* dst) const
{
    // Near face, specified counter-clockwise looking towards the origin from the positive z-axis.
    // Left-top-front.
    dst[0] = RVector3(min.x, max.y, max.z);
    // Left-bottom-front.
    dst[1] = RVector3(min.x, min.y, max.z);
    // Right-bottom-front.
    dst[2] = RVector3(max.x, min.y, max.z);
    // Right-top-front.
    dst[3] = RVector3(max.x, max.y, max.z);

    // Far face, specified counter-clockwise looking towards the origin from the negative z-axis.
    // Right-top-back.
    dst[4] = RVector3(max.x, max.y, min.z);
    // Right-bottom-back.
    dst[5] = RVector3(max.x, min.y, min.z);
    // Left-bottom-back.
    dst[6] = RVector3(min.x, min.y, min.z);
    // Left-top-back.
    dst[7] = RVector3(min.x, max.y, min.z);
}

API RVector3 RBoundingBox::getCenter() const
{
    RVector3 center;
    getCenter(&center);
    return center;
}

API void RBoundingBox::getCenter(RVector3* dst) const
{
    RVector3 l = (max - min) * 0.5f;
    RVector3 center = (l + min);
    dst->x = center.x;
    dst->y = center.y;
    dst->z = center.z;
}

API bool RBoundingBox::intersects(const RBoundingSphere& sphere) const
{
    return sphere.intersects(*this);
}

API bool RBoundingBox::intersects(const RBoundingBox& box) const
{
    return ((min.x >= box.min.x && min.x <= box.max.x) || (box.min.x >= min.x && box.min.x <= max.x)) &&
            ((min.y >= box.min.y && min.y <= box.max.y) || (box.min.y >= min.y && box.min.y <= max.y)) &&
            ((min.z >= box.min.z && min.z <= box.max.z) || (box.min.z >= min.z && box.min.z <= max.z));
}

API bool RBoundingBox::intersects(const RFrustum& RFrustum) const
{
    // The box must either intersect or be in the positive half-space of all six planes of the RFrustum.
    return (intersects(RFrustum.getNear()) != RPlane::INTERSECTS_BACK &&
            intersects(RFrustum.getFar()) != RPlane::INTERSECTS_BACK &&
            intersects(RFrustum.getLeft()) != RPlane::INTERSECTS_BACK &&
            intersects(RFrustum.getRight()) != RPlane::INTERSECTS_BACK &&
            intersects(RFrustum.getBottom()) != RPlane::INTERSECTS_BACK &&
            intersects(RFrustum.getTop()) != RPlane::INTERSECTS_BACK);
}

API float RBoundingBox::intersects(const RPlane& plane) const
{
    // Calculate the distance from the center of the box to the plane.
    RVector3 center((min.x + max.x) * 0.5f, (min.y + max.y) * 0.5f, (min.z + max.z) * 0.5f);
    float distance = plane.distance(center);

    // Get the extents of the box from its center along each axis.
    float extentX = (max.x - min.x) * 0.5f;
    float extentY = (max.y - min.y) * 0.5f;
    float extentZ = (max.z - min.z) * 0.5f;

    const RVector3& planeNormal = plane.getNormal();
    if (fabsf(distance) <= (fabsf(extentX * planeNormal.x) + fabsf(extentY * planeNormal.y) + fabsf(
        extentZ * planeNormal.z)))
    {
        return RPlane::INTERSECTS_INTERSECTING;
    }

    return (distance > 0.0f) ? (float)RPlane::INTERSECTS_FRONT : (float)RPlane::INTERSECTS_BACK;
}

API float RBoundingBox::intersects(const RRay& ray) const
{
    // Intermediate calculation variables.
    float dnear = 0.0f;
    float dfar = 0.0f;
    float tmin = 0.0f;
    float tmax = 0.0f;

    const RVector3& origin = ray.getOrigin();
    const RVector3& direction = ray.getDirection();

    // X direction.
    float div = 1.0f / direction.x;
    if (div >= 0.0f)
    {
        tmin = (min.x - origin.x) * div;
        tmax = (max.x - origin.x) * div;
    }
    else
    {
        tmin = (max.x - origin.x) * div;
        tmax = (min.x - origin.x) * div;
    }
    dnear = tmin;
    dfar = tmax;

    // Check if the ray misses the box.
    if (dnear > dfar || dfar < 0.0f)
    {
        return RRay::INTERSECTS_NONE;
    }

    // Y direction.
    div = 1.0f / direction.y;
    if (div >= 0.0f)
    {
        tmin = (min.y - origin.y) * div;
        tmax = (max.y - origin.y) * div;
    }
    else
    {
        tmin = (max.y - origin.y) * div;
        tmax = (min.y - origin.y) * div;
    }

    // Update the near and far intersection distances.
    if (tmin > dnear)
    {
        dnear = tmin;
    }
    if (tmax < dfar)
    {
        dfar = tmax;
    }
    // Check if the ray misses the box.
    if (dnear > dfar || dfar < 0.0f)
    {
        return RRay::INTERSECTS_NONE;
    }

    // Z direction.
    div = 1.0f / direction.z;
    if (div >= 0.0f)
    {
        tmin = (min.z - origin.z) * div;
        tmax = (max.z - origin.z) * div;
    }
    else
    {
        tmin = (max.z - origin.z) * div;
        tmax = (min.z - origin.z) * div;
    }

    // Update the near and far intersection distances.
    if (tmin > dnear)
    {
        dnear = tmin;
    }
    if (tmax < dfar)
    {
        dfar = tmax;
    }

    // Check if the ray misses the box.
    if (dnear > dfar || dfar < 0.0f)
    {
        return RRay::INTERSECTS_NONE;
    }
    // The ray intersects the box (and since the direction of a RRay is normalized, dnear is the distance to the ray).
    return dnear;
}

API bool RBoundingBox::isEmpty() const
{
    return min.x == max.x && min.y == max.y && min.z == max.z;
}

API void RBoundingBox::merge(const RBoundingBox& box)
{
    // Calculate the new minimum point.
    min.x = std::min(min.x, box.min.x);
    min.y = std::min(min.y, box.min.y);
    min.z = std::min(min.z, box.min.z);

    // Calculate the new maximum point.
    max.x = std::max(max.x, box.max.x);
    max.y = std::max(max.y, box.max.y);
    max.z = std::max(max.z, box.max.z);
}

API void RBoundingBox::merge(const RBoundingSphere& sphere)
{
    const RVector3& center = sphere.center;
    float radius = sphere.radius;

    // Calculate the new minimum point for the merged bounding box.
    min.x = std::min(min.x, center.x - radius);
    min.y = std::min(min.y, center.y - radius);
    min.z = std::min(min.z, center.z - radius);

    // Calculate the new maximum point for the merged bounding box.
    max.x = std::max(max.x, center.x + radius);
    max.y = std::max(max.y, center.y + radius);
    max.z = std::max(max.z, center.z + radius);
}

API void RBoundingBox::set(const RVector3& min, const RVector3& max)
{
    this->min = min;
    this->max = max;
}

API void RBoundingBox::set(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
{
    min = RVector3(minX, minY, minZ);
    max = RVector3(maxX, maxY, maxZ);
}

static void updateMinMax(RVector3* point, RVector3* min, RVector3* max)
{

    // Leftmost point.
    if (point->x < min->x)
    {
        min->x = point->x;
    }

    // Rightmost point.
    if (point->x > max->x)
    {
        max->x = point->x;
    }

    // Lowest point.
    if (point->y < min->y)
    {
        min->y = point->y;
    }

    // Highest point.
    if (point->y > max->y)
    {
        max->y = point->y;
    }

    // Farthest point.
    if (point->z < min->z)
    {
        min->z = point->z;
    }

    // Nearest point.
    if (point->z > max->z)
    {
        max->z = point->z;
    }
}

API void RBoundingBox::set(const RBoundingBox& box)
{
    min = box.min;
    max = box.max;
}

API void RBoundingBox::set(const RBoundingSphere& sphere)
{
    const RVector3& center = sphere.center;
    float radius = sphere.radius;

    // Calculate the minimum point for the box.
    min.x = center.x - radius;
    min.y = center.y - radius;
    min.z = center.z - radius;

    // Calculate the maximum point for the box.
    max.x = center.x + radius;
    max.y = center.y + radius;
    max.z = center.z + radius;
}

API void RBoundingBox::transform(const RMatrix& matrix)
{
    // Calculate the corners.
    RVector3 corners[8];
    getCorners(corners);

    // Transform the corners, recalculating the min and max points along the way.
    RVector4 corner = (matrix* RVector4(corners[0].x, corners[0].y, corners[0].z, 1.0f));
    RVector3 c = RVector3(corner.x, corner.y, corner.z);
    corners[0] = c;
    RVector3 newMin = corners[0];
    RVector3 newMax = corners[0];
    for (int i = 1; i < 8; i++)
    {
        corners[i] = c;
        updateMinMax(&corners[i], &newMin, &newMax);
    }
    this->min.x = newMin.x;
    this->min.y = newMin.y;
    this->min.z = newMin.z;
    this->max.x = newMax.x;
    this->max.y = newMax.y;
    this->max.z = newMax.z;
}

}
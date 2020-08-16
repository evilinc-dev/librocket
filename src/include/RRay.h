#pragma once

#include "common.h"

namespace rocket
{

class RFrustum;
class RPlane;
class RBoundingSphere;
class RBoundingBox;


/**
 * Defines a 3-dimensional ray.
 *
 * Rays direction vector are always normalized.
 */
class API RRay
{
public:

    /**
     * Represents when a 3D entity does not intersect a ray.
     */
    static const int INTERSECTS_NONE = -1;

    /**
     * Constructs a new ray initialized to origin(0,0,0) and direction(0,0,1).
     */
    RRay();

    /**
     * Constructs a new ray initialized to the specified values.
     *
     * @param origin The ray's origin.
     * @param direction The ray's direction.
     */
    RRay(const RVector3& origin, const RVector3& direction);

    /**
     * Constructs a new ray initialized to the specified values.
     * 
     * @param originX The x coordinate of the origin.
     * @param originY The y coordinate of the origin.
     * @param originZ The z coordinate of the origin.
     * @param dirX The x coordinate of the direction.
     * @param dirY The y coordinate of the direction.
     * @param dirZ The z coordinate of the direction.
     */
    RRay(float originX, float originY, float originZ, float dirX, float dirY, float dirZ);

    /**
     * Constructs a new ray from the given ray.
     *
     * @param copy The ray to copy.
     */
    RRay(const RRay& copy);

    /**
     * Destructor.
     */
    ~RRay();

    /**
     * Gets the ray's origin.
     *
     * @return The ray's origin.
     */
    const RVector3& getOrigin() const;

    /**
     * Sets the ray's origin to the given point.
     *
     * @param origin The new origin.
     */
    void setOrigin(const RVector3& origin);

    /**
     * Sets the ray's origin.
     * 
     * @param x The x coordinate of the origin.
     * @param y The y coordinate of the origin.
     * @param z The z coordinate of the origin.
     */
    void setOrigin(float x, float y, float z);

    /**
     * Gets the ray's direction.
     *
     * @return The ray's direction.
     */
    const RVector3& getDirection() const;

    /**
     * Sets the ray's direction to the given vector.
     *
     * @param direction The new direction vector.
     */
    void setDirection(const RVector3& direction);

    /**
     * Sets the ray's direction.
     * 
     * @param x The x coordinate of the direction.
     * @param y The y coordinate of the direction.
     * @param z The z coordinate of the direction.
     */
    void setDirection(float x, float y, float z);

    /**
     * Tests whether this ray intersects the specified bounding sphere.
     *
     * @param sphere The bounding sphere to test intersection with.
     * 
     * @return The distance from the origin of this ray to the bounding object or
     *     INTERSECTS_NONE if this ray does not intersect the bounding object.
     */
    float intersects(const RBoundingSphere& sphere) const;

    /**
     * Tests whether this ray intersects the specified bounding box.
     *
     * @param box The bounding box to test intersection with.
     * 
     * @return The distance from the origin of this ray to the bounding object or
     *     INTERSECTS_NONE if this ray does not intersect the bounding object.
     */
    float intersects(const RBoundingBox& box) const;

    /**
     * Tests whether this ray intersects the specified RFrustum.
     *
     * @param RFrustum The RFrustum to test intersection with.
     * 
     * @return The distance from the origin of this ray to the RFrustum or
     *     INTERSECTS_NONE if this ray does not intersect the RFrustum.
     */
    float intersects(const RFrustum& RFrustum) const;

    /**
     * Tests whether this ray intersects the specified plane and returns the distance
     * from the origin of the ray to the plane.
     *
     * @param plane The plane to test intersection with.
     * 
     * @return The distance from the origin of this ray to the plane or
     *     INTERSECTS_NONE if this ray does not intersect the plane.
     */
    float intersects(const RPlane& plane) const;

    /**
     * Sets this ray to the specified values.
     *
     * @param origin The ray's origin.
     * @param direction The ray's direction.
     */
    void set(const RVector3& origin, const RVector3& direction);

    /**
     * Sets this ray to the given ray.
     *
     * @param ray The ray to copy.
     */
    void set(const RRay& ray);

    /**
     * Transforms this ray by the given transformation matrix.
     *
     * @param matrix The transformation matrix to transform by.
     */
    void transform(const RMatrix& matrix);

    /**
     * Transforms this ray by the given matrix.
     * 
     * @param matrix The matrix to transform by.
     * @return This ray, after the transformation occurs.
     */
    inline RRay& operator*=(const RMatrix& matrix);

private:

    /**
     * Normalizes the ray.
     */
    void normalize();

    RVector3 _origin;        // The ray origin position.
    RVector3 _direction;     // The ray direction vector.
};

/**
 * Transforms the given ray by the given matrix.
 * 
 * @param matrix The matrix to transform by.
 * @param ray The ray to transform.
 * @return The resulting transformed ray.
 */
API inline const RRay operator*(const RMatrix& matrix, const RRay& ray);

}

#include "RRay.inl"
#pragma once
#include "common.h"

namespace rocket
{

class RBoundingSphere;
class RBoundingBox;
class RFrustum;
class RRay;

/**
 * Defines a plane which is a flat surface with 2 sides.
 *
 * The plane is represented as a plane using a 3D vector normal and a
 * distance value (stored as a negative value).
 */
class API RPlane
{
public:

    /**
     * Represents when a 3D entity intersects a plane.
     */
    static const int INTERSECTS_INTERSECTING = 0;

    /**
     * Represents when a 3D entity is in front of (in the positive half-space of) a plane.
     */
    static const int INTERSECTS_FRONT = 1;

    /**
     * Represents when a 3D entity is behind (in the negative half-space of) a plane.
     */
    static const int INTERSECTS_BACK = -1;

    /**
     * Constructs a new plane with normal (0, 1, 0) and distance 0.
     */
    RPlane();

    /**
     * Constructs a new plane from the specified values.
     *
     * @param normal The normal vector of this plane.
     * @param distance The distance from this plane along its (unit) normal to the origin.
     */
    RPlane(const RVector3& normal, float distance);

    /**
     * Constructs a new plane from the specified values.
     * 
     * @param normalX The x coordinate of the normal.
     * @param normalY The y coordinate of the normal.
     * @param normalZ The z coordinate of the normal.
     * @param distance The distance from this plane along its (unit) normal to the origin.
     */
    RPlane(float normalX, float normalY, float normalZ, float distance);

    /**
     * Constructs a new plane from the given plane.
     *
     * @param copy The plane to copy.
     */
    RPlane(const RPlane& copy);

    /**
     * Destructor.
     */
    ~RPlane();

    /**
     * Gets the plane's normal in the given vector.
     *
     * @return normal The plane's normal.
     */
    const RVector3& getNormal() const;

    /**
     * Sets the plane's normal to the given vector.
     *
     * @param normal The new normal vector.
     */
    void setNormal(const RVector3& normal);

    /**
     * Sets the plane's normal.
     * 
     * @param x The x coordinate of the normal.
     * @param y The y coordinate of the normal.
     * @param z The z coordinate of the normal.
     */
    void setNormal(float x, float y, float z);

    /**
     * Gets the plane's distance to the origin along its normal.
     *
     * @return The plane's distance to the origin along its normal.
     */
    float getDistance() const;

    /**
     * Sets the plane's distance to the origin along its normal.
     *
     * @param distance The new distance.
     */
    void setDistance(float distance);

    /**
     * Calculates the distance from this plane to the specified point.
     *
     * @param point The point to calculate distance to.
     */
    float distance(const RVector3& point) const;

    /**
     * Calculates the point of intersection of the given three planes and stores it in the given point.
     *
     * @param p1 The first plane.
     * @param p2 The second plane.
     * @param p3 The third plane.
     * @param point The point to store the point of intersection in
     *  (this is left unmodified if the planes do not all intersect or if
     *  they are all parallel along one vector and intersect along a line).
     */
    static void intersection(const RPlane& p1, const RPlane& p2, const RPlane& p3, RVector3* point);

    /**
     * Tests whether this plane intersects the specified bounding sphere.
     *
     * @param sphere The bounding sphere to test intersection with.
     * 
     * @return RPlane::INTERSECTS_BACK if the specified bounding object is in the negative half-space of
     *  this plane, RPlane::INTERSECTS_FRONT if it is in the positive half-space of this plane,
     *  and RPlane::INTERSECTS_INTERSECTING if it intersects this plane.
     */
    float intersects(const RBoundingSphere& sphere) const;

    /**
     * Tests whether this plane intersects the specified bounding box.
     *
     * @param box The bounding box to test intersection with.
     * 
     * @return RPlane::INTERSECTS_BACK if the specified bounding object is in the negative half-space of
     *  this plane, RPlane::INTERSECTS_FRONT if it is in the positive half-space of this plane,
     *  and RPlane::INTERSECTS_INTERSECTING if it intersects this plane.
     */
    float intersects(const RBoundingBox& box) const;

    /**
     * Tests whether this plane intersects the specified RFrustum.
     *
     * @param RFrustum The RFrustum to test intersection with.
     * 
     * @return RPlane::INTERSECTS_BACK if the specified RFrustum is in the negative half-space of
     *  this plane, RPlane::INTERSECTS_FRONT if it is in the positive half-space of this plane,
     *  and RPlane::INTERSECTS_INTERSECTING if it intersects this plane.
     */
    float intersects(const RFrustum& RFrustum) const;

    /**
     * Tests whether this plane intersects the specified plane.
     *
     * @param plane The plane to test intersection with.
     * 
     * @return RPlane::INTERSECTS_BACK if the specified plane is in the negative half-space of
     *  this plane, RPlane::INTERSECTS_FRONT if it is in the positive half-space of this plane,
     *  and RPlane::INTERSECTS_INTERSECTING if it intersects this plane.
     */
    float intersects(const RPlane& plane) const;

    /**
     * Tests whether this plane intersects the specified ray.
     *
     * @param ray The ray to test intersection with.
     * 
     * @return RPlane::INTERSECTS_BACK if the specified ray is in the negative half-space of
     *  this plane, RPlane::INTERSECTS_FRONT if it is in the positive half-space of this plane,
     *  and RPlane::INTERSECTS_INTERSECTING if it intersects this plane.
     */
    float intersects(const RRay& ray) const;

    /**
     * Determines whether the given plane is parallel to this plane.
     * 
     * @param plane The plane to test.
     * 
     * @return true if the given plane is parallel to this plane; false otherwise.
     */
    bool isParallel(const RPlane& plane) const;

    /**
     * Sets this plane to the specified values.
     *
     * @param normal The normal vector of this plane.
     * @param distance The distance to this plane along its normal to the origin.
     */
    void set(const RVector3& normal, float distance);

    /**
     * Sets this plane to the given plane.
     *
     * @param plane The plane to copy.
     */
    void set(const RPlane& plane);

    /**
     * Transforms this plane by the given transformation matrix.
     *
     * @param matrix The transformation matrix to transform by.
     */
    void transform(const RMatrix& matrix);

    /**
     * Transforms this plane by the given matrix.
     * 
     * @param matrix The matrix to transform by.
     * @return This plane, after the transformation occurs.
     */
    inline RPlane& operator*=(const RMatrix& matrix);

private:

    /**
     * Normalizes this plane.
     */
    void normalize();

    RVector3 _normal;    // The normal vector of the RPlane.
    float _distance;    // The distance of the RPlane along its normal from the origin.
};

/**
 * Transforms the given plane by the given matrix.
 * 
 * @param matrix The matrix to transform by.
 * @param plane The plane to transform.
 * @return The resulting transformed plane.
 */
API inline const RPlane operator*(const RMatrix& matrix, const RPlane& plane);


}

#include "RPlane.inl"
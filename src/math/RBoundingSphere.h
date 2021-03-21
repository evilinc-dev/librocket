#pragma once
#include "common.h"
#include "RFrustum.h"

namespace rocket
{

/**
 * Defines a 3-dimensional bounding sphere.
 */
class API RBoundingSphere
{
public:

    /**
     * The center point.
     */
    RVector3 center;

    /**
     * The sphere radius.
     */
    float radius;

    /**
     *  Constructs a new bounding sphere initialized to all zeros.
     */
    RBoundingSphere();

    /**
     * Constructs a new bounding sphere initialized to the specified values.
     *
     * @param center The center of the sphere.
     * @param radius The radius of the sphere.
     */
    RBoundingSphere(const RVector3& center, float radius);

    /**
     * Constructs a bounding sphere from the given bounding sphere.
     *
     * @param copy The bounding sphere to copy.
     */
    RBoundingSphere(const RBoundingSphere& copy);

    /**
     * Destructor.
     */
    ~RBoundingSphere();

    /**
     * Returns an empty bounding sphere.
     */
    static const RBoundingSphere& empty();

    /**
     * Tests whether this bounding sphere intersects the specified bounding sphere.
     *
     * @param sphere The bounding sphere to test intersection with.
     * 
     * @return true if the specified bounding sphere intersects this bounding sphere; false otherwise.
     */
    bool intersects(const RBoundingSphere& sphere) const;

    /**
     * Tests whether this bounding sphere intersects the specified bounding box.
     *
     * @param box The bounding box to test intersection with.
     * 
     * @return true if the specified bounding box intersects this bounding sphere; false otherwise.
     */
    bool intersects(const RBoundingBox& box) const;

    /**
     * Tests whether this bounding sphere intersects the specified RFrustum.
     *
     * @param RFrustum The RFrustum to test intersection with.
     * 
     * @return true if this bounding sphere intersects the specified RFrustum; false otherwise.
     */
    bool intersects(const RFrustum& RFrustum) const;

    /**
     * Tests whether this bounding sphere intersects the specified plane.
     *
     * @param plane The plane to test intersection with.
     * 
     * @return RPlane::INTERSECTS_BACK INTERSECTS_BACK if this bounding sphere is in the negative half-space of
     *  the plane, RPlane::INTERSECTS_FRONT INTERSECTS_FRONT if it is in the positive half-space of the plane,
     *  and RPlane::INTERSECTS_INTERSECTING INTERSECTS_INTERSECTING if it intersects the plane.
     */
    float intersects(const RPlane& plane) const;

    /**
     * Tests whether this bounding sphere intersects the specified ray.
     *
     * @param ray The ray to test intersection with.
     * 
     * @return The distance from the origin of the ray to this bounding sphere or
     *  RRay::INTERSECTS_NONE INTERSECTS_NONE if the ray does not intersect this bounding sphere.
     */
    float intersects(const RRay& ray) const;

    /**
     * Determines if this bounding sphere is empty.
     *
     * @return true if this bounding sphere is empty; false otherwise.
     */
    bool isEmpty() const;

    /**
     * Sets this bounding sphere to the smallest bounding sphere
     * that contains both this bounding sphere and the specified bounding sphere.
     *
     * @param sphere The bounding sphere to merge with.
     */
    void merge(const RBoundingSphere& sphere);

    /**
     * Sets this bounding sphere to the smallest bounding sphere
     * that contains both this bounding sphere and the specified bounding box.
     *
     * @param box The bounding box to merge with.
     */
    void merge(const RBoundingBox& box);

    /**
     * Sets this bounding sphere to the specified values.
     *
     * @param center The center of the sphere.
     * @param radius The radius of the sphere.
     */
    void set(const RVector3& center, float radius);

    /**
     * Sets this bounding sphere to the specified bounding sphere.
     *
     * @param sphere The bounding sphere to set to.
     */
    void set(const RBoundingSphere& sphere);

    /**
     * Sets this bounding sphere to tightly contain the specified bounding box.
     *
     * @param box The box to contain.
     */
    void set(const RBoundingBox& box);

    /**
     * Transforms the bounding sphere by the given transformation matrix.
     *
     * @param matrix The transformation matrix to transform by.
     */
    void transform(const RMatrix& matrix);

    /**
     * Transforms this bounding sphere by the given matrix.
     * 
     * @param matrix The matrix to transform by.
     * @return This bounding sphere, after the transformation occurs.
     */
    inline RBoundingSphere& operator*=(const RMatrix& matrix);

private:

    float distance(const RBoundingSphere& sphere, const RVector3&);

    bool contains(const RBoundingSphere& sphere, RVector3* points, unsigned int count);
};

/**
 * Transforms the given bounding sphere by the given matrix.
 * 
 * @param matrix The matrix to transform by.
 * @param sphere The bounding sphere to transform.
 * @return The resulting transformed bounding sphere.
 */
API inline const RBoundingSphere operator*(const RMatrix& matrix, const RBoundingSphere& sphere);

}
#include "RBoundingSphere.inl"
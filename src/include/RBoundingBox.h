#pragma once

#include "common.h"
#include "RFrustum.h"

namespace rocket
{

/**
 * Defines a 3-dimensional axis-aligned bounding box.
 */
class API RBoundingBox
{
public:

    /**
     * The minimum point.
     */
    RVector3 min;

    /**
     * The maximum point.
     */
    RVector3 max;

    /**
     * Constructs an empty bounding box at the origin.
     */
    RBoundingBox();

    /**
     * Constructs a new bounding box from the specified values.
     *
     * @param min The minimum point of the bounding box.
     * @param max The maximum point of the bounding box.
     */
    RBoundingBox(const RVector3& min, const RVector3& max);

    /**
     * Constructs a new bounding box from the specified values.
     * 
     * @param minX The x coordinate of the minimum point of the bounding box.
     * @param minY The y coordinate of the minimum point of the bounding box.
     * @param minZ The z coordinate of the minimum point of the bounding box.
     * @param maxX The x coordinate of the maximum point of the bounding box.
     * @param maxY The y coordinate of the maximum point of the bounding box.
     * @param maxZ The z coordinate of the maximum point of the bounding box.
     */
    RBoundingBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);

    /**
     * Constructs a new bounding box from the given bounding box.
     *
     * @param copy The bounding box to copy.
     */
    RBoundingBox(const RBoundingBox& copy);

    /**
     * Destructor.
     */
    ~RBoundingBox();

    /**
     * Returns an empty bounding box.
     */
    static const RBoundingBox& empty();

    /**
     * Gets the center point of the bounding box.
     *
     * This method computes the center point of the box from its min and max.
     *
     * @return The center point of the bounding box.
     */
    RVector3 getCenter() const;

    /**
     * Gets the center point of the bounding box.
     *
     * This method computes the center point of the box from its min and max
     * points and stores the result in dst.
     *
     * @param dst The vector to store the result in.
     */
    void getCenter(RVector3* dst) const;

    /**
     * Gets the corners of the bounding box in the specified array.
     *
     * The corners are returned as follows: 0 to 3 specify the near face starting at the upper left point
     * when looking towards the origin from the positive z-axis in a counter-clockwise fashion; 4 to 7
     * specify the far face starting at the upper left point when looking towards the origin from the negative
     * z-axis in a counter-clockwise fashion.
     *
     * @param dst The array to store the corners in. Must be size 8.
     */
    void getCorners(RVector3* dst) const;

    /**
     * Tests whether this bounding box intersects the specified bounding object.
     *
     * @param box The bounding box to test intersection with.
     * 
     * @return true if the specified bounding box intersects this bounding box; false otherwise.
     */
    bool intersects(const RBoundingBox& box) const;

    /**
     * Tests whether this bounding box intersects the specified bounding sphere.
     *
     * @param sphere The bounding sphere to test intersection with.
     * 
     * @return true if the specified bounding sphere intersects this bounding box; false otherwise.
     */
    bool intersects(const RBoundingSphere& sphere) const;

    /**
     * Tests whether this bounding box intersects the specified RFrustum.
     *
     * @param RFrustum The RFrustum to test intersection with.
     * 
     * @return true if this bounding sphere intersects the specified RFrustum; false otherwise.
     */
    bool intersects(const RFrustum& RFrustum) const;

    /**
     * Tests whether this bounding box intersects the specified plane.
     *
     * @param plane The plane to test intersection with.
     * 
     * @return RPlane::INTERSECTS_BACK INTERSECTS_BACK if this bounding box is in the negative half-space of
     *  the plane, RPlane::INTERSECTS_FRONT INTERSECTS_FRONT if it is in the positive half-space of the plane;
     *  and RPlane::INTERSECTS_INTERSECTING INTERSECTS_INTERSECTING if it intersects the plane.
     */
    float intersects(const RPlane& plane) const;

    /**
     * Tests whether this bounding box intersects the specified ray.
     *
     * @param ray The ray to test intersection with.
     * 
     * @return The distance from the origin of the ray to this bounding box or
     *  INTERSECTS_NONE INTERSECTS_NONE if the ray does not intersect this bounding box.
     */
    float intersects(const RRay& ray) const;

    /**
     * Determines if this bounding box is empty.
     *
     * @return true if this bounding box is empty; false otherwise.
     */
    bool isEmpty() const;

    /**
     * Sets this bounding box to the smallest bounding box
     * that contains both this bounding box and the specified bounding sphere.
     *
     * @param sphere The bounding sphere to merge with.
     */
    void merge(const RBoundingSphere& sphere);

    /**
     * Sets this bounding box to the smallest bounding box
     * that contains both this bounding object and the specified bounding box.
     *
     * @param box The bounding box to merge with.
     */
    void merge(const RBoundingBox& box);

    /**
     * Sets this bounding box to the specified values.
     *
     * @param min The minimum point of the bounding box.
     * @param max The maximum point of the bounding box.
     */
    void set(const RVector3& min, const RVector3& max);

    /**
     * Sets this bounding box to the specified values.
     * 
     * @param minX The x coordinate of the minimum point of the bounding box.
     * @param minY The y coordinate of the minimum point of the bounding box.
     * @param minZ The z coordinate of the minimum point of the bounding box.
     * @param maxX The x coordinate of the maximum point of the bounding box.
     * @param maxY The y coordinate of the maximum point of the bounding box.
     * @param maxZ The z coordinate of the maximum point of the bounding box.
     */
    void set(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);

    /**
     * Sets this bounding box to the specified bounding box.
     *
     * @param box The bounding box to set to.
     */
    void set(const RBoundingBox& box);

    /**
     * Sets this box to tightly contain the specified bounding sphere.
     *
     * @param sphere The sphere to contain.
     */
    void set(const RBoundingSphere& sphere);

    /**
     * Transforms the bounding box by the given transformation matrix.
     *
     * @param matrix The transformation matrix to transform by.
     */
    void transform(const RMatrix& matrix);

    /**
     * Transforms this bounding box by the given matrix.
     * 
     * @param matrix The matrix to transform by.
     * @return This bounding box, after the transformation occurs.
     */
    inline RBoundingBox& operator*=(const RMatrix& matrix);
};

/**
 * Transforms the given bounding box by the given matrix.
 * 
 * @param matrix The matrix to transform by.
 * @param box The bounding box to transform.
 * @return The resulting transformed bounding box.
 */
API inline const RBoundingBox operator*(const RMatrix& matrix, const RBoundingBox& box);


}
#include "RBoundingBox.inl"
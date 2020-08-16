#pragma once
#include "common.h"
#include "RRay.h"
#include "RPlane.h"

namespace rocket
{

/**
 * Defines a 3-dimensional Frustum.
 *
 * A frustum in computer graphics is generally a volume of 3D space,
 * defined as the part of a rectangular pyramid that lies between
 * two planes perpendicular to its center line. A frustum is often used
 * to represent what a "camera" sees in your 3D space.
 *
 * The RFrustum class allows you to define a bounding frustum using a combined
 * matrix that is generally the product of a view matrix and a projection matrix.
 *
 * You can query a RFrustum object for any one of its bounding planes,
 * for its corners, and for whether it intersects with a given object.
 * Since objects that don't intersect with your view frustum generally
 * don't need to be rendered, culling them quickly can save you a lot of
 * rendering time.
 */
class API RFrustum
{
public:

    /**
     * Constructs the default RFrustum (corresponds to the identity matrix).
     */
    RFrustum();

    /**
     * Constructs a new RFrustum from the specified view projection matrix.
     *
     * @param matrix The view projection matrix to create this RFrustum from.
     */
    RFrustum(const RMatrix& matrix);

    /**
     * Constructs a new RFrustum from the given RFrustum.
     * 
     * @param RFrustum The RFrustum to create this RFrustum from.
     */
    RFrustum(const RFrustum& RFrustum);

    /**
     * Destructor.
     */
    ~RFrustum();

    /**
     * Gets the near plane of the RFrustum.
     *
     * @return near The near plane.
     */
    const RPlane& getNear() const;

    /**
     * Gets the far plane of the RFrustum.
     *
     * @return far The far plane.
     */
    const RPlane& getFar() const;

    /**
     * Gets the left plane of the RFrustum.
     *
     * @return left The left plane.
     */
    const RPlane& getLeft() const;

    /**
     * Gets the right plane of the RFrustum.
     *
     * @return right The right plane.
     */
    const RPlane& getRight() const;

    /**
     * Gets the bottom plane of the RFrustum.
     *
     * @return bottom The bottom plane.
     */
    const RPlane& getBottom() const;

    /**
     * Gets the top plane of the RFrustum.
     *
     * @return top The top plane.
     */
    const RPlane& getTop() const;

    /**
     * Gets the projection matrix corresponding to the RFrustum in the specified matrix.
     * 
     * @param dst The projection matrix to copy into.
     */
    void getMatrix(RMatrix* dst) const;

    /**
     * Gets the corners of the RFrustum in the specified array.
     *
     * The corners are stored in the following order:
     * (N-near, F-far, L-left, R-right, B-bottom, T-top)
     * LTN, LBN, RBN, RTN, RTF, RBF, LBF, LTF.
     * 
     * @param corners The array (of at least size 8) to store the corners in.
     */
    void getCorners(RVector3* corners) const;

    /**
     * Gets the corners of the RFrustum's near plane in the specified array.
     *
     * The corners are stored in the following order:
     * left-top, left-bottom, right-bottom, right-top.
     *
     * @param corners The array (of at least size 4) to store the corners in.
     */
    void getNearCorners(RVector3* corners) const;

    /**
     * Gets the corners of the RFrustum's far plane in the specified array.
     *
     * The corners are stored in the following order:
     * right-top, right-bottom, left-bottom, left-top.
     *
     * @param corners The array (of at least size 4) to store the corners in.
     */
    void getFarCorners(RVector3* corners) const;

    /**
     * Tests whether this RFrustum intersects the specified point.
     *
     * @param point The point to test intersection with.
     *
     * @return true if the specified point intersects this RFrustum; false otherwise.
     */
    bool intersects(const RVector3& point) const;

    /**
     * Tests whether this RFrustum intersects the specified point.
     *
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @param z The z coordinate.
     *
     * @return true if the specified point intersects this RFrustum; false otherwise.
     */
    bool intersects(float x, float y, float z) const;

    /**
     * Tests whether this RFrustum intersects the specified bounding sphere.
     *
     * @param sphere The bounding sphere to test intersection with.
     * 
     * @return true if the specified bounding sphere intersects this RFrustum; false otherwise.
     */
    bool intersects(const RBoundingSphere& sphere) const;

    /**
     * Tests whether this RFrustum intersects the specified bounding box.
     *
     * @param box The bounding box to test intersection with.
     * 
     * @return true if the specified bounding box intersects this RFrustum; false otherwise.
     */
    bool intersects(const RBoundingBox& box) const;

    /**
     * Tests whether this RFrustum intersects the specified plane.
     *
     * @param plane The plane to test intersection with.
     * 
     * @return RPlane::INTERSECTS_BACK if the specified bounding object is in the negative half-space of
     *  this plane, RPlane::INTERSECTS_FRONT if it is in the positive half-space of this plane,
     *  and RPlane::INTERSECTS_INTERSECTING if it intersects this plane.
     */
    float intersects(const RPlane& plane) const;

    /**
     * Tests whether this RFrustum intersects the specified ray.
     *
     * @param ray The ray to test intersection with.
     * 
     * @return RPlane::INTERSECTS_BACK if the specified ray is in the negative half-space of
     *  this plane, RPlane::INTERSECTS_FRONT if it is in the positive half-space of this plane,
     *  and RPlane::INTERSECTS_INTERSECTING if it intersects this plane.
     */
    float intersects(const RRay& ray) const;

    /**
     * Sets this RFrustum to the specified RFrustum.
     *
     * @param RFrustum The RFrustum to set to.
     */
    void set(const RFrustum& RFrustum);

    /**
     * Sets the RFrustum to the RFrustum corresponding to the specified view projection matrix.
     *
     * @param matrix The view projection matrix.
     */
    void set(const RMatrix& matrix);

private:

    /**
     * Updates the planes of the RFrustum.
     */
    void updateRPlanes();

    RPlane _near;
    RPlane _far;
    RPlane _bottom;
    RPlane _top;
    RPlane _left;
    RPlane _right;
    RMatrix _matrix;
};

}
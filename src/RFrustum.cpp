#include <common.h>
#include <RFrustum.h>
#include <RBoundingSphere.h>
#include <RBoundingBox.h>

namespace rocket
{

RFrustum::RFrustum()
{
    set(RMatrix());
}

RFrustum::RFrustum(const RMatrix& matrix)
{
    set(matrix);
}

RFrustum::RFrustum(const RFrustum& RFrustum)
{
    set(RFrustum);
}

RFrustum::~RFrustum()
{
}

const RPlane& RFrustum::getNear() const
{
    return _near;
}

const RPlane& RFrustum::getFar() const
{
    return _far;
}

const RPlane& RFrustum::getLeft() const
{
    return _left;
}

const RPlane& RFrustum::getRight() const
{
    return _right;
}

const RPlane& RFrustum::getBottom() const
{
    return _bottom;
}

const RPlane& RFrustum::getTop() const
{
    return _top;
}

void RFrustum::getMatrix(RMatrix* dst) const
{
    dst->set(_matrix);
}

void RFrustum::getCorners(RVector3* corners) const
{
    getNearCorners(corners);
    getFarCorners(corners + 4);
}

void RFrustum::getNearCorners(RVector3* corners) const
{
    RPlane::intersection(_near, _left, _top, &corners[0]);
    RPlane::intersection(_near, _left, _bottom, &corners[1]);
    RPlane::intersection(_near, _right, _bottom, &corners[2]);
    RPlane::intersection(_near, _right, _top, &corners[3]);
}

void RFrustum::getFarCorners(RVector3* corners) const
{
    RPlane::intersection(_far, _right, _top, &corners[0]);
    RPlane::intersection(_far, _right, _bottom, &corners[1]);
    RPlane::intersection(_far, _left, _bottom, &corners[2]);
    RPlane::intersection(_far, _left, _top, &corners[3]);
}

bool RFrustum::intersects(const RVector3& point) const
{
    if (_near.distance(point) <= 0)
        return false;
    if (_far.distance(point) <= 0)
        return false;
    if (_left.distance(point) <= 0)
        return false;
    if (_right.distance(point) <= 0)
        return false;
    if (_top.distance(point) <= 0)
        return false;
    if (_bottom.distance(point) <= 0)
        return false;

    return true;
}

bool RFrustum::intersects(float x, float y, float z) const
{
    return intersects(RVector3(x, y, z));
}

bool RFrustum::intersects(const RBoundingSphere& sphere) const
{
    return sphere.intersects(*this);
}

bool RFrustum::intersects(const RBoundingBox& box) const
{
    return box.intersects(*this);
}

float RFrustum::intersects(const RPlane& plane) const
{
    return plane.intersects(*this);
}

float RFrustum::intersects(const RRay& ray) const
{
    return ray.intersects(*this);
}

void RFrustum::set(const RFrustum& RFrustum)
{
    _near = RFrustum._near;
    _far = RFrustum._far;
    _bottom = RFrustum._bottom;
    _top = RFrustum._top;
    _left = RFrustum._left;
    _right = RFrustum._right;
    _matrix = RFrustum._matrix;
}

void RFrustum::updateRPlanes()
{
    _near.set(RVector3(_matrix[3] + _matrix[2], _matrix[7] + _matrix[6], _matrix[11] + _matrix[10]), _matrix[15] + _matrix[14]);
    _far.set(RVector3(_matrix[3] - _matrix[2], _matrix[7] - _matrix[6], _matrix[11] - _matrix[10]), _matrix[15] - _matrix[14]);
    _bottom.set(RVector3(_matrix[3] + _matrix[1], _matrix[7] + _matrix[5], _matrix[11] + _matrix[9]), _matrix[15] + _matrix[13]);
    _top.set(RVector3(_matrix[3] - _matrix[1], _matrix[7] - _matrix[5], _matrix[11] - _matrix[9]), _matrix[15] - _matrix[13]);
    _left.set(RVector3(_matrix[3] + _matrix[0], _matrix[7] + _matrix[4], _matrix[11] + _matrix[8]), _matrix[15] + _matrix[12]);
    _right.set(RVector3(_matrix[3] - _matrix[0], _matrix[7] - _matrix[4], _matrix[11] - _matrix[8]), _matrix[15] - _matrix[12]);
}

void RFrustum::set(const RMatrix& matrix)
{
    _matrix = matrix;

    // Update the planes.
    updateRPlanes();
}

}
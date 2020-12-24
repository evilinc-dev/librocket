#include "common.h"
#include "RTransform.h"

namespace rocket
{

int RTransform::_suspendTransformChanged(0);
std::vector<RTransform*> RTransform::_transformsChanged;

API RTransform::RTransform()
    : _matrixDirtyBits(0), _listeners(NULL)
{
    //_targetType = AnimationTarget::TRANSFORM;
    _scale.set(RVector3::one());
}

RTransform::RTransform(const RVector3& scale, const RQuaternion& rotation, const RVector3& translation)
    : _matrixDirtyBits(0), _listeners(NULL)
{
    set(scale, rotation, translation);
}

RTransform::RTransform(const RVector3& scale, const RMatrix& rotation, const RVector3& translation)
    : _matrixDirtyBits(0), _listeners(NULL)
{
    set(scale, rotation, translation);
}

RTransform::RTransform(const RTransform& copy)
    : _matrixDirtyBits(0), _listeners(NULL)
{
    set(copy);
}

RTransform::~RTransform()
{
    if (_listeners != NULL){
        delete _listeners;
    }
}

void RTransform::suspendTransformChanged()
{
    _suspendTransformChanged++;
}

void RTransform::resumeTransformChanged()
{
    if (_suspendTransformChanged == 0) // We haven't suspended transformChanged() calls, so do nothing.
        return;
    
    if (_suspendTransformChanged == 1)
    {
        // Call transformChanged() on all transforms in the list
        size_t transformCount = _transformsChanged.size();
        for (size_t i = 0; i < transformCount; i++)
        {
            RTransform* t = _transformsChanged.at(i);
            t->transformChanged();
        }

        // Go through list and reset DIRTY_NOTIFY bit. The list could potentially be larger here if the 
        // transforms we were delaying calls to transformChanged() have any child nodes.
        transformCount = _transformsChanged.size();
        for (size_t i = 0; i < transformCount; i++)
        {
            RTransform* t = _transformsChanged.at(i);
            t->_matrixDirtyBits &= ~DIRTY_NOTIFY;
        }

        // empty list for next frame.
        _transformsChanged.clear();
    }
    _suspendTransformChanged--;
}

bool RTransform::isTransformChangedSuspended()
{
    return (_suspendTransformChanged > 0);
}

const char* RTransform::getTypeName() const
{
    return "Transform";
}

const RMatrix& RTransform::getMatrix() const
{
    if (_matrixDirtyBits & (DIRTY_TRANSLATION | DIRTY_ROTATION | DIRTY_SCALE))
    {
        if (!isStatic())
        {
            bool hasScale = !_scale.isOne();
            bool hasRotation = !_rotation.isIdentity();

            // Compose the matrix in TRS order since we use column-major matrices with column vectors and
            // multiply M*v (as opposed to XNA and DirectX that use row-major matrices with row vectors and multiply v*M).
            RMatrix::createTranslation(_translation, &_matrix);
            if (hasRotation)
            {
                _matrix.rotate(_rotation);
            }
            if (hasScale)
            {
                _matrix.scale(_scale);
            }
        }

        _matrixDirtyBits &= ~(DIRTY_TRANSLATION | DIRTY_ROTATION | DIRTY_SCALE);
    }

    return _matrix;
}

const RVector3& RTransform::getScale() const
{
    return _scale;
}

void RTransform::getScale(RVector3* scale) const
{
    scale->set(_scale);
}

float RTransform::getScaleX() const
{
    return _scale.x;
}

float RTransform::getScaleY() const
{
    return _scale.y;
}

float RTransform::getScaleZ() const
{
    return _scale.z;
}

const RQuaternion& RTransform::getRotation() const
{
    return _rotation;
}

void RTransform::getRotation(RQuaternion* rotation) const
{
    rotation->set(_rotation);
}

void RTransform::getRotation(RMatrix* rotation) const
{
    RMatrix::createRotation(_rotation, rotation);
}

float RTransform::getRotation(RVector3* axis) const
{
    return _rotation.toAxisAngle(axis);
}

const RVector3& RTransform::getTranslation() const
{
    return _translation;
}

void RTransform::getTranslation(RVector3* translation) const
{
    translation->set(_translation);
}

float RTransform::getTranslationX() const
{
    return _translation.x;
}

float RTransform::getTranslationY() const
{
    return _translation.y;
}

float RTransform::getTranslationZ() const
{
    return _translation.z;
}

RVector3 RTransform::getForwardVector() const
{
    RVector3 v;
    getForwardVector(&v);
    return v;
}

void RTransform::getForwardVector(RVector3* dst) const
{
    getMatrix().getForwardVector(dst);
}

RVector3 RTransform::getBackVector() const
{
    RVector3 v;
    getBackVector(&v);
    return v;
}

void RTransform::getBackVector(RVector3* dst) const
{
    getMatrix().getBackVector(dst);
}

RVector3 RTransform::getUpVector() const
{
    RVector3 v;
    getUpVector(&v);
    return v;
}

void RTransform::getUpVector(RVector3* dst) const
{
    getMatrix().getUpVector(dst);
}

RVector3 RTransform::getDownVector() const
{
    RVector3 v;
    getDownVector(&v);
    return v;
}

void RTransform::getDownVector(RVector3* dst) const
{
    getMatrix().getDownVector(dst);
}

RVector3 RTransform::getLeftVector() const
{
    RVector3 v;
    getLeftVector(&v);
    return v;
}

void RTransform::getLeftVector(RVector3* dst) const
{
    getMatrix().getLeftVector(dst);
}

RVector3 RTransform::getRightVector() const
{
    RVector3 v;
    getRightVector(&v);
    return v;
}

void RTransform::getRightVector(RVector3* dst) const
{
    getMatrix().getRightVector(dst);
}

void RTransform::rotate(float qx, float qy, float qz, float qw)
{
    if (isStatic())
        return;

    RQuaternion q(qx, qy, qz, qw);
    _rotation.multiply(q);
    dirty(DIRTY_ROTATION);
}

void RTransform::rotate(const RQuaternion& rotation)
{
    if (isStatic())
        return;

    _rotation.multiply(rotation);
    dirty(DIRTY_ROTATION);
}

void RTransform::rotate(const RVector3& axis, float angle)
{
    if (isStatic())
        return;

    RQuaternion rotationQuat;
    RQuaternion::createFromAxisAngle(axis, angle, &rotationQuat);
    _rotation.multiply(rotationQuat);
    _rotation.normalize();
    dirty(DIRTY_ROTATION);
}

void RTransform::rotate(const RMatrix& rotation)
{
    if (isStatic())
        return;

    RQuaternion rotationQuat;
    RQuaternion::createFromRotationMatrix(rotation, &rotationQuat);
    _rotation.multiply(rotationQuat);
    dirty(DIRTY_ROTATION);
}

void RTransform::rotateX(float angle)
{
    if (isStatic())
        return;

    RQuaternion rotationQuat;
    RQuaternion::createFromAxisAngle(RVector3::unitX(), angle, &rotationQuat);
    _rotation.multiply(rotationQuat);
    dirty(DIRTY_ROTATION);
}

void RTransform::rotateY(float angle)
{
    if (isStatic())
        return;

    RQuaternion rotationQuat;
    RQuaternion::createFromAxisAngle(RVector3::unitY(), angle, &rotationQuat);
    _rotation.multiply(rotationQuat);
    dirty(DIRTY_ROTATION);
}

void RTransform::rotateZ(float angle)
{
    if (isStatic())
        return;

    RQuaternion rotationQuat;
    RQuaternion::createFromAxisAngle(RVector3::unitZ(), angle, &rotationQuat);
    _rotation.multiply(rotationQuat);
    dirty(DIRTY_ROTATION);
}

void RTransform::scale(float scale)
{
    if (isStatic())
        return;

    _scale.scale(scale);
    dirty(DIRTY_SCALE);
}

void RTransform::scale(float sx, float sy, float sz)
{
    if (isStatic())
        return;

    _scale.x *= sx;
    _scale.y *= sy;
    _scale.z *= sz;
    dirty(DIRTY_SCALE);
}

void RTransform::scale(const RVector3& scale)
{
    if (isStatic())
        return;

    _scale.x *= scale.x;
    _scale.y *= scale.y;
    _scale.z *= scale.z;
    dirty(DIRTY_SCALE);
}

void RTransform::scaleX(float sx)
{
    if (isStatic())
        return;

    _scale.x *= sx;
    dirty(DIRTY_SCALE);
}

void RTransform::scaleY(float sy)
{
    if (isStatic())
        return;

    _scale.y *= sy;
    dirty(DIRTY_SCALE);
}

void RTransform::scaleZ(float sz)
{
    if (isStatic())
        return;

    _scale.z *= sz;
    dirty(DIRTY_SCALE);
}

void RTransform::set(const RVector3& scale, const RQuaternion& rotation, const RVector3& translation)
{
    if (isStatic())
        return;

    _scale.set(scale);
    _rotation.set(rotation);
    _translation.set(translation);
    dirty(DIRTY_TRANSLATION | DIRTY_ROTATION | DIRTY_SCALE);
}

void RTransform::set(const RVector3& scale, const RMatrix& rotation, const RVector3& translation)
{
    if (isStatic())
        return;

    _scale.set(scale);
    RQuaternion rotationQuat;
    RQuaternion::createFromRotationMatrix(rotation, &rotationQuat);
    _rotation.set(rotationQuat);
    _translation.set(translation);
    dirty(DIRTY_TRANSLATION | DIRTY_ROTATION | DIRTY_SCALE);
}

void RTransform::set(const RVector3& scale, const RVector3& axis, float angle, const RVector3& translation)
{
    if (isStatic())
        return;

    _scale.set(scale);
    _rotation.set(axis, angle);
    _translation.set(translation);
    dirty(DIRTY_TRANSLATION | DIRTY_ROTATION | DIRTY_SCALE);
}

void RTransform::set(const RTransform& transform)
{
    if (isStatic())
        return;

    _scale.set(transform._scale);
    _rotation.set(transform._rotation);
    _translation.set(transform._translation);
    dirty(DIRTY_TRANSLATION | DIRTY_ROTATION | DIRTY_SCALE);
}

void RTransform::setIdentity()
{
    if (isStatic())
        return;

    _scale.set(1.0f, 1.0f, 1.0f);
    _rotation.setIdentity();
    _translation.set(0.0f, 0.0f, 0.0f);
    dirty(DIRTY_TRANSLATION | DIRTY_ROTATION | DIRTY_SCALE);
}

void RTransform::setScale(float scale)
{
    if (isStatic())
        return;

    _scale.set(scale, scale, scale);
    dirty(DIRTY_SCALE);
}

void RTransform::setScale(float sx, float sy, float sz)
{
    if (isStatic())
        return;

    _scale.set(sx, sy, sz);
    dirty(DIRTY_SCALE);
}

void RTransform::setScale(const RVector3& scale)
{
    _scale.set(scale);
    dirty(DIRTY_SCALE);
}

void RTransform::setScaleX(float sx)
{
    if (isStatic())
        return;

    _scale.x = sx;
    dirty(DIRTY_SCALE);
}

void RTransform::setScaleY(float sy)
{
    if (isStatic())
        return;

    _scale.y = sy;
    dirty(DIRTY_SCALE);
}

void RTransform::setScaleZ(float sz)
{
    if (isStatic())
        return;

    _scale.z = sz;
    dirty(DIRTY_SCALE);
}

void RTransform::setRotation(const RQuaternion& rotation)
{
    if (isStatic())
        return;

    _rotation.set(rotation);
    dirty(DIRTY_ROTATION);
}

void RTransform::setRotation(float qx, float qy, float qz, float qw)
{
    if (isStatic())
        return;

    _rotation.set(qx, qy, qz, qw);
    dirty(DIRTY_ROTATION);
}

void RTransform::setRotation(const RMatrix& rotation)
{
    if (isStatic())
        return;

    RQuaternion rotationQuat;
    RQuaternion::createFromRotationMatrix(rotation, &rotationQuat);
    _rotation.set(rotationQuat);
    dirty(DIRTY_ROTATION);
}

void RTransform::setRotation(const RVector3& axis, float angle)
{
    if (isStatic())
        return;

    _rotation.set(axis, angle);
    dirty(DIRTY_ROTATION);
}

void RTransform::setTranslation(const RVector3& translation)
{
    if (isStatic())
        return;

    _translation.set(translation);
    dirty(DIRTY_TRANSLATION);
}

void RTransform::setTranslation(float tx, float ty, float tz)
{
    if (isStatic())
        return;

    _translation.set(tx, ty, tz);
    dirty(DIRTY_TRANSLATION);
}

void RTransform::setTranslationX(float tx)
{
    if (isStatic())
        return;

    _translation.x = tx;
    dirty(DIRTY_TRANSLATION);
}

void RTransform::setTranslationY(float ty)
{
    if (isStatic())
        return;

    _translation.y = ty;
    dirty(DIRTY_TRANSLATION);
}

void RTransform::setTranslationZ(float tz)
{
    if (isStatic())
        return;

    _translation.z = tz;
    dirty(DIRTY_TRANSLATION);
}

void RTransform::translate(float tx, float ty, float tz)
{
    if (isStatic())
        return;

    _translation.x += tx;
    _translation.y += ty;
    _translation.z += tz;
    dirty(DIRTY_TRANSLATION);
}

void RTransform::translate(const RVector3& translation)
{
    if (isStatic())
        return;

    _translation.x += translation.x;
    _translation.y += translation.y;
    _translation.z += translation.z;
    dirty(DIRTY_TRANSLATION);
}

void RTransform::translateX(float tx)
{
    if (isStatic())
        return;

    _translation.x += tx;
    dirty(DIRTY_TRANSLATION);
}

void RTransform::translateY(float ty)
{
    if (isStatic())
        return;

    _translation.y += ty;
    dirty(DIRTY_TRANSLATION);
}

void RTransform::translateZ(float tz)
{
    if (isStatic())
        return;

    _translation.z += tz;
    dirty(DIRTY_TRANSLATION);
}

void RTransform::translateLeft(float amount)
{
    if (isStatic())
        return;

    // Force the current transform matrix to be updated.
    getMatrix();

    RVector3 left;
    _matrix.getLeftVector(&left);
    left.normalize();
    left.scale(amount);

    translate(left);
}

void RTransform::translateUp(float amount)
{
    if (isStatic())
        return;

    // Force the current transform matrix to be updated.
    getMatrix();

    RVector3 up;
    _matrix.getUpVector(&up);
    up.normalize();
    up.scale(amount);

    translate(up);
}

void RTransform::translateForward(float amount)
{
    if (isStatic())
        return;

    // Force the current transform matrix to be updated.
    getMatrix();

    RVector3 forward;
    _matrix.getForwardVector(&forward);
    forward.normalize();
    forward.scale(amount);

    translate(forward);
}

void RTransform::translateSmooth(const RVector3& target, float elapsedTime, float responseTime)
{
    if (isStatic())
        return;

    if (elapsedTime > 0)
    {
        _translation += (target - _translation) * (elapsedTime / (elapsedTime + responseTime));
        dirty(DIRTY_TRANSLATION);
    }
}

void RTransform::transformPoint(RVector3* point)
{
    getMatrix();
    _matrix.transformPoint(point);
}

void RTransform::transformPoint(const RVector3& point, RVector3* dst)
{
    getMatrix();
    _matrix.transformPoint(point, dst);
}

void RTransform::transformVector(RVector3* normal)
{
    getMatrix();
    _matrix.transformVector(normal);
}

void RTransform::transformVector(const RVector3& normal, RVector3* dst)
{
    getMatrix();
    _matrix.transformVector(normal, dst);
}

void RTransform::transformVector(float x, float y, float z, float w, RVector3* dst)
{
    getMatrix();
    _matrix.transformVector(x, y, z, w, dst);
}

bool RTransform::isStatic() const
{
    return false;
}

void RTransform::dirty(char matrixDirtyBits)
{
    _matrixDirtyBits |= matrixDirtyBits;
    if (isTransformChangedSuspended())
    {
        if (!isDirty(DIRTY_NOTIFY))
        {
            suspendTransformChange(this);
        }
    }
    else
    {
        transformChanged();
    }
}

bool RTransform::isDirty(char matrixDirtyBits) const
{
    return (_matrixDirtyBits & matrixDirtyBits) == matrixDirtyBits;
}

void RTransform::suspendTransformChange(RTransform* transform)
{
    transform->_matrixDirtyBits |= DIRTY_NOTIFY;
    _transformsChanged.push_back(transform);
}

void RTransform::addListener(RTransform::Listener* listener, long cookie)
{
    if (_listeners == NULL)
        _listeners = new std::list<RTransformListener>();

    RTransformListener l;
    l.listener = listener;
    l.cookie = cookie;
    _listeners->push_back(l);
}

void RTransform::removeListener(RTransform::Listener* listener)
{
    if (_listeners)
    {
        for (std::list<RTransformListener>::iterator itr = _listeners->begin(); itr != _listeners->end(); ++itr)
        {
            if ((*itr).listener == listener)
            {
                _listeners->erase(itr);
                break;
            }
        }
    }
}

void RTransform::transformChanged()
{
    if (_listeners)
    {
        for (std::list<RTransformListener>::iterator itr = _listeners->begin(); itr != _listeners->end(); ++itr)
        {
            RTransformListener& l = *itr;
            l.listener->transformChanged(this, l.cookie);
        }
    }
}

}
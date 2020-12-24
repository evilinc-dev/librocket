#include "common.h"
#include "RVector2.h"

namespace rocket
{

RVector2::RVector2()
    : x(0.0f), y(0.0f)
{
}

RVector2::RVector2(float x, float y)
    : x(x), y(y)
{
}

RVector2::RVector2(const float* array)
{
    set(array);
}

RVector2::RVector2(const RVector2& p1, const RVector2& p2)
{
    set(p1, p2);
}

RVector2::RVector2(const RVector2& copy)
{
    set(copy);
}

RVector2::~RVector2()
{
}

const RVector2& RVector2::zero()
{
    static RVector2 value(0.0f, 0.0f);
    return value;
}

const RVector2& RVector2::one()
{
    static RVector2 value(1.0f, 1.0f);
    return value;
}

const RVector2& RVector2::unitX()
{
    static RVector2 value(1.0f, 0.0f);
    return value;
}

const RVector2& RVector2::unitY()
{
    static RVector2 value(0.0f, 1.0f);
    return value;
}

bool RVector2::isZero() const
{
    return x == 0.0f && y == 0.0f;
}

bool RVector2::isOne() const
{
    return x == 1.0f && y == 1.0f;
}

float RVector2::angle(const RVector2& v1, const RVector2& v2)
{
    float dz = v1.x * v2.y - v1.y * v2.x;
    return atan2f(fabsf(dz) + MATH_FLOAT_SMALL, dot(v1, v2));
}

void RVector2::add(const RVector2& v)
{
    x += v.x;
    y += v.y;
}

void RVector2::add(const RVector2& v1, const RVector2& v2, RVector2* dst)
{
    dst->x = v1.x + v2.x;
    dst->y = v1.y + v2.y;
}

void RVector2::clamp(const RVector2& min, const RVector2& max)
{
    // Clamp the x value.
    if (x < min.x)
        x = min.x;
    if (x > max.x)
        x = max.x;

    // Clamp the y value.
    if (y < min.y)
        y = min.y;
    if (y > max.y)
        y = max.y;
}

void RVector2::clamp(const RVector2& v, const RVector2& min, const RVector2& max, RVector2* dst)
{
    // Clamp the x value.
    dst->x = v.x;
    if (dst->x < min.x)
        dst->x = min.x;
    if (dst->x > max.x)
        dst->x = max.x;

    // Clamp the y value.
    dst->y = v.y;
    if (dst->y < min.y)
        dst->y = min.y;
    if (dst->y > max.y)
        dst->y = max.y;
}

float RVector2::distance(const RVector2& v) const
{
    float dx = v.x - x;
    float dy = v.y - y;

    return sqrt(dx * dx + dy * dy);
}

float RVector2::distanceSquared(const RVector2& v) const
{
    float dx = v.x - x;
    float dy = v.y - y;
    return (dx * dx + dy * dy);
}

float RVector2::dot(const RVector2& v) const
{
    return (x * v.x + y * v.y);
}

float RVector2::dot(const RVector2& v1, const RVector2& v2)
{
    return (v1.x * v2.x + v1.y * v2.y);
}

float RVector2::length() const
{
    return sqrt(x * x + y * y);
}

float RVector2::lengthSquared() const
{
    return (x * x + y * y);
}

void RVector2::negate()
{
    x = -x;
    y = -y;
}

RVector2& RVector2::normalize()
{
    normalize(this);
    return *this;
}

void RVector2::normalize(RVector2* dst) const
{
    if (dst != this)
    {
        dst->x = x;
        dst->y = y;
    }

    float n = x * x + y * y;
    // Already normalized.
    if (n == 1.0f)
        return;

    n = sqrt(n);
    // Too close to zero.
    if (n < MATH_TOLERANCE)
        return;

    n = 1.0f / n;
    dst->x *= n;
    dst->y *= n;
}

void RVector2::scale(float scalar)
{
    x *= scalar;
    y *= scalar;
}

void RVector2::scale(const RVector2& scale)
{
    x *= scale.x;
    y *= scale.y;
}

void RVector2::rotate(const RVector2& point, float angle)
{
    double sinAngle = sin(angle);
    double cosAngle = cos(angle);

    if (point.isZero())
    {
        float tempX = x * cosAngle - y * sinAngle;
        y = y * cosAngle + x * sinAngle;
        x = tempX;
    }
    else
    {
        float tempX = x - point.x;
        float tempY = y - point.y;

        x = tempX * cosAngle - tempY * sinAngle + point.x;
        y = tempY * cosAngle + tempX * sinAngle + point.y;
    }
}

void RVector2::set(float x, float y)
{
    this->x = x;
    this->y = y;
}

void RVector2::set(const float* array)
{
    x = array[0];
    y = array[1];
}

void RVector2::set(const RVector2& v)
{
    this->x = v.x;
    this->y = v.y;
}

void RVector2::set(const RVector2& p1, const RVector2& p2)
{
     x = p2.x - p1.x;
     y = p2.y - p1.y;
}

void RVector2::subtract(const RVector2& v)
{
    x -= v.x;
    y -= v.y;
}

void RVector2::subtract(const RVector2& v1, const RVector2& v2, RVector2* dst)
{
    dst->x = v1.x - v2.x;
    dst->y = v1.y - v2.y;
}

void RVector2::smooth(const RVector2& target, float elapsedTime, float responseTime)
{
    if (elapsedTime > 0)
    {
        *this += (target - *this) * (elapsedTime / (elapsedTime + responseTime));
    }
}

}

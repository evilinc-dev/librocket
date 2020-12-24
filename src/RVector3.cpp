#include "common.h"
#include "RVector3.h"
#include "RMath.h"

namespace rocket
{

RVector3::RVector3()
    : x(0.0f), y(0.0f), z(0.0f)
{
}

RVector3::RVector3(float x, float y, float z)
    : x(x), y(y), z(z)
{
}

RVector3::RVector3(const float* array)
{
    set(array);
}

RVector3::RVector3(const RVector3& p1, const RVector3& p2)
{
    set(p1, p2);
}

RVector3::RVector3(const RVector3& copy)
{
    set(copy);
}

RVector3 RVector3::fromColor(unsigned int color)
{
    float components[3];
    int componentIndex = 0;
    for (int i = 2; i >= 0; --i)
    {
        int component = (color >> i*8) & 0x0000ff;

        components[componentIndex++] = static_cast<float>(component) / 255.0f;
    }

    RVector3 value(components);
    return value;
}

RVector3::~RVector3()
{
}

const RVector3& RVector3::zero()
{
    static RVector3 value(0.0f, 0.0f, 0.0f);
    return value;
}

const RVector3& RVector3::one()
{
    static RVector3 value(1.0f, 1.0f, 1.0f);
    return value;
}

const RVector3& RVector3::unitX()
{
    static RVector3 value(1.0f, 0.0f, 0.0f);
    return value;
}

const RVector3& RVector3::unitY()
{
    static RVector3 value(0.0f, 1.0f, 0.0f);
    return value;
}

const RVector3& RVector3::unitZ()
{
    static RVector3 value(0.0f, 0.0f, 1.0f);
    return value;
}

bool RVector3::isZero() const
{
    return x == 0.0f && y == 0.0f && z == 0.0f;
}

bool RVector3::isOne() const
{
    return x == 1.0f && y == 1.0f && z == 1.0f;
}

float RVector3::angle(const RVector3& v1, const RVector3& v2)
{
    float dx = v1.y * v2.z - v1.z * v2.y;
    float dy = v1.z * v2.x - v1.x * v2.z;
    float dz = v1.x * v2.y - v1.y * v2.x;

    return std::atan2f(std::sqrt(dx * dx + dy * dy + dz * dz) + MATH_FLOAT_SMALL, dot(v1, v2));
}

void RVector3::add(const RVector3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
}

void RVector3::add(const RVector3& v1, const RVector3& v2, RVector3* dst)
{
    dst->x = v1.x + v2.x;
    dst->y = v1.y + v2.y;
    dst->z = v1.z + v2.z;
}

void RVector3::clamp(const RVector3& min, const RVector3& max)
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

    // Clamp the z value.
    if (z < min.z)
        z = min.z;
    if (z > max.z)
        z = max.z;
}

void RVector3::clamp(const RVector3& v, const RVector3& min, const RVector3& max, RVector3* dst)
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

    // Clamp the z value.
    dst->z = v.z;
    if (dst->z < min.z)
        dst->z = min.z;
    if (dst->z > max.z)
        dst->z = max.z;
}

void RVector3::cross(const RVector3& v)
{
    cross(*this, v, this);
}

void RVector3::cross(const RVector3& v1, const RVector3& v2, RVector3* dst)
{
    // NOTE: This code assumes RVector3 struct members are contiguous floats in memory.
    // We might want to revisit this (and other areas of code that make this assumption)
    // later to guarantee 100% safety/compatibility.
    RMath::crossVector3(&v1.x, &v2.x, &dst->x);
}

float RVector3::distance(const RVector3& v) const
{
    float dx = v.x - x;
    float dy = v.y - y;
    float dz = v.z - z;

    return sqrt(dx * dx + dy * dy + dz * dz);
}

float RVector3::distanceSquared(const RVector3& v) const
{
    float dx = v.x - x;
    float dy = v.y - y;
    float dz = v.z - z;

    return (dx * dx + dy * dy + dz * dz);
}

float RVector3::dot(const RVector3& v) const
{
    return (x * v.x + y * v.y + z * v.z);
}

float RVector3::dot(const RVector3& v1, const RVector3& v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float RVector3::length() const
{
    return std::sqrt(x * x + y * y + z * z);
}

float RVector3::lengthSquared() const
{
    return (x * x + y * y + z * z);
}

void RVector3::negate()
{
    x = -x;
    y = -y;
    z = -z;
}

RVector3& RVector3::normalize()
{
    normalize(this);
    return *this;
}

void RVector3::normalize(RVector3* dst) const
{
    if (dst != this)
    {
        dst->x = x;
        dst->y = y;
        dst->z = z;
    }

    float n = x * x + y * y + z * z;
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
    dst->z *= n;
}

void RVector3::scale(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

void RVector3::set(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void RVector3::set(const float* array)
{
    x = array[0];
    y = array[1];
    z = array[2];
}

void RVector3::set(const RVector3& v)
{
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}

void RVector3::set(const RVector3& p1, const RVector3& p2)
{
    x = p2.x - p1.x;
    y = p2.y - p1.y;
    z = p2.z - p1.z;
}

void RVector3::subtract(const RVector3& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

void RVector3::subtract(const RVector3& v1, const RVector3& v2, RVector3* dst)
{
    dst->x = v1.x - v2.x;
    dst->y = v1.y - v2.y;
    dst->z = v1.z - v2.z;
}

void RVector3::smooth(const RVector3& target, float elapsedTime, float responseTime)
{
    if (elapsedTime > 0)
    {
        *this += (target - *this) * (elapsedTime / (elapsedTime + responseTime));
    }
}

}

#include "common.h"
#include "RRectangle.h"

using std::min;
using std::max;

namespace rocket
{

RRectangle::RRectangle()
    : x(0), y(0), width(0), height(0)
{
}

RRectangle::RRectangle(float width, float height) :
    x(0), y(0), width(width), height(height)
{
}

RRectangle::RRectangle(float x, float y, float width, float height) :
    x(x), y(y), width(width), height(height)
{
}

RRectangle::RRectangle(const RRectangle& copy)
{
    set(copy);
}

RRectangle::~RRectangle()
{
}

const RRectangle& RRectangle::empty()
{
    static RRectangle empty;
    return empty;
}

bool RRectangle::isEmpty() const
{
    return (x == 0 && y == 0 && width == 0 && height == 0);
}

void RRectangle::set(const RRectangle& r)
{
    set(r.x, r.y, r.width, r.height);
}

void RRectangle::set(float x, float y, float width, float height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void RRectangle::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;
}

float RRectangle::left() const
{
    return x;
}

float RRectangle::top() const
{
    return y;
}

float RRectangle::right() const
{
    return x + width;
}

float RRectangle::bottom() const
{
    return y + height;
}

bool RRectangle::contains(float x, float y) const
{
    return (x >= this->x && x <= (this->x + width) && y >= this->y && y <= (this->y + height));
}

bool RRectangle::contains(float x, float y, float width, float height) const
{
    return (contains(x, y) && contains(x + width, y + height));
}

bool RRectangle::contains(const RRectangle& r) const
{
    return contains(r.x, r.y, r.width, r.height);
}

bool RRectangle::intersects(float x, float y, float width, float height) const
{
    float t;
    if ((t = x - this->x) > this->width || -t > width)
        return false;
    if ((t = y - this->y) > this->height || -t > height)
        return false;
    return true;
}

bool RRectangle::intersects(const RRectangle& r) const
{
    return intersects(r.x, r.y, r.width, r.height);
}

bool RRectangle::intersect(const RRectangle& r1, const RRectangle& r2, RRectangle* dst)
{

    float xmin = max(r1.x, r2.x);
    float xmax = min(r1.right(), r2.right());
    if (xmax > xmin)
    {
        float ymin = max(r1.y, r2.y);
        float ymax = min(r1.bottom(), r2.bottom());
        if (ymax > ymin)
        {
            dst->set(xmin, ymin, xmax - xmin, ymax - ymin);
            return true;
        }
    }

    dst->set(0, 0, 0, 0);
    return false;
}

void RRectangle::combine(const RRectangle& r1, const RRectangle& r2, RRectangle* dst)
{

    dst->x = min(r1.x, r2.x);
    dst->y = min(r1.y, r2.y);
    dst->width = max(r1.x + r1.width, r2.x + r2.width) - dst->x;
    dst->height = max(r1.y + r1.height, r2.y + r2.height) - dst->y;
}

void RRectangle::inflate(float horizontalAmount, float verticalAmount)
{
    x -= horizontalAmount;
    y -= verticalAmount;
    width += horizontalAmount * 2;
    height += verticalAmount * 2;
}

RRectangle& RRectangle::operator = (const RRectangle& r)
{
    x = r.x;
    y = r.y;
    width = r.width;
    height = r.height;
    return *this;
}

bool RRectangle::operator == (const RRectangle& r) const
{
    return (x == r.x && width == r.width && y == r.y && height == r.height);
}

bool RRectangle::operator != (const RRectangle& r) const
{
    return (x != r.x || width != r.width || y != r.y || height != r.height);
}

}
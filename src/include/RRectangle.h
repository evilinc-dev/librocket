#pragma once

#include "common.h"

namespace rocket
{

/**
 * Defines a rectangle.
 */
class API RRectangle
{
public:

    /**
     * Specifies the x-coordinate of the rectangle.
     */
    float x;

    /**
     * Specifies the y-coordinate of the rectangle.
     */
    float y;

    /**
     * Specifies the width of the rectangle.
     */
    float width;

    /**
     * Specifies the height of the rectangle.
     */
    float height;

    /**
     * Constructs a new rectangle initialized to all zeros.
     */
    RRectangle();

    /**
     * Constructs a new rectangle with the x = 0, y = 0 and the specified width and height.
     *
     * @param width The width of the rectangle.
     * @param height The height of the rectangle.
     */
    RRectangle(float width, float height);

    /**
     * Constructs a new rectangle with the specified x, y, width and height.
     *
     * @param x The x-coordinate of the rectangle.
     * @param y The y-coordinate of the rectangle.
     * @param width The width of the rectangle.
     * @param height The height of the rectangle.
     */
    RRectangle(float x, float y, float width, float height);

    /**
     * Constructs a new rectangle that is a copy of the specified rectangle.
     *
     * @param copy The rectangle to copy.
     */
    RRectangle(const Rectangle& copy);

    /**
     * Destructor.
     */
    ~RRectangle();

    /**
     * Returns a rectangle with all of its values set to zero.
     *
     * @return The empty rectangle with all of its values set to zero.
     */
    static const RRectangle& empty();

    /**
     * Gets a value that indicates whether the rectangle is empty.
     *
     * @return true if the rectangle is empty, false otherwise.
     */
    bool isEmpty() const;

    /**
     * Sets the values of this rectangle to the specified values.
     *
     * @param x The x-coordinate of the rectangle.
     * @param y The y-coordinate of the rectangle.
     * @param width The width of the rectangle.
     * @param height The height of the rectangle.
     */
    void set(float x, float y, float width, float height);

    /**
     * Sets the values of this rectangle to those in the specified rectangle.
     *
     * @param r The rectangle to copy.
     */
    void set(const RRectangle& r);

    /**
     * Sets the x-coordinate and y-coordinate values of this rectangle to the specified values.
     *
     * @param x The x-coordinate of the rectangle.
     * @param y The y-coordinate of the rectangle.
     */
    void setPosition(float x, float y);

    /**
     * Returns the x-coordinate of the left side of the rectangle.
     *
     * @return The x-coordinate of the left side of the rectangle.
     */
    float left() const;

    /**
     * Returns the y-coordinate of the top of the rectangle.
     *
     * @return The y-coordinate of the top of the rectangle.
     */
    float top() const;

    /**
     * Returns the x-coordinate of the right side of the rectangle.
     *
     * @return The x-coordinate of the right side of the rectangle.
     */
    float right() const;

    /**
     * Returns the y-coordinate of the bottom of the rectangle.
     *
     * @return The y-coordinate of the bottom of the rectangle.
     */
    float bottom() const;

    /**
     * Determines whether this rectangle contains a specified point.
     *
     * @param x The x-coordinate of the point.
     * @param y The y-coordinate of the point.
     * 
     * @return true if the rectangle contains the point, false otherwise.
     */
    bool contains(float x, float y) const;

    /**
     * Determines whether this rectangle contains a specified rectangle.
     *
     * @param x The x-coordinate of the rectangle.
     * @param y The y-coordinate of the rectangle.
     * @param width The width of the rectangle.
     * @param height The height of the rectangle.
     * 
     * @return true if the rectangle contains the specified rectangle, false
     * otherwise.
     */
    bool contains(float x, float y, float width, float height) const;

    /**
     * Determines whether this rectangle contains a specified rectangle.
     *
     * @param r The rectangle.
     * 
     * @return true if the rectangle contains the specified rectangle, false
     * otherwise.
     */
    bool contains(const RRectangle& r) const;

    /**
     * Determines whether a specified rectangle intersects with this rectangle.
     * Rectangles intersect if there is a common point that is contained in both rectangles.
     *
     * @param x The x-coordinate of the rectangle.
     * @param y The y-coordinate of the rectangle.
     * @param width The width of the rectangle.
     * @param height The height of the rectangle.
     * 
     * @return true if the specified Rectangle intersects with this one, false otherwise.
     */
    bool intersects(float x, float y, float width, float height) const;

    /**
     * Determines whether a specified rectangle intersects with this rectangle.
     *
     * @param r The rectangle.
     * 
     * @return true if the specified rectangle intersects with this one, false
     * otherwise.
     */
    bool intersects(const RRectangle& r) const;

    /**
     * Computes the intersection of two rectangles and returns the result.
     *
     * @param r1 The first rectangle.
     * @param r2 The second rectangle.
     * @param dst Populated with the resulting intersection, or Rectangle.empty if they do not intersect.
     *
     * @return True if the two rectangles intersect, false otherwise.
     */
    static bool intersect(const RRectangle& r1, const RRectangle& r2, RRectangle* dst);

    /**
     * Returns a new rectangle that exactly contains two other rectangles.
     *
     * @param r1 The first rectangle to contain.
     * @param r2 The second rectangle to contain.
     * @param dst A rectangle to store the union of the two rectangle parameters.
     */
    static void combine(const RRectangle& r1, const RRectangle& r2, RRectangle* dst);

    /**
     * Pushes the edges of the Rectangle out by the horizontal and vertical values specified.
     *
     * Each corner of the Rectangle is pushed away from the center of the rectangle
     * by the specified amounts. This results in the width and height of the Rectangle
     * increasing by twice the values provided.
     *
     * @param horizontalAmount The value to push the sides out by.
     * @param verticalAmount The value to push the top and bottom out by.
     */
    void inflate(float horizontalAmount, float verticalAmount);

    /**
     * operator =
     */
    RRectangle& operator = (const RRectangle& r);

    /**
     * operator ==
     */
    bool operator == (const RRectangle& r) const;

    /**
     * operator !=
     */
    bool operator != (const RRectangle& r) const;
};

}
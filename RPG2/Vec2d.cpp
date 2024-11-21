#include <math.h>
#include "Vec2d.hpp"

Vec2d::Vec2d() {}

Vec2d::Vec2d(double x, double y) : x(x), y(y) {}

bool Vec2d::operator == (const Vec2d& v2) const
{
    return (x == v2.x && y == v2.y);
}

bool Vec2d::operator != (const Vec2d& v2) const
{
    return (x != v2.x && y != v2.y);
}

Vec2d Vec2d::operator + (const Vec2d& v2) const
{
    return Vec2d(x + v2.x, y + v2.y);
}
Vec2d Vec2d::operator - (const Vec2d& v2) const
{
    return Vec2d(x - v2.x, y - v2.y);
}
Vec2d Vec2d::operator * (const double val) const
{
    return Vec2d(x * val, y * val);
}
Vec2d Vec2d::operator / (const double val) const
{
    return Vec2d(x / val, y / val);
}

void Vec2d::operator += (const Vec2d& v2)
{
    x += v2.x;
    y += v2.y;
}
void Vec2d::operator -= (const Vec2d& v2)
{
    x -= v2.x;
    y -= v2.y;
}
void Vec2d::operator *= (const double val)
{
    x *= val;
    y *= val;
}
void Vec2d::operator /= (const double val)
{
    x /= val;
    y /= val;
}

double Vec2d::dist(const Vec2d& v2) const
{
    double dx = v2.x - x;
    double dy = v2.y - y;
    return sqrt(dx * dx + dy * dy);
}

double Vec2d::dist2(const Vec2d& v2) const
{
    double dx = fabs(v2.x - x);
    double dy = fabs(v2.y - y);
    double distance = dx * dx + dy * dy;

    return (distance < 10) ? 0.0 : distance;
}


double Vec2d::getX() const
{
    return x;
}

double Vec2d::getY() const
{
    return y;
}

void Vec2d::setX(const double num)
{
    x = num;
}

void Vec2d::setY(const double num)
{
    y = num;
}



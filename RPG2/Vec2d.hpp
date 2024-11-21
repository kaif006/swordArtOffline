#pragma once
#include <math.h>
#include <cmath>

class Vec2d
{
public:
    double x;
    double y;

    Vec2d();
    Vec2d(double x, double y);

    bool operator == (const Vec2d& v2) const;

    bool operator != (const Vec2d& v2) const;
    Vec2d operator + (const Vec2d& v2) const;
    Vec2d operator - (const Vec2d& v2) const;
    Vec2d operator * (const double val) const;
    Vec2d operator / (const double val) const;

    void operator += (const Vec2d& v2);
    void operator -= (const Vec2d& v2);
    void operator *= (const double val);
    void operator /= (const double val);

    double dist(const Vec2d& v2) const;
    double dist2(const Vec2d& v2) const;

    double getX() const;
    double getY() const;
    void setX(const double num);
    void setY(const double num);
};
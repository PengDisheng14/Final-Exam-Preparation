#include <iostream>
#include <cmath>
using namespace std;

class Point
{
protected:
    double x, y;

public:
    Point(double x, double y) : x(x), y(y) {}
    Point(const Point &p);
    void operator=(const Point &p);
    friend ostream &operator<<(ostream &os, const Point &p);
};

Point::Point(const Point &p)
{
    x = p.x;
    y = p.y;
}

void Point::operator=(const Point &p)
{
    x = p.x;
    y = p.y;
}

ostream &operator<<(ostream &os, const Point &p)
{
    os << "(" << p.x << "," << p.y << ")";
    return os;
}

class ThreeDPoint : public Point
{
    double z;

public:
    ThreeDPoint(double x, double y, double z) : Point(x, y), z(z) {}
    double distance(const ThreeDPoint &);
    friend ostream &operator<<(ostream &os, const ThreeDPoint &th);
};

double ThreeDPoint::distance(const ThreeDPoint &th)
{
    double Dx = x - th.x;
    double Dy = y - th.y;
    double Dz = z - th.z;
    return sqrt(Dx * Dx + Dy * Dy + Dz * Dz);
}

ostream &operator<<(ostream &os, const ThreeDPoint &th)
{
    os << "(" << th.x << "," << th.y << "," << th.z << ")";
    return os;
}

class Rectangle : protected Point
{
    Point LeftDown;
    double length, width;

public:
    Rectangle(double x0, double y0, double x, double y, double len, double wid) : Point(x0, y0), LeftDown(x, y), length(len), width(wid) {}
    Rectangle(const Rectangle &other) : Point(other), LeftDown(other.LeftDown), length(other.length), width(other.width) {}
    void operator=(const Rectangle &other);
};

void Rectangle::operator=(const Rectangle &other)
{
    LeftDown = other.LeftDown;
    length = other.length;
    width = other.width;
}

class Line
{
    ThreeDPoint th1, th2;

public:
    Line(const ThreeDPoint &th1, const ThreeDPoint &th2) : th1(th1), th2(th2) {}
    void displayLine();
    double lengthLine();
};

void Line::displayLine()
{
    cout << "端点一：" << th1 << endl;
    cout << "端点二：" << th2 << endl;
}

double Line::lengthLine()
{
    return th1.distance(th2);
}
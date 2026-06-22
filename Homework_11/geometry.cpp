#include <iostream>
#include <cmath>
#include <string>
using namespace std;

class Point
{
protected:
    double x, y;

public:
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}
    Point(const Point &p) : x(p.x), y(p.y) {}
    Point &operator=(const Point &p);

    double getX() const { return x; }
    double getY() const { return y; }
    friend ostream &operator<<(ostream &os, const Point &p);
};

Point &Point::operator=(const Point &p)
{
    if (this != &p)
    {
        x = p.x;
        y = p.y;
    }
    return *this;
}

ostream &operator<<(ostream &os, const Point &p)
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

class ThreeDPoint : public Point
{
protected:
    double z;

public:
    ThreeDPoint(double x = 0.0, double y = 0.0, double z = 0.0)
        : Point(x, y), z(z) {}

    ThreeDPoint(const ThreeDPoint &p) : Point(p), z(p.z) {}

    ThreeDPoint &operator=(const ThreeDPoint &p)
    {
        if (this != &p)
        {
            Point::operator=(p);
            z = p.z;
        }
        return *this;
    }

    void setZ(double val) { z = val; }
    double getZ() const { return z; }

    void setPoint(double px, double py, double pz)
    {
        x = px;
        y = py;
        z = pz;
    }

    double distance(const ThreeDPoint &other) const
    {
        double dx = x - other.x;
        double dy = y - other.y;
        double dz = z - other.z;
        return sqrt(dx * dx + dy * dy + dz * dz);
    }

    friend ostream &operator<<(ostream &os, const ThreeDPoint &p);
};

ostream &operator<<(ostream &os, const ThreeDPoint &p)
{
    os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
    return os;
}

class Rectangle : protected Point
{
protected:
    double width, height;

public:
    Rectangle(double x = 0.0, double y = 0.0,
              double w = 0.0, double h = 0.0)
        : Point(x, y), width(w), height(h) {}

    Rectangle(const Rectangle &r)
        : Point(r), width(r.width), height(r.height) {}

    Rectangle &operator=(const Rectangle &r)
    {
        if (this != &r)
        {
            Point::operator=(r);
            width = r.width;
            height = r.height;
        }
        return *this;
    }

    void setRectangle(double px, double py, double w, double h)
    {
        x = px;
        y = py;
        width = w;
        height = h;
    }

    double area() const { return width * height; }

    int relation(double px, double py) const
    {
        bool onEdge =
            ((px == x || px == x + width) && py >= y && py <= y + height) ||
            ((py == y || py == y + height) && px >= x && px <= x + width);
        if (onEdge)
            return 1;
        if (px > x && px < x + width && py > y && py < y + height)
            return 0;
        return 2;
    }

    string relationStr(double px, double py) const
    {
        int r = relation(px, py);
        if (r == 0)
            return "矩形内部";
        if (r == 1)
            return "矩形边上";
        return "矩形外部";
    }

    void printInfo() const
    {
        cout << "矩形左下角: (" << x << ", " << y << ")"
             << "  宽=" << width << "  高=" << height << endl;
    }

    double getX() const { return x; }
    double getY() const { return y; }
    double getWidth() const { return width; }
    double getHeight() const { return height; }
};

class Line
{
private:
    ThreeDPoint start, end;

public:
    Line(const ThreeDPoint &s, const ThreeDPoint &e) : start(s), end(e) {}

    void display() const;

    double length() const;
};

void Line::display() const
{
    cout << "线段: " << start << " --> " << end << endl;
}

double Line::length() const
{
    return start.distance(end);
}

class Cuboid : private Rectangle
{
private:
    double depth;

public:
    Cuboid(double x = 0.0, double y = 0.0,
           double w = 0.0, double h = 0.0, double d = 0.0)
        : Rectangle(x, y, w, h), depth(d) {}

    Cuboid(const Cuboid &c) : Rectangle(c), depth(c.depth) {}

    Cuboid &operator=(const Cuboid &c)
    {
        if (this != &c)
        {
            Rectangle::operator=(c);
            depth = c.depth;
        }
        return *this;
    }

    double surfaceArea() const
    {
        return 2.0 * (width * height + width * depth + height * depth);
    }

    double volume() const
    {
        return width * height * depth;
    }

    void printInfo() const
    {
        cout << "长方体底面左下角: (" << x << ", " << y << ")"
             << "  长=" << width << "  宽=" << height
             << "  高=" << depth << endl;
    }
};

void section(const string &title)
{
    cout << "\n"
         << title << "\n";
}

int main()
{
    // ---- 1) Point 测试 ----
    section("1) 二维点类 Point 测试");

    Point p1(3.0, 4.0);
    cout << "p1 = " << p1 << endl;

    Point p2(p1); // 复制构造
    cout << "p2（复制 p1）= " << p2 << endl;

    Point p3;
    p3 = p1; // 赋值运算符
    cout << "p3（赋值 p1）= " << p3 << endl;

    Point p4(1.5, 2.5);
    cout << "p4 = " << p4 << endl;

    // ---- 2) ThreeDPoint 测试 ----
    section("2) 三维点类 ThreeDPoint 测试");

    ThreeDPoint t1(1.0, 2.0, 3.0);
    ThreeDPoint t2(4.0, 6.0, 3.0);
    cout << "t1 = " << t1 << endl;
    cout << "t2 = " << t2 << endl;

    double dist = t1.distance(t2);
    cout << "t1 与 t2 的距离 = " << dist << endl;

    ThreeDPoint t3(t1); // 复制构造
    cout << "t3（复制 t1）= " << t3 << endl;

    ThreeDPoint t4;
    t4 = t2; // 赋值
    cout << "t4（赋值 t2）= " << t4 << endl;

    t4.setPoint(0.0, 0.0, 0.0);
    cout << "t4 重新设置为原点 = " << t4 << endl;
    cout << "t1 到原点的距离 = " << t1.distance(t4) << endl;

    // ---- 3) Rectangle 测试 ----
    section("3) 矩形类 Rectangle 测试");

    Rectangle rect(0.0, 0.0, 5.0, 3.0);
    rect.printInfo();
    cout << "矩形面积 = " << rect.area() << endl;

    // 测试坐标点关系
    struct TestPt
    {
        double px, py;
    };
    TestPt pts[] = {{2.5, 1.5}, {0.0, 1.0}, {6.0, 2.0}, {5.0, 3.0}};
    for (auto &tp : pts)
    {
        cout << "点 (" << tp.px << ", " << tp.py << ") -> "
             << rect.relationStr(tp.px, tp.py) << endl;
    }

    Rectangle rect2;
    rect2 = rect; // 赋值
    cout << "rect2（赋值 rect）: ";
    rect2.printInfo();

    Rectangle rect3(rect); // 复制构造
    cout << "rect3（复制 rect）: ";
    rect3.printInfo();

    // ---- 4) Line 测试 ----
    section("4) 线段类 Line 测试");

    ThreeDPoint lp1(0.0, 0.0, 0.0);
    ThreeDPoint lp2(3.0, 4.0, 0.0);
    Line line1(lp1, lp2);
    line1.display();
    cout << "线段长度 = " << line1.length() << endl;

    ThreeDPoint lp3(1.0, 1.0, 1.0);
    ThreeDPoint lp4(4.0, 5.0, 1.0);
    Line line2(lp3, lp4);
    line2.display();
    cout << "线段长度 = " << line2.length() << endl;

    // ---- 5) Cuboid 测试 ----
    section("5) 长方体类 Cuboid 测试");

    Cuboid cub(0.0, 0.0, 4.0, 3.0, 2.0);
    cub.printInfo();
    cout << "长方体表面积 = " << cub.surfaceArea() << endl;
    cout << "长方体体积   = " << cub.volume() << endl;

    Cuboid cub2(cub); // 复制构造
    cout << "\ncub2（复制 cub）:\n";
    cub2.printInfo();
    cout << "cub2 表面积 = " << cub2.surfaceArea() << endl;
    cout << "cub2 体积   = " << cub2.volume() << endl;

    Cuboid cub3;
    cub3 = cub; // 赋值
    cout << "\ncub3（赋值 cub）:\n";
    cub3.printInfo();
    cout << "cub3 表面积 = " << cub3.surfaceArea() << endl;
    cout << "cub3 体积   = " << cub3.volume() << endl;

    return 0;
}

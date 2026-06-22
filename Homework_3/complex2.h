#include <iostream>
#include <cmath>
using namespace std;

class complex2
{
    double real; // 实部
    double imag; // 虚部
public:
    complex2(double r = 0.0, double i = 0.0); // 构造函数
    complex2(const complex2 &);               // 复制构造函数
    double getReal() const;                   // 取实部
    double getImag() const;                   // 取虚部
    double modulus() const;                   // 取模值
    complex2 &operator=(const complex2 &);    // 重载赋值=

    // 完善补充运算符重载友元函数的声明
    friend complex2 operator+(const complex2 &, const complex2 &); // 重载+，实现复数的加运算
    friend complex2 operator-(const complex2 &, const complex2 &); // 重载-，实现复数的减运算
    friend complex2 operator*(const complex2 &, const complex2 &); // 重载*,  实现复数的乘运算
    friend complex2 operator/(const complex2 &, const complex2 &); // 重载/，实现复数的除法运算
    friend complex2 &operator+=(complex2 &, const complex2 &);     // 重载+=，实现复数的+=运算
    friend complex2 &operator-=(complex2 &, const complex2 &);     // 重载-=，实现复数的-=运算
    friend complex2 &operator*=(complex2 &, const complex2 &);     // 重载*=，实现复数的*=运算
    friend complex2 &operator/=(complex2 &, const complex2 &);     // 重载/=，实现复数的/=运算
    friend bool operator==(complex2 &, const complex2 &);          // 重载==,比较复数是否相等(实部相等且虚部相等)
    friend bool operator>(complex2 &, const complex2 &);           // 重载>，实现复数的模值的>比较运算
    friend complex2 operator-(complex2 &);                         // 重载-，实现复数的符号取反，-(a+bi)=-a-bi
    friend complex2 operator++(complex2 &);                        // 重载复数的前缀++运算，实部虚部均加 1
    friend complex2 operator++(complex2 &, int);                   // 重载复数的后缀++运算，实部虚部均加 1

    // 完善补充<<和>>重载友元函数的声明
    friend ostream &operator<<(ostream &, const complex2 &);
    friend istream &operator>>(istream &, complex2 &);
};

complex2::complex2(double r, double i)
{
    real = r;
    imag = i;
}

complex2::complex2(const complex2 &other)
{
    real = other.real;
    imag = other.imag;
}

double complex2::getReal() const
{
    return real;
}

double complex2::getImag() const
{
    return imag;
}

double complex2::modulus() const
{
    return (sqrt(real * real + imag * imag));
}

complex2 &complex2::operator=(const complex2 &other)
{
    real = other.real;
    imag = other.imag;
    return *this;
}

complex2 operator+(const complex2 &c1, const complex2 &c2)
{
    return complex2(c1.real + c2.real, c1.imag + c2.imag);
}

complex2 operator-(const complex2 &c1, const complex2 &c2)
{
    return complex2(c1.real - c2.real, c1.imag - c2.imag);
}

complex2 operator*(const complex2 &c1, const complex2 &c2)
{
    double r = c1.real * c2.real - c1.imag * c2.imag;
    double i = c1.imag * c2.real + c1.real * c2.imag;
    return complex2(r, i);
}

complex2 operator/(const complex2 &c1, const complex2 &c2)
{
    double denom = c2.real * c2.real + c2.imag * c2.imag;
    double r = (c1.real * c2.real + c1.imag * c2.imag) / denom;
    double i = (c1.imag * c2.real - c1.real * c2.imag) / denom;
    return complex2(r, i);
}

complex2 &operator+=(complex2 &com, const complex2 &other)
{
    com.real += other.real;
    com.imag += other.imag;
    return com;
}

complex2 &operator-=(complex2 &com, const complex2 &other)
{
    com.real -= other.real;
    com.imag -= other.imag;
    return com;
}

complex2 &operator*=(complex2 &com, const complex2 &other)
{
    com.real = com.real * other.real - com.imag * other.imag;
    com.imag = com.imag * other.real + com.real * other.imag;
    return com;
}

complex2 &operator/=(complex2 &com, const complex2 &other)
{
    com.real = (com.real * other.real + com.imag * other.imag) / (other.real * other.real + other.imag * other.imag);
    com.imag = (com.imag * other.real - com.real * other.imag) / (other.real * other.real + other.imag * other.imag);
    return com;
}

bool operator==(complex2 &com, const complex2 &other)
{
    return (com.real == other.real && com.imag == other.imag);
}

bool operator>(complex2 &com, const complex2 &other)
{
    return ((com.real * com.real + com.imag * com.imag) > (other.real * other.real + other.imag * other.imag));
}

complex2 operator-(complex2 &com)
{
    return complex2(-com.real, -com.imag);
}

complex2 operator++(complex2 &com)
{
    com.real += 1;
    com.imag += 1;
    return com;
}

complex2 operator++(complex2 &com, int)
{
    complex2 temp = com;
    com.real += 1;
    com.imag += 1;
    return temp;
}

ostream &operator<<(ostream &cout, const complex2 &com)
{
    cout << com.real << "+" << com.imag << "j";
    return cout;
}

istream &operator>>(istream &cin, complex2 &com)
{
    cin >> com.real >> com.imag;
    return cin;
}

#include <iostream>
#include <cmath>
using namespace std;

class complex1
{
    double real; // 实部
    double imag; // 虚部
public:
    complex1(double r = 0.0, double i = 0.0); // 构造函数
    complex1(const complex1 &);               // 复制构造函数
    complex1 operator+(const complex1 &);     // 重载+，实现复数的加运算
    complex1 operator-(const complex1 &);     // 重载-，实现复数的减运算
    complex1 operator*(const complex1 &);     // 重载*,  实现复数的乘运算
    complex1 operator/(const complex1 &);     // 重载/，实现复数的除法运算
    complex1 &operator+=(const complex1 &);   // 重载+=，实现复数的+=运算
    complex1 &operator-=(const complex1 &);   // 重载-=，实现复数的-=运算
    complex1 &operator*=(const complex1 &);   // 重载*=，实现复数的*=运算
    complex1 &operator/=(const complex1 &);   // 重载/=，实现复数的/=运算
    complex1 &operator=(const complex1 &);    // 重载赋值=
    complex1 operator++();                    // 重载复数的前缀++运算，实部虚部均加 1
    complex1 operator++(int);                 // 重载复数的后缀++运算，实部虚部均加 1
    bool operator==(const complex1 &) const;  // 重载==,比较复数是否相等(实部相等且虚部相等)
    bool operator>(const complex1 &) const;   // 重载>，实现复数的模值的>比较运算
    complex1 operator-() const;               // 重载-，实现复数的符号取反，-(a+bi)=-a-bi
    double getReal() const;                   // 取实部
    double getImag() const;                   //  取虚部
    double modulus() const;                   // 取模值
    // 完善补充<<和>>重载的友元函数声明
    friend ostream &operator<<(ostream &, const complex1 &);
    friend istream &operator>>(istream &, complex1 &);
};

complex1::complex1(double r, double i)
{
    real = r;
    imag = i;
}

complex1::complex1(const complex1 &other)
{
    real = other.real;
    imag = other.imag;
}

complex1 complex1::operator+(const complex1 &other)
{
    complex1 result = *this;
    result.real += other.real;
    result.imag += other.imag;
    return result;
}

complex1 complex1::operator-(const complex1 &other)
{
    complex1 result = *this;
    result.real -= other.real;
    result.imag -= other.imag;
    return result;
}

complex1 complex1::operator*(const complex1 &other)
{
    complex1 result = *this;
    result.real = real * other.real - imag * other.imag;
    result.imag = imag * other.real + real * other.imag;
    return result;
}

complex1 complex1::operator/(const complex1 &other)
{
    complex1 result = *this;
    result.real = (real * other.real + imag * other.imag) / (other.real * other.real + other.imag * other.imag);
    result.imag = (imag * other.real - real * other.imag) / (other.real * other.real + other.imag * other.imag);
    return result;
}

complex1 &complex1::operator+=(const complex1 &other)
{
    real += other.real;
    imag += other.imag;
    return *this;
}

complex1 &complex1::operator-=(const complex1 &other)
{
    real -= other.real;
    imag -= other.imag;
    return *this;
}

complex1 &complex1::operator*=(const complex1 &other)
{
    real = real * other.real - imag * other.imag;
    imag = imag * other.real + real * other.imag;
    return *this;
}

complex1 &complex1::operator/=(const complex1 &other)
{
    real = (real * other.real + imag * other.imag) / (other.real * other.real + other.imag * other.imag);
    imag = (imag * other.real - real * other.imag) / (other.real * other.real + other.imag * other.imag);
    return *this;
}

complex1 &complex1::operator=(const complex1 &other)
{
    real = other.real;
    imag = other.imag;
    return *this;
}

complex1 complex1::operator++()
{
    real += 1;
    imag += 1;
    return *this;
}

complex1 complex1::operator++(int)
{
    complex1 temp = *this;
    real += 1;
    imag += 1;
    return temp;
}

bool complex1::operator==(const complex1 &other) const
{
    return (real == other.real && imag == other.imag);
}

bool complex1::operator>(const complex1 &other) const
{
    return (real * real + imag * imag > other.real * other.real + other.imag * other.imag);
}

complex1 complex1::operator-() const
{
    complex1 result = *this;
    result.real = -real;
    result.imag = -imag;
    return result;
}

double complex1::getReal() const
{
    return real;
}

double complex1::getImag() const
{
    return imag;
}

double complex1::modulus() const
{
    return (sqrt(real * real + imag * imag));
}

ostream &operator<<(ostream &cout, const complex1 &com)
{
    cout << com.real << "+" << com.imag << "j";
    return cout;
}

istream &operator>>(istream &cin, complex1 &com)
{
    cin >> com.real >> com.imag;
    return cin;
}

#include <iostream>
#include <cmath>
#include <random>
#include <cstdlib>
#include <ctime>
using namespace std;

int gcd(int a, int b)
{
    return b == 0 ? std::abs(a) : gcd(b, a % b);
}

class MyFraction
{
    int Numerator;                // 分子
    int Denominator;              // 分母
    void reduction();             // 约分
    void makeCommond(MyFraction); // 将当前分数改为与形参分数通分的形式
public:
    MyFraction(int m, int d);
    MyFraction add(MyFraction); // 分数相加，不改变加数值，返回相加后的值
    MyFraction sub(MyFraction); // 分数相减，不改变减数和被减数，返回差值
    MyFraction mul(MyFraction); // 分数相乘，不改变乘数值，返回乘积值
    MyFraction div(MyFraction); // 分数相除，不改变减数和被减数，返回商值
    void display();             // 显示分数，格式 1/3，如有负号显示在分子
    double ToDouble();          // 输出分数的实数值
};

MyFraction::MyFraction(int n, int d)
{
    int Num, Den;
    if (d == 0)
    {
        Den = 1;
        Num = n;
        cout << "输入分母为零，已自动修正为1" << endl;
    }
    else if (d < 0)
    {
        Num = -n;
        Den = -d;
        cout << "输入分母为负数，已自动修正" << endl;
    }
    else
    {
        Den = d;
        Num = n;
    }
    Numerator = Num;
    Denominator = Den;
}

void MyFraction::reduction()
{
    int common = gcd(Numerator, Denominator);
    Numerator /= common;
    Denominator /= common;
    if (Denominator < 0)
    {
        Numerator = -Numerator;
        Denominator = -Denominator;
    }
}

void MyFraction::makeCommond(MyFraction f)
{
    int commonDenomiator = Denominator * f.Denominator / gcd(Denominator, f.Denominator);
    int factor = commonDenomiator / Denominator;
    Numerator = Numerator * factor;
    Denominator = commonDenomiator;
}

MyFraction MyFraction::add(MyFraction f)
{
    MyFraction result = *this;
    int commonD = Denominator * f.Denominator / gcd(Denominator, f.Denominator);

    result.Numerator = result.Numerator * (commonD / result.Denominator) + f.Numerator * (commonD / f.Denominator);
    result.Denominator = commonD;
    result.reduction();
    cout << "(";
    this->display();
    cout << ") + (";
    f.display();
    cout << ") = (";
    result.display();
    cout << ")" << std::endl;
    return result;
}

MyFraction MyFraction::sub(MyFraction f)
{
    MyFraction result = *this;
    int commonD = Denominator * f.Denominator / gcd(Denominator, f.Denominator);

    result.Numerator = result.Numerator * (commonD / result.Denominator) - f.Numerator * (commonD / f.Denominator);
    result.Denominator = commonD;
    result.reduction();
    cout << "(";
    this->display();
    cout << ") - (";
    f.display();
    cout << ") = (";
    result.display();
    cout << ")" << std::endl;
    return result;
}

MyFraction MyFraction::mul(MyFraction f)
{
    MyFraction result = *this;
    result.Numerator = result.Numerator * f.Numerator;
    result.Denominator = result.Denominator * f.Denominator;
    result.reduction();
    cout << "(";
    this->display();
    cout << ") * (";
    f.display();
    cout << ") = (";
    result.display();
    cout << ")" << std::endl;
    return result;
}

MyFraction MyFraction::div(MyFraction f)
{
    MyFraction result = *this;
    result.Numerator = result.Numerator * f.Denominator;
    result.Denominator = result.Denominator * f.Numerator;
    result.reduction();
    cout << "(";
    this->display();
    cout << ") / (";
    f.display();
    cout << ") = (";
    result.display();
    cout << ")" << std::endl;
    return result;
}

void MyFraction::display()
{
    cout << Numerator << "/" << Denominator;
}

double MyFraction::ToDouble()
{
    return static_cast<double>(Numerator) / Denominator;
}

MyFraction fractions[] = {
    MyFraction(1, 3),
    MyFraction(1, 6),
    MyFraction(2, 4),
    MyFraction(4, 15),
    MyFraction(5, 9),
    MyFraction(1, 8)};

int main()
{
    MyFraction f1(1, 15);
    fractions[0].add(fractions[1]);
    fractions[0].add(f1);
    fractions[1].sub(fractions[5]);
    fractions[3].sub(fractions[2]);
    fractions[5].mul(fractions[2]);
    fractions[3].mul(fractions[4]);
    fractions[0].div(fractions[4]);
    fractions[2].div(fractions[1]);
}

int num[] = {1, 2, 3};
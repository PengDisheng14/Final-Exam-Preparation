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
    MyFraction(int = 1, int = 1);
    MyFraction add(MyFraction);          // 分数相加，不改变加数值，返回相加后的值
    MyFraction sub(MyFraction);          // 分数相减，不改变减数和被减数，返回差值
    MyFraction mul(MyFraction);          // 分数相乘，不改变乘数值，返回乘积值
    MyFraction div(MyFraction);          // 分数相除，不改变减数和被减数，返回商值
    void display();                      // 显示分数，格式1/3，如有负号显示在分子
    double ToDouble();                   // 输出分数的实数值
    void myadd(const MyFraction &);      // 分数值自加，本周作业添加
    void mysub(const MyFraction &);      // 分数值自减，本周作业添加
    void mymul(const MyFraction &);      // 分数值自乘，本周作业添加
    void mydiv(const MyFraction &);      // 分数值自除，本周作业添加
    MyFraction reciprocal();             // 求当前分数的倒数, 本周作业添加
    bool equal(MyFraction &);            // 比较两个分数的是否相等，本周作业添加
    bool greaterThan(MyFraction &);      // 比较两个分数值大小，本周作业添加
    void inputFraction();                // 读取键盘输入的分子分母，实现输入，本周作业添加
    MyFraction(const MyFraction &other); // 拷贝构造函数，参数是同类对象的 const 引用
    ~MyFraction();                       // 析构函数
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
    else if (Denominator == 0)
    {
        cout << "分母为零，在约分过程中已自动修正为1" << endl;
        Denominator = 1;
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
    reduction();
    cout << Numerator << "/" << Denominator;
}

double MyFraction::ToDouble()
{
    return static_cast<double>(Numerator) / Denominator;
}

void MyFraction::myadd(const MyFraction &f)
{
    int commonD = Denominator * f.Denominator / gcd(Denominator, f.Denominator);

    Numerator = Numerator * (commonD / Denominator) + f.Numerator * (commonD / f.Denominator);
    Denominator = commonD;
    reduction();
}

void MyFraction::mysub(const MyFraction &f)
{
    int commonD = Denominator * f.Denominator / gcd(Denominator, f.Denominator);

    Numerator = Numerator * (commonD / Denominator) - f.Numerator * (commonD / f.Denominator);
    Denominator = commonD;
    reduction();
}

void MyFraction::mymul(const MyFraction &f)
{
    Numerator = Numerator * f.Numerator;
    Denominator = Denominator * f.Denominator;
    reduction();
}

void MyFraction::mydiv(const MyFraction &f)
{
    Numerator = Numerator * f.Denominator;
    Denominator = Denominator * f.Numerator;
    reduction();
}

MyFraction MyFraction::reciprocal()
{
    MyFraction temp(Denominator, Numerator);
    temp.reduction();
    return temp;
}

bool MyFraction::equal(MyFraction &f)
{
    return Numerator * f.Denominator == Denominator * f.Numerator;
}

bool MyFraction::greaterThan(MyFraction &f)
{
    return Numerator * f.Denominator > Denominator * f.Numerator;
}

void MyFraction::inputFraction()
{
    int N, D;
    cout << "请分别键入分子、分母值：";
    cin >> N >> D;
    *this = MyFraction(N, D);
}

MyFraction::MyFraction(const MyFraction &other) : Numerator(other.Numerator), Denominator(other.Denominator)
{
    cout << "拷贝构造函数调用" << endl;
}

MyFraction::~MyFraction()
{
    // cout << "析构函数调用" << endl;
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
    for (int m = 0; m < 6; m++)
    {
        fractions[m].display();
        cout << '\t' << "求倒数结果为：" << '\t';
        fractions[m] = fractions[m].reciprocal();
        fractions[m].display();
        cout << endl;
    }
}
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// 货物基类
class goods
{
private:
    double price;      // 单价
    int num;           // 数量
    double totalPrice; // 总价
public:
    goods(double p = 0, int n = 0) : price(p), num(n)
    {
        // 题目 1：完善构造函数（5 分）
        totalPrice = price * num;
    }
    // 比较货物总价
    bool operator<(const goods &g2) const
    {
        // 题目 2：完善运算符重载（5 分）
        if (totalPrice < g2.totalPrice)
            return true;
        else
            return false;
    }
    friend ostream &operator<<(ostream &os, const goods &g)
    {
        os << g.price << " " << g.num << " " << g.totalPrice;
        return os;
    }
};
// 派生类 1：水果
class fruit : public goods
{
private:
    string name;
    string unit;

public:
    // 题目 3：在类内添加 fruit 的构造函数（10 分）
    fruit(const string &n, const string &u, double p, int num);
    // 题目 4：在类内完成<<运算符重载（15 分）
    ostream &operator<<(ostream &os)
    {
        os << "name:" << name << "\t" << "unit:" << unit << endl;
        return os;
    }
};

fruit::fruit(const string &n, const string &u, double p, int num) : goods(p, num)
{
    name = n;
    unit = u;
}
// 定义顺序栈类
// 不考虑入栈出栈时空栈/满栈情况
template <class T>
class stack
{
private:
    T *pArr;
    int size;
    int top;

public:
    stack(int size)
    {
        top = size;
        // 题目 5：完善构造函数的定义（5 分）。
    }
    ~stack()
    {
        delete[] pArr;
    }
    void push(const T &);
    T &pop();
};
// 题目 6：完成入栈函数的类外定义（10 分）
// 题目 7：完成出栈函数的类外定义（10 分）
template <class T>
T &selectMaxLessThanBenchmark(const T &benchmark, T *arr, int len)
{
    // 假定一定存在待查找内容
    T temp = benchmark;
    int sub = 0;
    // 题目 8：找到数组中第一个小于 benchmark 的元素。（10 分）
    // 题目 9：遍历数组，查找到小于 benchmark 的最大元素并返回之引用。（10 分）
}

int main()
{
    fruit fArray[] =
        {
            fruit("苹果", "公斤", 5.5, 20),
            fruit("香蕉", "公斤", 2.8, 15),
            fruit("葡萄", "公斤", 6.2, 10),
            fruit("西瓜", "公斤", 3.6, 95),
            fruit("甜橙", "公斤", 4.8, 20)};
    for (int i = 0; i < 5; i++)
    {
        cout << fArray[i];
    }
    cout << "===========理货===========" << endl;
    fruit Maxbench = fruit("", "", 1000, 100);
    stack<fruit> fruitArrange(5);
    for (int i = 0; i <= 5; i++)
    {
        // 题目 10：选出总价第 i+1 大的水果（5 分）
        cout << Maxbench;
        // 题目 11：将上述水果入栈（5 分）
    }
    cout << "===========出货===========" << endl;
    // 题目 12：将栈中数据出栈，并存储至文本文件中（15 分）
    return 0;
}
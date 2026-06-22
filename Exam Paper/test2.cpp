#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// 货物基类
class goods
{
protected:
    double price;      // 单价
    int num;           // 数量
    double totalPrice; // 总价
public:
    goods(double p = 0, int n = 0) : price(p), num(n)
    {
        // 题目 1：完善构造函数（5 分）
        totalPrice = p * n;
    }
    // 比较货物总价
    bool operator<(const goods &g2) const
    {
        // 题目 2：完善运算符重载（5 分）
        return totalPrice < g2.totalPrice;
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
    fruit(string st1, string st2, double d, int i) : name(st1), unit(st2), goods(d, i) {}
    // 题目 4：在类内完成<<运算符重载（15 分）
    friend ostream &operator<<(ostream &out, fruit &f)
    {
        out << f.name << " " << f.unit << " " << f.price << " " << f.num;
        return out;
    }
};

// 定义顺序栈类，不考虑入栈出栈时空栈/满栈情况
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
        pArr = new T[size];
        this->size = size;
    }
    ~stack()
    {
        delete[] pArr;
    }
    void push(const T &);
    T &pop();
};

// 题目 6：完成入栈函数的类外定义（10 分）
template <typename T>
void stack<T>::push(const T &t1)
{
    --top;
    pArr[top] = t1;
}

// 题目 7：完成出栈函数的类外定义（10 分）
template <typename T>
T &stack<T>::pop()
{
    return pArr[top++];
}

template <class T>
T &selectMaxLessThanBenchmark(const T &benchmark, T *arr, int len)
{
    // 假定一定存在待查找内容
    T temp = benchmark;
    int sub = 0;
    // 题目 8：找到数组中第一个小于 benchmark 的元素。（10 分）
    for (int i = 0; i < len; i++)
    {
        if (arr[i] < benchmark)
        {
            cout << "第" << i << "个元素是第一个小于benchmark的元素" << endl;
            break; // 找到第一个就停
        }
    }
    // 题目 9：遍历数组，查找到小于 benchmark 的最大元素并返回值引用。（10 分）
    for (int i = 0; i < len; i++)
    {
        if (arr[i] < benchmark)
        {
            sub = i;
            break;
        }
    }
    for (int i = sub + 1; i < len; i++)
    {
        if (arr[i] < benchmark && arr[i] > arr[sub])
        {
            sub = i;
        }
    }

    // 返回原数组中该元素的引用，完全不修改原数组
    return arr[sub];
}

int main()
{
    fruit fArray[] = {
        fruit("苹果", "公斤", 5.5, 20),
        fruit("香蕉", "公斤", 2.8, 15),
        fruit("葡萄", "公斤", 6.2, 10),
        fruit("西瓜", "公斤", 3.6, 95),
        fruit("甜橙", "公斤", 4.8, 20)};
    for (int i = 0; i < 5; i++)
    {
        cout << fArray[i] << endl; // 输出所有水果（方便查看）
    }
    cout << "===========理货===========" << endl;

    fruit Maxbench = fruit("", "", 1000, 100); // 基准：总价为 1000*100=100000
    stack<fruit> fruitArrange(5);              // 容量为5的栈

    // 题目 10 & 11：循环5次，依次选出总价从大到小的水果并入栈
    for (int i = 0; i < 5; i++)
    {
        // 在数组 fArray 中找出总价小于当前基准的最大水果（引用）
        fruit &selected = selectMaxLessThanBenchmark(Maxbench, fArray, 5);

        // 题目 10：输出选中的水果（即第 i+1 大的水果）
        cout << "第" << (i + 1) << "大水果: " << selected << endl;

        // 题目 11：将该水果入栈
        fruitArrange.push(selected);

        // 更新基准为当前选中的水果（下次找总价更小的）
        Maxbench = selected; // 复制一份，因为 selected 是数组元素的引用
    }

    cout << "===========出货===========" << endl;

    // 题目 12：将栈中数据出栈，并存储至文本文件
    // 先关闭之前可能以读方式打开的流，重新以写方式打开
    fstream outfile;
    outfile.open("text.txt", ios::out);
    if (!outfile)
    {
        cerr << "打开文本文件失败" << endl;
        exit(1);
    }

    // 依次出栈并写入文件（栈是后进先出，所以出栈顺序为总价从小到大）
    while (!fruitArrange.empty())
    {
        fruit f = fruitArrange.pop(); // 弹出栈顶元素（复制一份）
        outfile << f << endl;         // 利用 fruit 的 << 重载输出
    }
    outfile.close();

    cout << "数据已保存到 text.txt" << endl;
    return 0;
}
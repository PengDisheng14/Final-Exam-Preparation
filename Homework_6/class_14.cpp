// 上机实验14，考试题简化版
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class CGoods
{
    string Description;
    string No;
    int Quantity;
    double Cost;
    double Retail;
    fstream datafile;

public:
    CGoods();                                           // 从文件中读取数据进行初始化
    ~CGoods();                                          // 数据保存到文件中
    void SetParam(string, string, int, double, double); // 为类的成员数据赋值
};

// 构造函数：从 D:\mydatafile.txt 读取数据初始化成员
CGoods::CGoods()
{
    // 尝试打开文件（输入模式）
    datafile.open("D:\\mydatafile.txt", ios::in);
    if (datafile.is_open())
    {
        // 读取五个成员变量，假设文件格式为每行一个数据，或空格/换行分隔
        datafile >> Description >> No >> Quantity >> Cost >> Retail;
        datafile.close();
    }
    else
    {
        // 文件打开失败时，赋予默认值
        Description = "";
        No = "";
        Quantity = 0;
        Cost = 0.0;
        Retail = 0.0;
    }
}

// 析构函数：将成员数据保存到工程目录下的 mydatafile.txt
CGoods::~CGoods()
{
    // 打开文件（输出模式，覆盖写入）
    datafile.open("mydatafile.txt", ios::out);
    if (datafile.is_open())
    {
        // 写入五个成员变量，每个数据后换行
        datafile << Description << endl;
        datafile << No << endl;
        datafile << Quantity << endl;
        datafile << Cost << endl;
        datafile << Retail << endl;
        datafile.close();
    }
}

// SetParam：为成员数据赋值
void CGoods::SetParam(string desc, string no, int qty, double cost, double retail)
{
    Description = desc;
    No = no;
    Quantity = qty;
    Cost = cost;
    Retail = retail;
}

// 用于测试的 main 函数（题目已给出）
int main()
{
    CGoods goods;                                         // 构造函数从 D:\mydatafile.txt 读取
    goods.SetParam("绝世神功", "BOOK001", 1, 2, 9999999); // 修改成员值
    return 0;                                             // 程序结束，析构函数自动将最新数据保存到工程目录下的 mydatafile.txt
}
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

void test01()
{
    // rand() % (B - A + 1) + A
    srand(time(0));           // 初始化种子（只需一次）
    int num = rand() % 7 - 1; // -1 到 5

    int den;
    do
    {
        den = rand() % 21 - 10;
    } while (den == 0); // -10 到 10，排除0
}

void test02()
{
    cout << "以右对齐方式输出整数，域宽为10：" << endl;
    cout << setw(10) << setfill('*') << a << endl;
    cout << setw(10) << setfill('*') << b << endl;
    cout << setw(10) << setfill('*') << c << endl;

    cout << "以左对齐方式输出整数，域宽为10：" << endl;
    cout << left << setw(10) << setfill('#') << a << endl;
    cout << left << setw(10) << setfill('#') << b << endl;
    cout << left << setw(10) << setfill('#') << c << endl;

    //==========三种进制输出==========
    cout << "十六进制：" << hex << showbase << a << " " << b << " " << c << endl;
    cout << "八进制：" << oct << showbase << a << " " << b << " " << c << endl;
    cout << "十进制：" << dec << showbase << a << " " << b << " " << c << endl;

    double pi = 1000.0 / 19;
    //==========科学计数法输出==========
    cout << setfill(' ');
    cout << scientific << "pi=" << setw(14) << pi << endl;

    //==========定点格式输出==========
    cout << fixed << showpos << internal << setw(12) << setprecision(6) << pi << endl;
}

int test3()
{
    ifstream infile("info1.txt");
    if (!infile)
    {
        cerr << "无法打开文件！" << endl;
        return 1;
    }
    student Students[10];
    for (int i = 0; i < 10; i++)
    {
        infile >> Students[i].student_ID // 读取信息存放在类或结构体数组中
            >> Students[i].name >> Students[i].sex >> Students[i].age >> Students[i].address >> Students[i].score;
    }
    infile.close();

    ofstream outfile("mydatafile.txt"); // 默认 ios::out
    if (!outfile)
    {
        cerr << "打开文件失败！" << endl;
        return 1;
    }
    outfile << "Hello, file!" << endl;
    outfile.close();
}

ostream &operator<<(ostream &cout, const complex1 &com)
{
    // 注意这是友元函数，需要通过对象访问私有成员哦
    cout << com.real << "+" << com.imag << "j";
    // 注意要return哦
    return cout;
}

// 输出需要const，输入不许写哦
istream &operator>>(istream &cin, complex1 &com)
{
    cin >> com.real >> com.imag;
    return cin;
}

template <class T, int size>
ostream &operator<<(ostream &out, const Set<T, size> &s)
{
    for (int i = 0; i < s.num; i++)
    {
        out << s.elements[i] << " ";
    }
    return out;
}

// 关于提取和丢弃回车、以什么字符作间隔，来不及看了，

template <typename T>
void mySwap(T &t1, T &t2)
{
    T temp = t1;
    t1 = t2;
    t2 = temp;
}

template <typename T>
int directSearch(T arr[], int size, T key)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == key)
            return i;
    }
    return -1;
}

template <typename T>
int binarySearch(T arr[], int size, T key)
{
    int left = 0, right = size - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] > key)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}

template <typename T>
void bubbleSort(T arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                mySwap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 后两个排序的背记落实都有严重问题。
template <typename T>
void directSort(T arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int key = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] > arr[key])
            {
                mySwap(j, key);
            }
        }
        if (i != key)
        {
            mySwap(arr[i], arr[key]);
        }
    }
}

template <typename T>
void inSort(T arr[], int size)
{
    for (int i = 1; i < size; i++)
    {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
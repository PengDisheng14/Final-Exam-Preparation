#include <iostream>
#include <iomanip>
#include <random>
using namespace std;

int main()
{
    const int MAX = 65535;
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> dist(0, MAX);

    int a = dist(gen);
    int b = dist(gen);
    int c = dist(gen);

    //==========左对齐和右对齐输出==========
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
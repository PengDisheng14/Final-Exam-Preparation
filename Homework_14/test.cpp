#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

void myWrite()
{
    int n;
    cout << "请为n赋值：";
    while (!(cin >> n) || n < 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cerr << "赋值操作有误，请重新为n赋值" << endl;
    }

    srand(time(0));
    int *numbers = new int[n];
    for (int i = 0; i < n; i++)
    {
        numbers[i] = rand() % 201 - 100;
    }

    ofstream outfile("binaryfile.dat", ios::binary);
    if (!outfile)
    {
        cerr << "打开二进制文件失败" << endl;
        delete[] numbers;
        exit(1);
    }
    outfile.write((char *)numbers, n * sizeof(int));
    outfile.close();

    ofstream outfile("txtfile.txt");
    if (!outfile)
    {
        cerr << "打开文本文件失败" << endl;
        delete[] numbers;
        exit(1);
    }
    for (int i = 0; i < n; i++)
    {
        outfile << numbers[i] << endl;
    }
    outfile.close();
    delete[] numbers;
}

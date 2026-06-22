#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    // 由用户手动输入文件名，使用string避免溢出、使用get保留空格
    string filename1, filename2;
    cout << "输入源文件名：";
    getline(cin, filename1);
    cout << "输入目的文件名：";
    getline(cin, filename2);
    ifstream infile(filename1);
    ofstream outfile(filename2);
    // 判断文件是否正确打开
    if (!infile)
    {
        cerr << "open error !" << endl;
        exit(1);
    }

    while (!infile)
    {
        cout << "源文件找不到,请重新输入路径文件名:" << endl;
        infile.clear(); // 清除状态字
        cin >> filename1;
        infile.open(filename1);
    }

    if (!outfile)
    {
        cerr << "open error !" << endl;
        exit(1);
    }
    // 拷贝到目标文件中
    char ch;
    while (infile.get(ch))
    {
        outfile.put(ch);
    }

    infile.close();
    outfile.close();
    return 0;
}

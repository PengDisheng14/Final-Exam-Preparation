#include <iostream>
#include <cstring>
using namespace std;

class student
{
    char *pName;

public:
    student();                      // 默认构造函数
    student(char *pname);           // 带参数构造函数
    ~student();                     // 析构函数
    student(student &s);            // 复制构造函数
    student &operator=(student &s); // 复制赋值操作符
};

student ::student()
{
    cout << "Constructor1";
    pName = NULL;
    cout << "默认" << endl;
}

student::student(char *pname)
{
    cout << "Constructor2";
    // 若成功分配内存，则进行拷贝，而且是深拷贝
    if (pName = new char[strlen(pname) + 1])
        strcpy(pName, pname);
    cout << pName << endl;
}

student ::~student()
{
    cout << "Destructor";
    if (pName)
    {
        cout << pName << endl;
        delete[] pName;
    }
}

student::student(student &s)
{
    cout << "Copy Constructor";
    if (s.pName)
    {
        if (pName = new char[strlen(s.pName) + 1])
            // strcpy和for循环是等价的
            for (int i = 0; i <= strlen(s.pName); i++)
                pName[i] = s.pName[i];
        cout << pName << endl;
    }
    else
        pName = nullptr;
}

student &student::operator=(student &s)
{
    cout << "Copy Assign operator";
    if (this != &s)
    {
        // 如原来已分配，应先撤销，再重分配。上面的是构造，不用考虑这个问题。
        if (pName)
            delete[] pName;
        if (s.pName)
        {
            if (pName = new char[strlen(s.pName) + 1])
                for (int i = 0; i <= strlen(s.pName); i++)
                    pName[i] = s.pName[i];
            cout << pName << endl;
        }
        else
            pName = nullptr;
    }
    return *this;
}

int main(void)
{
    student s1("范英明"), s2("沈俊"), s3;
    student s4 = s1;
    s3 = s2;
    return 0;
}
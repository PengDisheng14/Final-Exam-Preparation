#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <limits>
#include <cctype>
using namespace std;

class mystring
{
    static const int CAP = 64; // 最大字符数（含 '\0'）
    char buf[CAP];

public:
    mystring() { buf[0] = '\0'; }
    mystring(const char *s)
    {
        strncpy(buf, s, CAP - 1);
        buf[CAP - 1] = '\0';
    }
    mystring(const mystring &o) { strncpy(buf, o.buf, CAP); }

    mystring &operator=(const mystring &o)
    {
        if (this != &o)
            strncpy(buf, o.buf, CAP);
        return *this;
    }

    mystring &operator=(const char *s)
    {
        strncpy(buf, s, CAP - 1);
        buf[CAP - 1] = '\0';
        return *this;
    }

    bool operator==(const mystring &o) const { return strcmp(buf, o.buf) == 0; }
    bool operator<(const mystring &o) const { return strcmp(buf, o.buf) < 0; }
    bool operator>(const mystring &o) const { return strcmp(buf, o.buf) > 0; }

    const char *c_str() const { return buf; }
    bool empty() const { return buf[0] == '\0'; }

    // 流运算符
    friend ostream &operator<<(ostream &os, const mystring &ms)
    {
        os << ms.buf;
        return os;
    }

    friend istream &operator>>(istream &is, mystring &ms)
    {
        char tmp[mystring::CAP];
        if (is >> tmp)
        {
            strncpy(ms.buf, tmp, CAP - 1);
            ms.buf[CAP - 1] = '\0';
        }
        return is;
    }
};

class student
{
    mystring id;      // 学号（关键字）
    mystring name;    // 姓名
    char sex;         // 性别 M/F
    int age;          // 年龄
    mystring address; // 家庭地址
    float cplus;      // C++ 成绩

public:
    // ---------- 构造函数 ----------
    student() : sex('M'), age(0), cplus(0.0f) {}

    student(mystring i, mystring n, char s, int a, mystring add, float c)
        : id(i), name(n), sex(s), age(a), address(add), cplus(c) {}

    // ---------- 比较（按学号） ----------
    bool operator<(student &e) { return id < e.id; }
    bool operator>(student &e) { return id > e.id; }
    bool operator==(student &e) { return id == e.id; }

    // ---------- 访问器 ----------
    float Getcplus() const { return cplus; }
    mystring getId() const { return id; }

    friend ostream &operator<<(ostream &os, const student &s)
    {
        os << "学号  : " << s.id << "\n"
           << "姓名  : " << s.name << "\n"
           << "性别  : " << s.sex << "\n"
           << "年龄  : " << s.age << "\n"
           << "地址  : " << s.address << "\n"
           << "C++成绩: " << s.cplus << "\n";
        return os;
    }

    friend istream &operator>>(istream &is, student &s)
    {
        // —— 学号 ——
        while (true)
        {
            cout << "  学号（无空格）: ";
            if (is >> s.id && !s.id.empty())
                break;
            cout << "  [错误] 学号不能为空，请重新输入。\n";
            is.clear();
            is.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // —— 姓名 ——
        while (true)
        {
            cout << "  姓名（无空格）: ";
            if (is >> s.name && !s.name.empty())
                break;
            cout << "  [错误] 姓名不能为空，请重新输入。\n";
            is.clear();
            is.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // —— 性别 ——
        while (true)
        {
            cout << "  性别（M/F）   : ";
            char c;
            if (is >> c)
            {
                c = toupper((unsigned char)c);
                if (c == 'M' || c == 'F')
                {
                    s.sex = c;
                    break;
                }
            }
            cout << "  [错误] 性别只能输入 M 或 F，请重新输入。\n";
            is.clear();
            is.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // —— 年龄 ——
        while (true)
        {
            cout << "  年龄（1-150） : ";
            if (is >> s.age && s.age >= 1 && s.age <= 150)
                break;
            cout << "  [错误] 年龄须为 1~150 之间的整数，请重新输入。\n";
            is.clear();
            is.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // —— 地址 ——
        while (true)
        {
            cout << "  地址（无空格）: ";
            if (is >> s.address && !s.address.empty())
                break;
            cout << "  [错误] 地址不能为空，请重新输入。\n";
            is.clear();
            is.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // —— C++ 成绩 ——
        while (true)
        {
            cout << "  C++成绩（0-100）: ";
            if (is >> s.cplus && s.cplus >= 0.0f && s.cplus <= 100.0f)
                break;
            cout << "  [错误] 成绩须在 0~100 之间，请重新输入。\n";
            is.clear();
            is.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // 消耗本行剩余内容，为下一次输入做准备
        is.ignore(numeric_limits<streamsize>::max(), '\n');
        return is;
    }
};

int main()
{
    const int N = 6;
    const char *BIN_FILE = "student.dat";
    const char *TXT_FILE = "04123122_2.txt";
    const int TARGET = 4; // 第 4 条（1-based）

    cout << "========== 输入 " << N << " 条学生信息 ==========\n";
    {
        ofstream fout(BIN_FILE, ios::binary | ios::trunc);
        if (!fout)
        {
            cerr << "[错误] 无法打开文件 " << BIN_FILE << " 进行写入。\n";
            return 1;
        }

        for (int i = 0; i < N; ++i)
        {
            cout << "\n--- 第 " << (i + 1) << " 条 ---\n";
            student stu;
            cin >> stu;
            fout.write(reinterpret_cast<const char *>(&stu), sizeof(student));
            if (!fout)
            {
                cerr << "[错误] 写入第 " << (i + 1) << " 条时失败。\n";
                return 1;
            }
        }
        cout << "\n已将 " << N << " 条记录写入 " << BIN_FILE << "\n";
    }

    cout << "\n========== 读取第 " << TARGET << " 条记录 ==========\n";
    student rec4;
    {
        fstream fio(BIN_FILE, ios::binary | ios::in | ios::out);
        if (!fio)
        {
            cerr << "[错误] 无法打开文件 " << BIN_FILE << "\n";
            return 1;
        }

        // 定位：偏移 = (TARGET-1) * sizeof(student)
        streamoff offset = static_cast<streamoff>(TARGET - 1) * sizeof(student);
        fio.seekg(offset, ios::beg);
        fio.read(reinterpret_cast<char *>(&rec4), sizeof(student));
        if (!fio)
        {
            cerr << "[错误] 读取第 " << TARGET << " 条失败。\n";
            return 1;
        }
        cout << rec4;

        cout << "\n========== 修改第 " << TARGET << " 条记录 ==========\n";
        cout << "请输入修改后的信息：\n";
        cin >> rec4;

        // 回到同一偏移处写入
        fio.seekp(offset, ios::beg);
        fio.write(reinterpret_cast<const char *>(&rec4), sizeof(student));
        if (!fio)
        {
            cerr << "[错误] 回写第 " << TARGET << " 条失败。\n";
            return 1;
        }
        cout << "第 " << TARGET << " 条已更新至 " << BIN_FILE << "\n";
    }

    cout << "\n========== 导出全部记录到 " << TXT_FILE << " ==========\n";
    {
        ifstream fin(BIN_FILE, ios::binary);
        if (!fin)
        {
            cerr << "[错误] 无法读取 " << BIN_FILE << "\n";
            return 1;
        }
        ofstream txt(TXT_FILE, ios::trunc);
        if (!txt)
        {
            cerr << "[错误] 无法创建 " << TXT_FILE << "\n";
            return 1;
        }

        txt << "========== 全部学生记录 ==========\n";
        student s;
        int cnt = 0;
        while (fin.read(reinterpret_cast<char *>(&s), sizeof(student)))
        {
            ++cnt;
            txt << "\n--- 第 " << cnt << " 条 ---\n"
                << s;
        }
        cout << "共导出 " << cnt << " 条记录到 " << TXT_FILE << "\n";
    }

    cout << "\n程序结束。\n";
    return 0;
}
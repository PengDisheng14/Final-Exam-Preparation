#include <iostream>
#include <string>
using namespace std;
const int N = 64;

class mystring
{
    char str[N]; // 存放字符串的数组
    int maxsize; // 最大可用元素数，可防止数组出界
    int last;    // 已用元素最大下标,对于字符串，last 位置存放的是字符’\0’
public:
    mystring()
    {
        last = 0;
        maxsize = N;
        str[last] = '\0';
    }
    mystring(char *s);                       // 有参构造：利用字符串s 初始化，参数字符串过长时应截尾处理
    mystring(const mystring &ms);            // 复制构造函数
    int mystringlen() const { return last; } // 返回字符串长度
    mystring &operator=(const mystring &);   // 重载赋值运算符
    mystring &operator=(char *ms);           // 重载=，把C 风格字符串赋给mystring
    mystring operator+(const mystring &);    // 字符串连接至一个新的字符串
    mystring &operator+=(const mystring &);  // 字符串连接至本身
    bool operator<(const mystring &) const;  // 字符串小于比较例如cat<dog cat<cate dog<狗
    bool operator==(const mystring &) const; // 字符串等于比较  cat==cat
    bool operator>(const mystring &) const;  // 字符串大于比较  dog>cat，狗＞dog
    char &operator[](int i);
    friend istream &operator>>(istream &in, mystring &s);
    friend ostream &operator<<(ostream &in, const mystring &s);
};

mystring::mystring(char *s)
{
    maxsize = N;
    int i = 0;
    while (i < N - 1 && s[i] != '\0')
    {
        str[i] = s[i];
        i++;
    }
    str[i] = '\0';
    last = i;
}

mystring::mystring(const mystring &ms)
{
    maxsize = N;
    last = ms.last;
    for (int i = 0; i <= last; i++)
    {
        str[i] = ms.str[i];
    }
}

mystring &mystring::operator=(const mystring &ms)
{
    maxsize = N;
    last = ms.last;
    for (int i = 0; i <= last; i++)
    {
        str[i] = ms.str[i];
    }
    return *this;
}

mystring &mystring::operator=(char *ms)
{
    maxsize = N;
    int i = 0;
    while (i < N - 1 && ms[i] != '\0')
    {
        str[i] = ms[i];
        i++;
    }
    str[i] = '\0';
    last = i;
    return *this;
}

mystring mystring::operator+(const mystring &ms)
{
    mystring result = *this;
    int i = result.last;
    while (i < result.last + ms.last && i < result.maxsize - 1)
    {
        result.str[i] = ms.str[i - result.last];
        i++;
    }
    result.str[i] = '\0';
    result.last = i;
    return result;
}

mystring &mystring::operator+=(const mystring &ms)
{
    // 把参数字符串连接至我之后
    int i = last;
    while (i < last + ms.last && i < maxsize - 1)
    {
        str[i] = ms.str[i - last];
        i++;
    }
    str[i] = '\0';
    last = i;
    return *this;
}

bool mystring::operator<(const mystring &ms) const
{
    int i = 0;
    while (str[i] != '\0' && ms.str[i] != '\0')
    {
        unsigned char left = static_cast<unsigned char>(str[i]);
        unsigned char right = static_cast<unsigned char>(ms.str[i]);
        if (left != right)
            return left < right; // 依据 unsigned char 值比较
        ++i;
    }
    // 一个串结束，另一个未结束：已结束的更小
    return str[i] == '\0' && ms.str[i] != '\0';
}

// 大于比较：直接复用 operator<
bool mystring::operator>(const mystring &ms) const
{
    return ms < *this;
}

bool mystring::operator==(const mystring &ms) const
{
    if (maxsize != ms.maxsize)
        return false;
    for (int i = 0; i <= last; i++) // 包括 '\0' 位置，确保 str 完全一致
        if (str[i] != ms.str[i])
            return false;
    return true;
}

char &mystring::operator[](int i)
{
    // 防止数组越界：i 必须在 [0, last] 范围内
    if (i < 0 || i > last)
    {
        cerr << "下标越界！" << endl;
        exit(1);
    }
    return str[i];
}

istream &operator>>(istream &in, mystring &s)
{
    char buf[N];
    in >> buf; // 读取 C 风格字符串
    s = buf;   // 利用 operator=(char*) 赋值
    return in;
}

ostream &operator<<(ostream &out, const mystring &s)
{
    out << s.str;
    return out;
}

int main()
{
    char *sp1[] = {"我们", "喜欢", "学习", "C++!"};
    char *sp2[] = {"东南大学", "前工院", "大礼堂", "樱花"};
    char *sp3[] = {"AI", "deepseek", " kimi ", " ChatGPT "};
    //-----------字符串类测试代码------------------------------//
    cout << "字符串类测试对比\n-------------\n";
    bool flag = true;
    if (flag) // flag为函数形参，通过函数参数传递，值1时为string类型
        cout << "C ++  类库string运行结果：\n";
    else
        cout << "自设计mystring运行结果：\n";       // flag值为0  类型为mystring
    mystring ms1(sp1[0]), ms2(sp2[1]), ms3(sp3[3]); // sp为字符指针数组，通过函数形参传递
    mystring ms4(ms3), ms5 = ms1;
    mystring ms6, ms7;
    cout << "ms1:" << ms1 << endl;
    cout << "ms2:" << ms2 << endl;
    cout << "ms3:" << ms3 << endl;
    cout << "ms4:" << ms4 << endl;
    cout << "ms5:" << ms5 << endl;
    cout << ms3[0] << endl;
    cout << ms4[3] << endl;
    //  赋值运算符测试
    cout << "\n---赋值运算符测试----" << endl;
    ms6 = sp1[2]; // ms6赋值是返回引用，不用拷贝构造函数
    ms7 = ms4;
    cout << "ms6=sp3:" << ms6 << endl;
    cout << "ms7=ms4:" << ms7 << endl;
    // +运算符测试
    cout << "\n----+运算符测试----" << endl;
    ms5 = ms1 + ms2 + ms4;
    cout << "ms5=ms1+ms2+ms4:" << ms5 << endl;
    // +=运算符测试
    cout << "\n----+=运算符测试---" << endl;
    ms1 += ms6 += ms3;
    cout << "ms1+=ms6+=ms3:" << ms1 << endl;
    // 输入测试
    cout << "\n---->>运算符测试---:" << endl;
    cout << "请输入一串字符：";
    cin >> ms2;
    cout << "输入的内容是：" << ms2 << endl;
    //  比较运算符测试
    cout << "\n----比较运算符测试----" << endl;
    if (ms5 < ms1)
        cout << "\"" << ms5 << "\"" << "  应排在  \"" << ms1 << "\"  之前" << endl;
    else
        cout << "\"" << ms5 << "\"  应排在  \"" << ms1 << "\"  之后" << endl;
    if (ms2 > ms6)
        cout << "\"" << ms6 << "\"  应排在  \"" << ms2 << "\"  之前" << endl;
    else
        cout << "\"" << ms6 << "\"  应排在  \"" << ms2 << "\"  之后" << endl;
    if (ms6 > ms7)
        cout << "\"" << ms7 << "\"  应排在  \"" << ms6 << "\"  之前" << endl;
    else
        cout << "\"" << ms7 << "\"  应排在  \"" << ms6 << "\"  之后" << endl;
    if (ms1 == ms7)
        cout << "\"" << ms1 << "\"  与  \"" << ms7 << "\"  相同" << endl;
    else
        cout << "\"" << ms1 << "\"  与  \"" << ms7 << "\"  不同" << endl;
    ms1 = ms7;
    if (ms1 == ms7)
        cout << "\"" << ms1 << "\"  与  \"" << ms7 << "\"  相同" << endl;
    else
        cout << "\"" << ms1 << "\"  与  \"" << ms7 << "\"  不同" << endl;
    cout << "----------END mystring测试-------------\n";
}


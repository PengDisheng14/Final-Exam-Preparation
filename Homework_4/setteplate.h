#include <iostream>
using namespace std;

const int maxsize = 30;

template <class T, int size>
class Set
{
    T elements[size]; // 存放集合元素的数组，最大长度maxsize
    int num;          // 集合元素个数
public:
    Set() { num = 0; }           // 构造函数，初始化集合元素数量0
    Set(const Set &);            // 复制构造函数
    bool AddElem(T);             // 向集合内添加元素，成功返回1，溢出返回0
    bool IsMember(T) const;      // 判断一个元素是否在该集合内，是返回1
    void RemoveELem(T);          // 从集合中删除一个元素
    void Copy(const Set &);      // 将一个集合中所有元素复制到本集合中,覆盖原有元素
    bool IsEqual(const Set &);   // 判断两个集合各自包含的元素是否完全相同
    Set Intersect(const Set &);  // 求本集合和参数给定的集合的交集
    Set Unionset(const Set &);   // 求本集合和参数集合的并集，如溢出，返回最大集合
    bool IsContain(const Set &); // 判断参数集合是否包含在本集合内，是返回1
    friend ostream &operator<< <T, size>(ostream &out, const Set<T, size> &);
};

template <class T, int size>
Set<T, size>::Set(const Set<T, size> &s)
{
    for (int i = 0; i < s.num; i++)
    {
        elements[i] = s.elements[i];
    }
    num = s.num;
}

template <class T, int size>
bool Set<T, size>::AddElem(T add)
{
    if (num == size)
        return 0;
    else
    {
        elements[num++] = add;
        return 1;
    }
}

template <class T, int size>
bool Set<T, size>::IsMember(T ism) const
{
    for (int i = 0; i < num; i++)
    {
        if (elements[i] == ism)
            return 1;
    }
    return 0;
}

template <class T, int size>
void Set<T, size>::RemoveELem(T tor)
{
    int newnum = 0;
    for (int i = 0; i < num; i++)
    {
        if (elements[i] != tor)
            elements[newnum++] = elements[i];
    }
    num = newnum;
}

template <class T, int size>
void Set<T, size>::Copy(const Set<T, size> &s)
{
    for (int i = 0; i < s.num; i++)
    {
        elements[i] = s.elements[i];
    }
    num = s.num;
}

template <class T, int size>
bool Set<T, size>::IsEqual(const Set<T, size> &s)
{
    if (num != s.num)
        return 0;
    for (int i = 0; i < num; ++i)
        if (!s.IsMember(elements[i]))
            return 0;
    return 1;
}

template <class T, int size>
Set<T, size> Set<T, size>::Intersect(const Set<T, size> &s)
{
    Set<T, size> result;
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < s.num; j++)
        {
            if (elements[i] == s.elements[j])
            {
                result.elements[result.num++] = elements[i];
            }
        }
    }
    return result;
}

template <class T, int size>
Set<T, size> Set<T, size>::Unionset(const Set<T, size> &s)
{
    Set<T, size> result = *this;
    for (int j = 0; j < s.num; ++j)
    {
        if (!result.IsMember(s.elements[j]))
        { // 未出现则添加
            if (result.num == size)
                return result; // 溢出时返回当前结果
            result.elements[result.num++] = s.elements[j];
        }
    }
    return result;
}

template <class T, int size>
bool Set<T, size>::IsContain(const Set<T, size> &s)
{
    for (int i = 0; i < s.num; ++i)
        if (!IsMember(s.elements[i]))
            return 0;
    return 1;
}

template <class T, int size>
ostream &operator<< <T, size>(ostream &out, const Set<T, size> &s)
{
    for (int i = 0; i < s.num; i++)
    {
        out << s.elements[i] << " ";
    }
    return out;
}

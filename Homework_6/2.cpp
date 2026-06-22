#include <iostream>
using namespace std;

template <typename T, int size>
class seqlist
{
    T slist[size]; // 存放顺序表的数组
    int Maxsize;   // 最大可容纳项数
    int last;      // 已存表项的最后位置
public:
    seqlist()
    {
        // 初始化为空表
        last = -1;
        Maxsize = size;
    }
    int Length() const { return last + 1; }       // 计算表长度
    int Find(const T &x) const;                   // 寻找x在表中位置（下标）
    bool IsIn(const T &x) const;                  // 判断x是否在表中
    bool Insert(const T &x, int i);               // x插入到列表中第i个位置处（下标）
    bool Remove(const T &x);                      // 删除x
    bool IsEmpty() { return last == -1; }         // 判断表是否空
    bool IsFull() { return last == Maxsize - 1; } // 判断表是否满
    T &operator[](int i);                         // 重载下标运算符[]
    void clear() { last = -1; }
    friend ostream &operator<< <T, size>(ostream &out, const seqlist<T, size> &list); // 输出表中内容，每10个一行

    void Reverse();                  // 顺序表反向（在当前表中操作表反向，不借助新表）
    void DownInsertSort();           // 实现降序排序的直接插入排序函数
    void DownBinaryInsertSort();     // 实现降序排序的折半插入排序函数
    void DownBubbleSort();           // 实现降序排序的冒泡排序函数
    void DownSelectSort();           // 实现降序排序的选择排序函数
    int DownBinarySearch(const T &); // 实现折半查找的函数
};

template <typename T, int size>
int seqlist<T, size>::Find(const T &x) const
{
    for (int i = 0; i <= last; i++)
    {
        if (slist[i] == x)
            return i;
    }
    return -1;
}

template <typename T, int size>
bool seqlist<T, size>::IsIn(const T &x) const
{
    for (int i = 0; i <= last; i++)
    {
        if (slist[i] == x)
            return 1;
    }
    return 0;
}

template <typename T, int size>
bool seqlist<T, size>::Insert(const T &x, int i)
{
    if (IsFull())
        return 0;
    if (i < 0 || i > last + 1)
        return false;

    for (int j = last + 1; j > i; j--)
    {
        slist[j] = slist[j - 1];
    }
    slist[i] = x;
    last++; // 长度更新
    return 1;
}

template <typename T, int size>
bool seqlist<T, size>::Remove(const T &x)
{
    int newLast = -1;
    for (int i = 0; i <= last; i++) // 我们这里last是下标，不是size长度
    {
        if (slist[i] != x)
            slist[++newLast] = slist[i];
    }
    bool found = (newLast != last);
    last = newLast;
    return found;
}

template <typename T, int size>
T &seqlist<T, size>::operator[](int i)
{
    return slist[i];
}

template <typename T, int size>
ostream &operator<< <T, size>(ostream &out, const seqlist<T, size> &list)
{
    for (int i = 0; i <= list.last; i++)
    {
        out << list.slist[i] << " ";
        if ((i + 1) % 10 == 0)
            out << endl;
    }
    if (list.last % 10 != 0)
        out << endl;
    return out;
}

template <typename T>
void swap(T &t1, T &t2)
{
    T temp = t1;
    t1 = t2;
    t2 = temp;
}

template <typename T, int size>
void seqlist<T, size>::Reverse()
{
    int left = 0, right = last;
    while (left < right)
    {
        swap(slist[left], slist[right]);
        left++;
        right--;
    }
}

template <typename T, int size>
void seqlist<T, size>::DownInsertSort()
{
    for (int i = 1; i < last + 1; i++)
    {
        T key = slist[i];
        int j = i - 1;
        while (j >= 0 && slist[j] < key)
        {
            slist[j + 1] = slist[j];
            j--;
        }
        slist[j + 1] = key;
    }
}

template <typename T, int size>
void seqlist<T, size>::DownBinaryInsertSort()
{
    int n = last + 1;
    for (int i = 1; i < n; i++)
    {
        T key = slist[i];
        int left = 0, right = i - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (slist[mid] < key) // 降序：mid 小于 key 时，key 应插在左边
                right = mid - 1;
            else
                left = mid + 1;
        }
        for (int j = i - 1; j >= left; j--)
            slist[j + 1] = slist[j];
        slist[left] = key;
    }
}

template <typename T, int size>
void seqlist<T, size>::DownBubbleSort()
{
    int size = last + 1;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (slist[j] < slist[j + 1])
            {
                swap(slist[j], slist[j + 1]);
            }
        }
    }
}

template <typename T, int size>
void seqlist<T, size>::DownSelectSort()
{
    int size = last + 1;
    for (int i = 0; i < size - 1; i++)
    {
        int key = i;
        for (int j = i + 1; j < size; j++)
        {
            if (slist[j] > slist[key])
            {
                key = j;
            }
        }
        if (key != i)
        {
            swap(slist[i], slist[key]);
        }
    }
}

template <typename T, int size>
int seqlist<T, size>::DownBinarySearch(const T &t)
{
    int left = 0, right = last;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (slist[mid] == t)
            return mid;
        else if (slist[mid] > t)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}
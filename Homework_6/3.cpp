#include <iostream>
using namespace std;

template <typename T>
void mySwap(T &t1, T &t2)
{
    T temp = t1;
    t1 = t2;
    t2 = temp;
}

// 顺序查找
template <typename T>
int Search1(T arr[], int size, T key)
{
    for (int i = 0; i < size; i++)
    {
        if (key == arr[i])
            return i;
    }
    return -1;
}

// 对半查找
template <typename T>
int Search2(T arr[], int size, T key)
{
    int right = size - 1, left = 0;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (key == arr[mid])
            return mid;
        else if (key > arr[mid])
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// 冒泡排序
template <typename T>
void bubbleSort(T arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                mySwap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 选择排序，降序
template <typename T>
void selectSort(T arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int key = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] > arr[key]) // key小则降
            {
                key = j;
            }
        }
        if (key != i)
        {
            mySwap(arr[i], arr[key]);
        }
    }
}

// 直接插入排序，降序
template <typename T>
void inSort(T arr[], int size)
{
    for (int i = 1; i < size; i++)
    {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] < key) // key小则升
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
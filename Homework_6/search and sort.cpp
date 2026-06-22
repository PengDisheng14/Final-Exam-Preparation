#include <iostream>
using namespace std;

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

// 后两个排序都有严重问题。
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
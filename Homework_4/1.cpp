#include <iostream>
#include <string>
#include <utility>
using namespace std;

template <typename T>
std::pair<T, T> maxminofArray(T arr[], int len)
{
    T max = arr[0], min = arr[0];
    for (int i = 0; i < len; i++)
    {
        if (arr[i] > max)
            max = arr[i];
        if (arr[i] < min)
            min = arr[i];
    }
    return {max, min};
}

template <typename T>
void arrayPrint(T arr[], int len)
{
    for (int i = 0; i < len; i++)
        cout << arr[i] << ' ';
}

template <typename T>
int deleteArray(T arr[], int &len, const T &toDelete)
{
    int newLen = 0; // 新数组的有效长度（也是下一个要放置元素的位置索引）
    int deletecount = 0;
    for (int i = 0; i < len; i++)
    {
        if (arr[i] == toDelete)
        {
            ++deletecount;
        }
        else
        {
            arr[newLen++] = arr[i]; // 将保留的元素向前移动到 newLen 位置
        }
    }
    len = newLen; // 更新数组的实际长度
    return deletecount;
}

int main()
{
    double arr1[] = {8.1, 2.2, 3.9, 9.3, 5.4, 6.5, 7.8};
    int arr2[] = {101, 204, 300, 18, 57, 77, 99, 23, 18};
    char arr3[] = "Program of template";
    string arr4[] = {"cat", "dog", "fox", "ox", "hen", "lion"};

    arrayPrint(arr1, 7);
    cout << endl;
    auto result1 = maxminofArray(arr1, 7);
    cout << "Max: " << result1.first << ", Min: " << result1.second << endl;
    cout << endl;

    int lenArr2 = 9;
    arrayPrint(arr2, lenArr2);
    cout << endl;
    auto result2 = maxminofArray(arr2, lenArr2);
    cout << "Max: " << result2.first << ", Min: " << result2.second << endl;
    cout << "delete count:" << deleteArray(arr2, lenArr2, 18) << endl;
    arrayPrint(arr2, lenArr2);
    cout << endl
         << endl;

    int lenArr3 = 19;
    arrayPrint(arr3, lenArr3);
    cout << endl;
    auto result3 = maxminofArray(arr3, lenArr3);
    cout << "Max: " << result3.first << ", Min: " << result3.second << endl;
    cout << "delete count:" << deleteArray(arr3, lenArr3, 'e') << endl;
    arrayPrint(arr3, lenArr3);
    cout << endl
         << endl;

    int lenArr4 = 6;
    arrayPrint(arr4, lenArr4);
    cout << endl;
    auto result4 = maxminofArray(arr4, lenArr4);
    cout << "Max: " << result4.first << ", Min: " << result4.second << endl;
    cout << "delete count:" << deleteArray(arr4, lenArr4, string("fox")) << endl;
    arrayPrint(arr4, lenArr4);
    cout << endl;
}
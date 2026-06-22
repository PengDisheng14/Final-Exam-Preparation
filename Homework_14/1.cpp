#include <iostream>
#include <fstream>
#include <cstdlib>   // for rand, srand
#include <ctime>     // for time
#include <algorithm> // for std::sort

int main()
{
    // ----------------- 第一部分 -----------------
    int n;
    std::cout << "请输入整数个数 n: ";
    std::cin >> n;

    // 输入合法性检查
    if (n <= 0)
    {
        std::cerr << "n 必须是正整数！" << std::endl;
        return 1;
    }

    // 生成随机数种子
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // 动态分配数组，存储 n 个随机数
    int *numbers = new int[n];
    for (int i = 0; i < n; ++i)
    {
        // 生成 [-100, 100] 范围内的随机整数
        numbers[i] = std::rand() % 201 - 100;
    }

    // 以二进制方式写入文件 binaryfile.dat
    std::ofstream binOut("binaryfile.dat", std::ios::binary);
    if (!binOut)
    {
        std::cerr << "无法打开 binaryfile.dat 进行写入！" << std::endl;
        delete[] numbers;
        return 1;
    }

    // 写入 n 的值
    binOut.write(reinterpret_cast<const char *>(&n), sizeof(n));
    // 写入 n 个整数
    binOut.write(reinterpret_cast<const char *>(numbers), n * sizeof(int));

    binOut.close();
    std::cout << "已成功生成 " << n << " 个随机数并写入 binaryfile.dat" << std::endl;

    // ----------------- 第二部分 -----------------
    // 重新打开二进制文件进行读取
    std::ifstream binIn("binaryfile.dat", std::ios::binary);
    if (!binIn)
    {
        std::cerr << "无法打开 binaryfile.dat 进行读取！" << std::endl;
        delete[] numbers;
        return 1;
    }

    // 读取第一个整数 n
    int readN;
    binIn.read(reinterpret_cast<char *>(&readN), sizeof(readN));
    if (!binIn || readN <= 0)
    {
        std::cerr << "读取 n 失败或 n 无效！" << std::endl;
        binIn.close();
        delete[] numbers;
        return 1;
    }

    // 动态声明数组，大小为 readN
    int *data = new int[readN];
    // 读取剩余的数据到数组中
    binIn.read(reinterpret_cast<char *>(data), readN * sizeof(int));

    // 检查是否读取了完整的 readN 个整数
    if (binIn.gcount() != static_cast<std::streamsize>(readN * sizeof(int)))
    {
        std::cerr << "读取数据不完整，文件可能损坏！" << std::endl;
        binIn.close();
        delete[] data;
        delete[] numbers;
        return 1;
    }
    binIn.close();

    // 对数组进行排序（使用标准库排序算法，也可自行实现）
    std::sort(data, data + readN);

    // 将排序后的数以文本形式写入 04123121.txt
    std::ofstream txtOut("04123122_1.txt");
    if (!txtOut)
    {
        std::cerr << "无法打开 04123122_1.txt 进行写入！" << std::endl;
        delete[] data;
        delete[] numbers;
        return 1;
    }

    for (int i = 0; i < readN; ++i)
    {
        txtOut << data[i] << std::endl; // 每个数占一行
    }
    txtOut.close();

    std::cout << "已成功对 " << readN << " 个数进行排序，并写入 04123122_1.txt" << std::endl;

    // 释放动态分配的内存
    delete[] numbers;
    delete[] data;

    return 0;
}
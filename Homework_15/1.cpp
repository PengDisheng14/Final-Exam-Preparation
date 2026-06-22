#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

// 检查字符串是否为合法的四位十六进制数
bool isValidHex(const std::string &s)
{
    if (s.length() != 4)
        return false;
    for (char c : s)
    {
        if (!((c >= '0' && c <= '9') ||
              (c >= 'A' && c <= 'F') ||
              (c >= 'a' && c <= 'f')))
            return false;
    }
    return true;
}

// 将四位十六进制字符串转换为十进制整数（输入已保证合法）
int hexToDec(const std::string &hexStr)
{
    int value = 0;
    for (char c : hexStr)
    {
        value *= 16;
        if (c >= '0' && c <= '9')
            value += c - '0';
        else if (c >= 'A' && c <= 'F')
            value += c - 'A' + 10;
        else if (c >= 'a' && c <= 'f')
            value += c - 'a' + 10;
    }
    return value;
}

int main()
{
    std::ifstream infile("hexfile.txt");
    std::ofstream outfile("04123122decfile.txt");

    if (!infile.is_open())
    {
        std::cerr << "错误：无法打开输入文件 hexfile.txt" << std::endl;
        return 1;
    }
    if (!outfile.is_open())
    {
        std::cerr << "错误：无法创建输出文件 04123122decfile.txt" << std::endl;
        return 1;
    }

    std::string token;
    int count = 0;
    // 读取前10个由空白字符分隔的字符串
    while (infile >> token && count < 10)
    {
        int result = -1; // 默认为非法数据
        if (isValidHex(token))
        {
            try
            {
                result = hexToDec(token); // 合法转换
            }
            catch (...)
            {
                // 理论上不会进入此分支，保留异常处理结构
                result = -1;
            }
        }
        outfile << result << std::endl;
        ++count;
    }

    infile.close();
    outfile.close();
    return 0;
}
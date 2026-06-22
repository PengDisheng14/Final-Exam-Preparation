#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>

class Plural
{
    double real, imag;

public:
    Plural(double re = 0, double im = 0) : real(re), imag(im) {}

    friend std::ostream &operator<<(std::ostream &os, const Plural &p);
    friend std::istream &operator>>(std::istream &is, Plural &p);

    // 获取实部和虚部（用于文件输出）
    double getReal() const { return real; }
    double getImag() const { return imag; }
};

// 输出运算符：美观格式化（实数、纯虚数、一般形式）
std::ostream &operator<<(std::ostream &os, const Plural &p)
{
    if (p.real == 0 && p.imag == 0)
    {
        os << "0";
    }
    else if (p.real == 0)
    {
        os << p.imag << "i";
    }
    else if (p.imag == 0)
    {
        os << p.real;
    }
    else
    {
        os << p.real;
        if (p.imag > 0)
            os << "+";
        os << p.imag << "i";
    }
    return os;
}

// ---------- 辅助函数：字符串处理与解析 ----------
static void removeSpaces(std::string &s)
{
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
}

static bool toDouble(const std::string &s, double &val)
{
    try
    {
        size_t pos;
        val = std::stod(s, &pos);
        return pos == s.size();
    }
    catch (...)
    {
        return false;
    }
}

// 核心解析函数：支持格式 a±bi, (a,b), 实数, 纯虚数
static bool parseComplex(const std::string &input, double &re, double &im)
{
    std::string s = input;
    removeSpaces(s);
    if (s.empty())
        return false;

    // 括号形式
    if (s.front() == '(' && s.back() == ')')
    {
        std::string inner = s.substr(1, s.size() - 2);
        removeSpaces(inner);
        size_t comma = inner.find(',');
        if (comma != std::string::npos)
        {
            std::string rePart = inner.substr(0, comma);
            std::string imPart = inner.substr(comma + 1);
            removeSpaces(rePart);
            removeSpaces(imPart);
            return toDouble(rePart, re) && toDouble(imPart, im);
        }
        else
        {
            return toDouble(inner, re) && (im = 0, true);
        }
    }

    // 无括号形式
    size_t iPos = s.find_first_of("iI");
    if (iPos == std::string::npos)
    {
        return toDouble(s, re) && (im = 0, true);
    }

    // 检查是否纯虚数（不含额外 + 或 -，首字符除外）
    bool hasSep = false;
    for (size_t k = 1; k < s.size(); ++k)
    {
        if (s[k] == '+' || s[k] == '-')
        {
            hasSep = true;
            break;
        }
    }
    if (!hasSep)
    {
        std::string coeff = s.substr(0, iPos);
        if (coeff.empty() || coeff == "+")
            coeff = "1";
        else if (coeff == "-")
            coeff = "-1";
        if (toDouble(coeff, im))
        {
            re = 0;
            return true;
        }
        return false;
    }

    // a±bi 形式：找最后一个 +/-（从位置1开始）
    size_t sepPos = std::string::npos;
    for (size_t k = 1; k < s.size(); ++k)
    {
        if (s[k] == '+' || s[k] == '-')
            sepPos = k;
    }
    if (sepPos == std::string::npos)
        return false;

    std::string realPart = s.substr(0, sepPos);
    std::string imagPart = s.substr(sepPos);
    removeSpaces(realPart);
    removeSpaces(imagPart);

    if (imagPart.find_first_of("iI") == std::string::npos)
        return false;
    size_t iPos2 = imagPart.find_first_of("iI");
    std::string coeffStr = imagPart.substr(0, iPos2);
    if (coeffStr.empty() || coeffStr == "+")
        coeffStr = "1";
    else if (coeffStr == "-")
        coeffStr = "-1";

    double tmpRe, tmpIm;
    if (toDouble(realPart, tmpRe) && toDouble(coeffStr, tmpIm))
    {
        re = tmpRe;
        im = tmpIm;
        return true;
    }
    return false;
}

// 输入运算符重载（保留原有交互，但主程序可单独使用解析函数）
std::istream &operator>>(std::istream &is, Plural &p)
{
    std::string line;
    double re, im;
    while (true)
    {
        std::cout << "请输入复数 (支持 a±bi, (a,b), 实数, 纯虚数) : ";
        if (!std::getline(is, line))
        {
            is.setstate(std::ios::failbit);
            return is;
        }
        if (line.empty())
            continue;
        // 退出命令
        if (line == "exit" || line == "quit")
        {
            is.setstate(std::ios::failbit);
            return is;
        }
        if (parseComplex(line, re, im))
        {
            p = Plural(re, im);
            return is;
        }
        else
        {
            std::cout << "格式错误！请重新输入。\n";
        }
    }
}

// ---------- 主程序：多轮输入，合法复数写入文件 ----------
int main()
{
    std::ofstream fout("04123122_13.txt", std::ios::app); // 追加模式
    if (!fout)
    {
        std::cerr << "无法打开文件 complex.txt\n";
        return 1;
    }

    std::string line;
    std::cout << "===== 复数输入程序 =====" << std::endl;
    std::cout << "支持格式: a±bi, (a,b), 实数, 纯虚数" << std::endl;
    std::cout << "输入空行或 exit 退出程序\n"
              << std::endl;

    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, line);
        if (line.empty() || line == "exit" || line == "quit")
        {
            std::cout << "退出程序。" << std::endl;
            break;
        }

        double re, im;
        if (parseComplex(line, re, im))
        {
            Plural z(re, im);
            // 输出到控制台
            std::cout << "合法复数: " << z << std::endl;
            // 写入文件（追加一行）
            fout << z << std::endl;
            std::cout << "已保存到 04123122_13.txt" << std::endl;
        }
        else
        {
            std::cout << "输入格式错误，请重新输入！" << std::endl;
        }
        std::cout << std::endl;
    }

    fout.close();
    return 0;
}
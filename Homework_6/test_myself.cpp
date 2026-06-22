// 完善代码：头文件
#include <iostream>
using namespace std;

class fraction
{
private:
	int numerator, denominator;

public:
	// 完善代码：所有的函数声明（包括友元函数）
	fraction()
	{
		numerator = 1;
		denominator = 1;
	}
	fraction(int n, int d) : numerator(n), denominator(d) {}
	void set();
	void reduct();
	fraction &operator-=(fraction &x);
	void save(const char *filename);
};

fraction::fraction(int n, int d)
{
	// 完善代码：带参数默认值的构造函数
}

void fraction::set()
{
	// 完善代码：从屏幕中输入分子和分母，中间用逗号隔开，实现分数对象的设置，这里要求对输入数据进行稳健性测试，
	// 当数据格式不符合要求时，要进行提示，并重新进行输入；
	// 要求：需要对两种错误输入进行检测，并提示重新输入情况
	// 错误输入1： 1=3
	// 错误输入2：1.2,4
}

void fraction::reduct()
{
	// 完善代码：约分函数，完成对分子和分母的约分，算法不限，
}

fraction operator+(fraction &x, const int &y)
{
	// 完善代码：完成+号的友元函数重载
}

fraction &fraction::operator-=(fraction &x)
{
	// 完善代码：完成-=号的成员函数重载
}

ostream &operator<<(ostream &dist, fraction &fr)
{
	// 完善代码：完成插入运算符<<的重载
}

void fraction::save(const char *filename)
{
	// 完善代码：完成数据存储到文件的功能，举例格式见示例
}

int main()
{
	fraction f1(4, 6), f2(10, 4), f3;

	f3.set();

	cout << endl
		 << "（1）三个分数分别为：" << endl;
	cout << f1 << f2 << f3;

	cout << endl
		 << "（2）运行f1 -= f2;后，f1中保存的分数是：" << endl;
	f1 -= f2;
	cout << f1;

	cout << endl
		 << "（3）运行f3 = f2 + 3;后，f3中保存的分数是：" << endl;
	f3 = f2 + 3;
	cout << f3;

	f3.save("f3.txt");
	cout << endl
		 << "（4）对象f3的数据成功保存！" << endl;

	return 0;
}

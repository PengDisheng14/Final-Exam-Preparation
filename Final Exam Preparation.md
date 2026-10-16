# 类与对象

## 类是一个数据类型

1. 可以做函数类型和返回值类型
2. 在被定义时不占用内存空间，只有创建对象时才会开辟实际内存

## 类的成员

类中的任何数据成员均不能使用关键字extern，auto或register限定其存储类型

在类内直接定义的函数称为**内联函数**。若类外定义函数也想成为内联函数，则需要在类外定义前加`inline`关键字。

### 静态类成员

`stastic`修饰，为所有对象共享，存储在公共区域中（一荣俱荣，一损俱损）。

静态变量缺省的初值为0。

静态成员函数没有`this`指针，不能访问非静态成员。

类外定义静态成员函数，前面不加`static`

### 常对象与常成员

`const`修饰

常对象不能变，只能调用常成员函数

常数据成员只能通过初始化列表来获得初值

常成员函数不能修改对象数据成员的值，不能调用没有用const修饰的成员函数

```c++
//以拷贝构造函数类外声明为例，const意味着不修改作为参数的对象
Class Name::ClassName(const ClassName &other)

//以分数类乘法类外声明为例，括号外const定义为常成员函数，不修改调用该函数的原对象
MyFraction MyFraction::mul(const MyFraction f)const
```

## 类的构造

1. 构造函数
   1. 无返回值、名称与类名相同、可用来初始化成员变量
   2. 可以重载，但每一个对象都必须有且仅有唯一对应的构造函数
   3. 只要显式定义了一个类的构造函数，则编译器就不产生缺省的构造函数
2. 拷贝构造函数
   1. 格式上：`ClassName(const ClassName &other)`形参为本类的对象引用
   2. 内容上：一定要将所有成员拷贝过来哦
3. 析构函数：
   1. 对象的生存期结束时，系统自动调用析构函数，然后回收存储空间
   2. 构造中有`new`时必须显式定义析构函数

例如：`ofstream outf ( "Myf.txt" );` 打开`Myf.txt`是通过文件流类的______实现。

答：构造函数。用类名创建对象并传入参数时，必定调用该类的构造函数。

构造时机问题：

| 对象类型         | 构造时机                         | 析构时机                      |
| :--------------- | :------------------------------- | :---------------------------- |
| **局部对象**     | 每次执行到定义点时（按定义顺序） | 离开其作用域时立即析构        |
| **静态局部对象** | 第一次执行到定义点时（只一次）   | 程序结束时（`main`之后）析构  |
| **全局对象**     | `main` 函数之前                  | 程序结束时（`main` 之后）析构 |

拷贝时机问题：
1. 用类的一个对象去初始化该类的另一个对象时系统自动调用
2. 函数的形参为类对象or返回值是类对象时，系统自动调用

注意：
1. 全局对象按定义顺序构造，逆序析构。
2. 三大构造函数都可由系统生成。

## this指针

每一个静态成员，编译器都会给其分配`this`指针（所以我们才能直接访问成员，或以显式指针访问成员）

友元函数不带有`this`指针，所以访问成员必须使用`类.`格式

**作用：**指示本对象。

以读取键盘输入的分子分母，实现输入为例：

```c++
void MyFraction::inputFraction()
{
    int N,D;
    cout<<"请分别键入分子、分母值："<<endl;
    cin>>N>>D;				//创建一个临时对象，然后立即销毁，对当前对象毫无影响
    *this=MyFraction(N, D);	//把新构造的对象赋值给当前对象
}

//调用
	f.inputFraction();
```

以使用白手套`result`，实现分数类乘法为例：

```c++
//对拷贝了本对象的result一通操作，但本对象未被修改
MyFraction MyFraction::mul(const MyFraction f)const
{
    MyFraction result = *this;
    result.Numerator = result.Numerator * f.Numerator;
    result.Denominator = result.Denominator * f.Denominator;
    result.reduction();
    return result;
}

//this指针指向本对象，篡改了本对象，错误！
MyFraction MyFraction::mul(const MyFraction f)
{
    MyFraction result = *this;
    this->Numerator = this->Numerator * f.Numerator;
    this->Denominator = this->Denominator * f.Denominator;
    this->reduction();
    return *this;
}

//可以直接使用构造函数，不使用this指针
MyFraction MyFraction::mul(MyFraction f) 
{
    MyFraction result(Numerator * f.Numerator, Denominator * f.Denominator);
    result.reduction();
    return result;
}

//自乘：修改原对象，且不需要使用this指针
void MyFraction::mymul(const MyFraction &f)
{
    Numerator = Numerator * f.Numerator;
    Denominator = Denominator * f.Denominator;
    reduction();
}
```

以虚数类重载前置`++`和后置`++`运算符的类外实现为例：

```c++
//改变原对象，并返回改变后的值
complex1 complex1::operator++()
{
    real += 1;
    imag += 1;
    return *this;
}

//改变原对象，但返回改变前副本；int是为了做区分，实际上不用传入参数
complex1 complex1::operator++(int)
{
    complex1 temp = *this;
    real += 1;
    imag += 1;
    return temp;
}
```

还有，想不清楚返回和参数也太笨啦！

```c++
    fractions[0].reciprocal();			   //该语句生成了一个结果，但将结果直接丢弃了
    fractions[0]=fractions[0].reciprocal();//将返回值赋给数组对象才行，且不需要重载
```

除此以外，若参数与数据成员重名，必须使用this

```c++
void showperson(string name) 
{
    cout << name;          // 输出参数 name
    cout << this->name;    // 输出成员变量 name
}
```

## 运算符重载

问题〇：重载
1. 函数重载：名称相同，参数不同
2. 运算符重载：名称相同，作用不同

问题一：运算符重载规则
1. 不创造新的运算符
2. 不改变原运算符优先级、结合性、逻辑
3. 二元运算符重载时，友元函数需要两个参数，成员函数默认左操作数为本类对象故只需要一个参数

问题二：运算符能否重载
1. 无法重载的运算符：`::`作用域解析、`.`直接成员访问、`.*`成员指针解引用、`?:`三目运算符、`sizeof`
2. 只能用成员函数重载的运算符：`=`赋值运算符、`()`函数调用运算符、`[]`下标运算符、`->`成员访问运算符、类型转换运算符
3. 一般用友元函数重载的运算符：流输入输出运算符`<<`和`>>`

++运算符的重载

## 友元

友元关系是单向的、不能传递的，破坏封装性的。

“A是B的友元”=“在B内声明A”：A能访问B，B不能访问A。

虚数类重载`<<`和`>>`：

```c++
ostream &operator<<(ostream &cout, const complex1 &com)
{
    //注意这是友元函数，需要通过对象访问私有成员哦
    cout << com.real << "+" << com.imag << "j";
    //注意要return哦
    return cout;
}

//输出需要const，输入不许写哦
istream &operator>>(istream &cin, complex1 &com)
{
    cin >> com.real >> com.imag;
    return cin;
}
```

# 模板

1. 函数模板用`function`，类模板用`class`
2. 多个函数重载时
   1. 找参数完全匹配的普通函数
   2. 找参数完全匹配的模板函数
   3. 找自动转换的普通函数
   4. 直接报错：匹配类模板时没有自动转换操作

记住一点：模板后面必须跟参数列表，即可！

```c++
// 作用域前，要添加！
Store<T>::Store() : Valuded(0) {}

// 声明类对象，要添加！
Store<int> S1, S2;
Store<double> S3;
Store<Student> S4;

//做成员函数参数时，要添加！
void Copy(const Set<T, size> &s)

//局部对象声明，要添加！
Set<T, size> result = *this;
```

模板参数列表中可以有非类型参数

```c++
template <typename T,int size>
class array
{
	T Element[size];
	int num;

public:
	array() : num(size) {};
};

array<int, 30> a1;      // 值不可修改
array<double, 40> a2;
```

# 动态内存分配

## 内存四区

1. 堆区：由程序员手动管理的内存
2. 栈区：局部变量、形参
3. 全局区：全局变量、静态变量（生命周期贯穿整个程序的内容）
4. 代码区：代码、字符串常量，只读

eg.成员函数存放在代码区

## `new`和`delete`运算符基本语法

1. 给**指针变量**赋初值
2. 只要`new`必须`delete`；只有`new`才能`delete`；`delete`一次就好避免重复释放
   这里的释放和Steam卸载游戏一样
3. 空指针`NULL`和野指针的概念：略

```c++
int *p1 = new int; *p1 = 4; *p1 =1 00;  // 先创建再初始化使用指针；可随时修改
int *p2 = new int(4);		            // 下标可以在运行时确定
Student *stu = new Student[4];          // 甚至可以new类对象数组出来

delete p1;
delete p2;
delete[] stu;                           // delete时不需要在[]里写内容
```

## 深拷贝与浅拷贝

三五法则：**只要定义了析构函数或赋值运算符，就必须定义拷贝构造函数**
如果程序员没有做这项工作，系统会自动生成**浅拷贝**默认拷贝构造函数

浅拷贝：所有对象使用同一个内存空间
深拷贝：每个对象独立享有内存空间

深拷贝实现赋值运算符重载：必须判断是否自我赋值，必须删原内容。

堆区数组还是用`for`循环，出入栈是对`top`做工作，排序用`bubbleSort`

```c++
Str::Str(char a, int b) : Char(a), Int(b) // 作为派生类，构造函数应该使用初始化列表
{
	this->s = new char[b]; // 给类成员s赋值（这里要会使用*s指向动态数组）
	for (int i = 0; i < b; i++)
		s[i] = a;
}

Str &Str::operator=(const Str &st)
{
	if (this == &st)
		return *this;
	delete[] s; // 需要先释放旧内存：我们动态内存分配的赋值需要考虑内存空间
	SetChar(st.GetChar());
	SetInt(st.GetNum());
	int len = GetNum();
	s = new char[len];
	memcpy(s, st.s, len);
	return *this;
}
```

# 线性表

线性表分为顺序表（例如数组）和链表。

## 数组

### 数组初始化

注意`char`类型数组的初始化：

```c++
double arr1[] = {8.1, 2.2, 3.9, 9.3, 5.4, 6.5, 7.8};
int arr2[] = {101, 204, 300, 18, 57, 77, 99, 23, 18};
char arr3[] = "Program of template";
string arr4[] = {"cat", "dog", "fox", "ox", "hen", "lion"};
```

### 数组长度

数组做函数参数时，退化为指针，不可使用`sizeof()`。

```c++
//正确
template <typename T>
void arrayPrint(T arr[], int len)
{
    for (int i = 0; i < len; i++)
        cout << arr[i] << ' ';
}

//错误
template <typename T>
void arrayPrint(T arr[])
{
    int len = sizeof(arr) / sizeof(T);
    for (int i = 0; i < len; i++)
        cout << arr[i] << ' ';
}
```

### 删除数组元素模板

1. 函数参数中的 `&` 表示引用；它的作用是**让函数内部的修改直接影响原始变量**，而不是仅仅操作一个副本。
2. 通过 `arr[i]` 修改数组元素，**会影响原始数组**

```c++
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
```

## 链表

单链表中每个元素占用一个**结点**：包含数据域、指针域；结点的物理地址和逻辑地址不需要相同。

首结点地址存放于表头指针`head`，`head`丢失则链表无法访问、内存泄漏。

顺序表的插入和删除需要移动，链表不需要。

插入删除操作

```c++
// 插在链首
newnode->link = head;
head = newnode;

// 插在第二个位置
newnode->link = head->link;
head->link = newnode;

// 插在中间
newnode->link = p->link;
p->link = newnode;

// 插在队尾
newnode->link = nulptr;
p->link = newnode;
```

# 数据结构

## 栈与队列

栈和队是特殊的线性表，使用顺序表和链表实现

栈：只允许在表一端插入删除的线性表；定义栈顶、栈底，后进先出

>题目中注意“元素已经在栈里”还是“元素待入栈”

## 栈基本操作

一直是对栈顶`top`做操作。

出入栈：注意一个顺序、一个加减。

以`top`指向首结点前面的空（存在哨兵结点）、数组顺序正常为例：

```c++
// 入栈：先赋值再移动指针
data[top++] = value;
// 出栈：先移动指针再返回值
return data[--top]

// 判空
bool isEmpty() const { return top == 0; }
// 判满
bool isFull() const { return top == capacity; }
```

头插法逆置链表：来不及了。

不会写就写`NULL`，`while`循环体内呈现“特步形”。

```c++
while(temp!=NULL)
{

}
```

## 三种排序算法对比

| 排序算法     | 最好时间复杂度    | 平均时间复杂度 | 最坏时间复杂度 | 空间复杂度 | 稳定性   |
| :----------- | :---------------- | :------------- | :------------- | :--------- | :------- |
| **插入排序** | **O(n)**          | O(n²)          | O(n²)          | O(1)       | ✅ 稳定   |
| **冒泡排序** | **O(n)** (优化后) | O(n²)          | O(n²)          | O(1)       | ✅ 稳定   |
| **选择排序** | O(n²)             | O(n²)          | O(n²)          | O(1)       | ❌ 不稳定 |

复杂度$\mathrm O(\mathrm n)$：括号里的数越大越复杂

交换次数最少的是**选择排序**：$(\mathrm n -1)$次；最好时间复杂度最高、唯一不稳定的也是它。

# 继承、派生与多态

## 基础知识

继承：
1. 箭头表示继承方向：基类或父类 $\leftarrow$ 派生类或子类
2. 单一继承：单亲家庭；多重继承：美满家庭
3. 构造函数和析构函数不能从基类继承。子类只需要初始化新增加的成员即可。

派生：
1. 若派生方式缺省，则默认为私有`private`
2. 三种派生方式之类内访问与类外访问问题
   1. 类内访问：基类的`public`和`protected`都可访问
   2. 类外访问：降级后是`public`才能在类外访问

## 派生的构造函数

1. 构造顺序：基类构造函数 $\rightarrow$ 基类对象构造函数 $\rightarrow$ 派生类构造函数
2. 析构顺序：派生类析构函数 $\rightarrow$ 基类析构函数
3. 若不显式调用基类构造函数，则系统默认调用缺省（无参）构造函数

```c++
// 三维点类构造函数类内实现
ThreeDPoint(double x, double y, double z) : Point(x, y), z(z) {}

// 派生类中基类对象作成员
Rectangle(double x0, double y0, double x, double y, double len, double wid) : Point(x0, y0), LeftDown(x, y), length(len), width(wid) {}
Rectangle(const Rectangle &other) : Point(other), LeftDown(other.LeftDown), length(other.length), width(other.width) {} 

// 聚合类中基类对象作成员
Line(const ThreeDPoint &th1, const ThreeDPoint &th2) : th1(th1), th2(th2) {}
```

## 多重继承

1. 构造函数声明方式：`class D:public A, private B, protected C{};`
2. 构造顺序不变，按声明顺序调用基类构造函数

## 派生类应用

赋值兼容：用公用派生类对象向基类对象赋值。该操作是单向不可逆的。

聚合：在一个类中以另一个类的对象作为数据成员。

注意，同一基类不同派生类对象之间不能相互赋值。

基类有无参构造函数，派生类构造函数就可以不带初始化列表。

派生类和基类中可以有同名数据成员，可以有同名同参数列表的函数成员，分别存储。

### 虚函数与虚基类

虚基类：在派生继承列表中写`virtual`定义虚基类

虚函数`virtual`
1. 基类的成员函数（不能是友元也不能是静态）声明为虚函数
2. 在所有派生类中保持虚函数特征
3. 作用：允许派生类中定义与基类虚函数完全同名的函数

虚析构：
1. 用new运算符建立临时对象，且用指向基类的指针指向该临时对象时，系统只析构基类不析构派生类
2. 解决方法：将基类析构函数定义为虚
3. 讲义甚至建议将所有析构函数定义为虚；构造函数不能虚，析构函数不能重载

纯虚函数
1. 格式：`virtual float area() =0;`等于0、没有函数体
2. 含有纯虚函数的基类称为抽象类，无法实例化，但其指针可以指向派生类对象

# 输入输出流类库与格式控制

## 基本概念

1. 输入输出流、输入输出流类、输入输出流类库：标准`<iostream>`、文件`<fstream>`
2. 缓冲区与缓冲流：概念而已，记住标准流中唯有`cerr`无缓冲即可。直接报错，告到中央。

文件：文件分为ASCII（文本）文件和二进制文件，分别对应字符数据和数值数据两种信息在内存中存放方式

## 输出格式控制

标志字（又称流格式控制成员函数）：本质是被IO类保护的位掩码，需要接口函数调用

```c++
cout.setf(ios::left, ios::adjustfield); 
cout.setf(ios::hex, ios::basefield);   
cout << 255 << endl;
```

控制符（又称流操作子）：被重载的运算符，更加简洁

```c++
cout << left << hex << 255 << endl;
```

作业中用到的：

```c++
//==========左对齐和右对齐输出==========
cout << setw(10) << setfill('*') << a << endl; 
cout << left << setw(10) << setfill('#') << a << endl;

//==========三种进制输出==========
cout << "十六进制：" << hex << showbase << a << endl;
cout << "八进制：" << oct << showbase << a << endl;
cout << "十进制：" << dec << showbase << a << endl;

double pi = 1000.0 / 19;
//==========科学计数法输出==========
cout << setfill(' ') << right;
cout << scientific << "pi=" << setw(14) << pi << endl;

//==========定点格式输出==========
cout << fixed << showpos << internal << setw(12) << setprecision(6) << pi << endl;
```

## 提高标准输入输出

`cin`为缓冲流：
1. 输入时如果输入错误，须在回车前修改，按下回车后无法修改
2. 输入的数据类型必须与提取的数据类型一致
3. 如果一次输入过多，会留在缓冲区待下一次提取；只有把缓冲区的数据取完，才会要求输入新的数据

缓冲区是`buff`

`>>`运算符和`cin.get()`：
1. 使用`>>`提取输入数据时，无法读取空格/回车，它们可以作为数据之间的分隔符
2. 要读取空格/回车，必须使用 `cin.get()` 或 `cin.getline()`
3. 输入一份内容以后，按回车，再输入第二份内容，这种情况需要使用一次 `cin.get()` 提取回车
4. 输入一份内容以后，按不止一个回车或空格，再输入第二份内容，这种情况需要清空缓冲区

函数家族：
1. `get`和`put`：可对文本文件造作，也可对二进制文件操作
2. `getline`：遇到指定结束符，提取该结束符，但不保存在串中；也可用于读空缓冲区和回车
3. `read`和`write`：只用于二进制文件
4. `clear(0)`：所有状态字定为0；`rdstate()`：显示状态字值
   `state`状态字：出错时置1；错误状态不清除，流会拒绝后续所有操作
5. `ignore(1000, '\n')`：清空缓冲区直到换行

```c++
ifstream infile("test.txt");
char ch1, ch2;
ch1 = infile.get();     // 读一个字符，读到文件末尾返回EOF，不跳过空格和换行
infile.get(ch2);        // 读取字符存入ch
char buffer[50];        // 定义长度为50的缓冲区，能容纳49个有效字符
infile.get(buffer, 50); // 最多读49个字符，直到遇到EOF或换行符，换行符留在流内

cin.getline(str, 255);  // 读空缓冲区和回车
char ch[20];
cin.getline(ch, 20, 'X');

ofstream outfile("test.txt");
outfile.put('\n');         // 写入换行符
outfile.put('B').put('C'); // 链式写入 "BC"

infile.read((char*)&num, sizeof(int));
infile.read((char*)&pi, sizeof(double));
if (infile.gcount() != sizeof(double))
    cerr << "文件长度不足！" << endl;

ofstream outfile("data.dat", ios::binary);
outfile.write((char*)&num, sizeof(int));
outfile.write((char*)&pi, sizeof(double));
outfile.write((char*)val, 6*sizeof(int) );       // 数组记得不加&

cin.clear(0);
cout << "状态字：" << cin.rdstate() << endl;     // 状态字被强制定为0
```

一个简单的例子：

```c++
#include<iostream>
using namespace std;

int main()
{
    char carr[20];
    cout << "enter a sentence:" << endl;
    cin.get(carr, 10, 'X');							// 最多读取9个字，指定X为结束符
    cout << "读入字符串为：" << carr << endl;
    cout << "读入字符串长度为：" << cin.gcount() << endl;
    cout << "继续读入字符：" << char(cin.get()) << endl;
    cin.clear();
    cout << "状态字：" << cin.rdstate() << endl;     // 状态字被强制定为0
    cin.ignore(20, '\n');							// 扔掉未被提取的字符和空格
}
```

输入`Happy New Year!`：

```c++
读入字符串为：Happy New
读入字符串长度为：9
继续读入字符：					//这里输出的是空格哦
状态字：0
```

输入`THE BOX IS BIG!`：

```c++
读入字符串为：THE BO
读入字符串长度为：6
继续读入字符：X
状态字：0
```

## 文本文件

打开与关闭过程：
1. 打开输入文件时，文件必须存在；打开输出文件时可不存在
2. 打开文件后应判断是否成功；关闭文件并没有取消文件流对象，文件流对象在程序结束时，或它的生命期结束时，由析构函数撤消
3. 调用成员函数open打开文件，并可指定文件的工作方式: 输入、输出、ASCII或二进制文件等。`iofile.open(磁盘文件名,输入输出方式);`可以用“位或”运算符“|”对输入输出方式进行组合。

文本文件读写示例：

```c++
#include <fstream>//要用到的头文件

ifstream infile("D:\\mydatafile.txt");
if (!infile) 
{
    cerr << "无法打开文件！" << endl;
    return 1;
}

string header;
getline(infile, header);   // 空getline读取并丢弃标题行

student Students[10];
for (int i = 0; i < 10; i++)
{
    infile >> Students[i].student_ID //读取信息存放在类或结构体数组中
        >> Students[i].name
        >> Students[i].sex
        >> Students[i].age
        >> Students[i].address
        >> Students[i].score;
}
infile.close();//读取完成后关闭文件

ofstream outfile("mydatafile.txt");   // 默认 ios::out
if (!outfile) 
{
    cerr << "打开文件失败！" << endl;
    return 1;   // main函数中return 1
}
outfile << "Hello, file!" << endl;
outfile.close();
```

## 二进制文件

1. 文件后缀名为`.dat`，需要显式使用`ios::binary`
2. 并且不能使用`infile >>`和`outfile <<`，只能使用`infile.read`和`outfile.write`
3. 可靠又保密
4. 文件结束后，系统不会再读，但程序不会自动停下来，要判断文件中是否已没有数据。
5. 文件中存在**文件指针**：
   1. 打开时位于文件头
   2. 如关闭后重新打开，位于文件头
   3. 如写完数据后没有关闭文件，直接开始读，须把文件指针移到文件头。

```c++
	char filename1[256], filename2[256];
	char buff[4096];
	cout << "输入源文件名:";
	cin >> filename1;
	cout << "输入目的文件名:";
	cin >> filename2;
	fstream infile(filename1, ios::in | ios::binary);
	fstream outfile(filename2, ios::out | ios::binary);
	if (!infile)
	{
		cerr << "open error!" << endl;
		exit(1);
	}
	if (!outfile)
	{
		cerr << "open error!" << endl;
		exit(1);
	}
	int n;
	while (!infile.eof()) // 只要不到文件尾就一直循环
	{
		infile.read(buff, 4096); // 尝试将最多4096个字节送入缓冲区
		n = infile.gcount();	 // 实际读入字节数
		outfile.write(buff, n);	 // 把实际读入字节数存入文件中，避开垃圾数据
	}
	infile.close();
	outfile.close();
	infile.clear(); // 重置标志位
	return 0;
```

# 异常处理

## 基本概念

处理的是**运行错误**（数组越界、除以0、压栈出栈失误、文件打开失败），避免程序直接停止运行

异常处理机制由三部分组成：检查`try`、抛出`throw`和捕捉`catch`：
1. `try`中存放需要检查的语句
2. `throw`用来发出异常信息，类型需要与`catch`匹配；程序立刻离开本函数或块
3. `catch`用来捕捉与处理异常信息。
4. `try-catch`必须连在一起

所以说设计思路是`try-catch`放一块，`throw`和需实现的内容都放在`try`中：

```c++
double triangle(double a, double b, double c)
{
    // 第一步：检查非正数，作为非法情形抛出
    if (a <= 0 || b <= 0 || c <= 0)
        throw a;
    // 第二步：检查三角不等式
    double s = (a + b + c) / 2;   
    if (a + b <= c || b + c <= a || c + a <= b)
        throw a;

    return sqrt(s * (s - a) * (s - b) * (s - c));
}

int main()
{
    double a, b, c;
    try 
    {
        while (cin >> a >> b >> c) // 持续读取，直到遇到文件结束符或非数字输入
            cout << triangle(a, b, c) << endl;
    }
    catch (double) // 捕获所有非法边长（包括非正数 和 不满足三角不等式）
    {
        cout << "a=" << a << ",b=" << b << ",c=" << c 
             << ", which is not a valid triangle!" << endl;
    }
    
    cout << "end" << endl;
    return 0;
}
```

`catch`检查的是类型。不过可以让它接收值。

```c++
// 原来的（只开门，不收件）
catch (double) {cout << "a=" << a << ",b=" << b << ",c=" << c << "...";}

// 修改后（开门且收件）
catch (double err) {cout << "发生错误，抛出的异常值是：" << err << endl;}
```

往`try-catch`结构最后放一个“接收其他一切报错”语句：

```c++
// 就是这样写
catch(...) {cout<<"OK"<<endl;}
```

## 栈展开

因发生异常而逐步退出复合语句和函数定义，被称为**栈展开**：一步步后退，直到找到匹配的`catch`语句为止。

栈展开过程自动调用析构函数。所以在包含自动内存分配时，最好把资源封装在类中，由析构函数集中释放。

```c++
int main( )
{
try  { f1(); }
catch(double)
{ cout<<"异常捕获在主函数try块!"<<endl; }
cout<<"main 函数结束！"<<endl;
return 0;
}

void f1()
{ try {f2();}                      
catch(char) {cout<<"异常捕获在f1 try 块中！";}
cout<<"函数f1()结束！"<<endl;
}

void f2()
{ try {f3();}                      
catch(int) {cout<<"异常捕获在f2 try 块中！";}
cout<<"函数f2()结束！"<<endl;
}

void f3()
{ double a=0;
try {throw a;}                      
catch(float) {cout<<"异常捕获在f3 try 块中！";}
cout<<"函数f3()结束！"<<endl;
}
```

在`main()`函数中匹配到`catch`，终端中输出如下：

```c++
异常捕获在主函数try块!
main 函数结束！
```

## 补充

1. 异常重新抛出：`catch;`
   仅有一个关键字，异常类型在`catch`语句中已有，不必再指明。被重新抛出的异常就是原来的异常对象
2. 异常和继承：不会
3. 异常规范：可在函数声明和定义时附上能抛出的异常列表
4. C++标准库异常类：使用`<stdexcept>`

```c++
void func() throw (int, double); // 可能抛出int或double
void func() throw ();            // 不会抛出异常
void func();                     // 可能抛出任何异常            
```


# 小点

## 数学

**最大公约数与最小公倍数**

欧几里得算法计算最大公约数：

```c++
#include<cmath>
int gcd(int a, int b) 
{
	return b == 0 ? std::abs(a) : gcd(b, a % b);
}
```

最小公倍数：
$$
\mathrm{Lcm}=\frac{\mathrm {a \times b}}{\mathrm{gcm(a,b)}}
$$

**开平方根**：`sqrt()`函数，需要`cmath`库文件

## 强制类型转换

将内存中的数组`int val[6]={2,4,8,9};`写入二进制文件`file.dat`中：

```c++
    // 可以实现，数组名退化为指向首元素的指针，转换后指向数据起始地址
    ofstream ofile(“file.dat”, ios::binary);
	ofile.write((char *)val, 6 * sizeof(int));
    
    // 可以实现，但语义不完备，算错
	ofstream ofile(“file.dat”, ios::binary);
	ofile.write((char *)&val, 6 * sizeof(int));
```

char数组的元素改为string类型：

```c++
//char数组的元素改为string类型，作为函数参数
cout << "delete count:" << deleteArray(arr4, lenArr4, string("fox")) << endl;
```

## 初始化列表

类外初始化拷贝构造函数：
```c++
MyFraction::MyFraction(const MyFraction& other):Numerator(other.Numerator),Denominator(other.Denominator)
{
	cout<<"拷贝构造函数调用"<<endl;
}
```

含继承情况下类内初始化构造函数与拷贝构造函数：

```c++
// 三维点类构造函数
ThreeDPoint(double x, double y, double z) : Point(x, y), z(z) {}

// 矩形类构造函数与拷贝构造函数
Rectangle(Point p, double len, double wid) : Point(p), LeftDown(p), length(len), width(wid) {}
Rectangle(const Rectangle &other) : Point(other), LeftDown(other.LeftDown), length(other.length), width(other.width) {}
```

## 与是`&&`或是`||`

以判断是否是闰年为例：

```c++
bool Day::checkLeap(int y)
{
    return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
}
```

## 生成随机数

使用 `rand()` 生成 `[A, B]` 之间的随机整数的核心语句是：`int num = rand() % (B - A + 1) + A;`

```c++
#include <cstdlib>
#include <ctime>

srand(time(0));                // 初始化种子（只需一次）
int num = rand() % 7 - 1;      // -1 到 5

int den;
do { den = rand() % 21 - 10; } while(den == 0);  // -10 到 10，排除0
```
## `return`时机问题

以循环遍历比较为例，在最后return而不是在循环体内部return

```c++
for (int i = 0; i < num; ++i)
    if (elements[i] == ism) return 1;
return 0;
```

## bool类型函数在返回语句内判断

以判断复数类对象是否相等为例：

```c++
bool MyFraction::equal(MyFraction &f)
{
    return Numerator * f.Denominator == Denominator * f.Numerator;
}
```

## `do……while`实现完成三轮操作

原理很简单：设置一个计数器，每次执行操作后+1；要注意是先操作，再更新计数器。

```c++
int turn = 1;
do
{
	//操作
    turn++;
} while (turn < 4);
```

## 每行输出10个

原理也很简单：首先`for`括号内的`i`就是一个计数器。使用取模运算符`%`，逢10输出`endl`即可。

```c++
for (int i = 0; i < last; i++)
{
    cout << slist[i] << " ";
    if (i + 1 % 10 == 0)        //注意i是下标，所以需要用i+1判断
        cout << endl;
}
if (n % 10 != 0)
    cout << endl;
```

## 不借助新表实现反向

使用`swap`函数即可

```c++
int left = 0, right = n - 1;
while (left < right)
{
    swap(arr[left], arr[right]);
    left++;
    right--;
}

```


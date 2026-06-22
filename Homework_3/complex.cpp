#include "complex1.h"
#include "complex2.h"
#include <iostream>
using namespace std;

void Ctest(complex1 A, complex1 B, complex1 C, complex1 D)
{
    cout << "A为:\t\t" << A;
    cout << "B为:\t\t" << B;
    cout << "C为:\t\t" << C;
    cout << "D为:\t\t" << D;
    C = A++; // 后置++运算
    cout << "C=A++，  C为:\t" << C;
    cout << "A为：\t\t" << A;

    C = ++A; // 前置++运算
    cout << "C=++A，  C为:\t" << C;
    cout << "                A为:\t" << A;

    cout << "                B为:\t" << B;
    C = A * B; // 乘法运算
    cout << "C=A*B，  C为:\t" << C;

    A *= B;
    cout << "A*=B，    A为:\t" << A;

    C = A / B;
    cout << "C=A/B，  C为:\t" << C;

    A /= B;
    cout << "A/=B，    A为:\t" << A;

    D = A + B + C;
    cout << "D=A+B+C,D为:\t" << D;

    A += B += C;
    cout << "A+=B+=C,A为:\t" << A;
    cout << "                B为:\t" << B;

    D = A - B - C;
    cout << "D=A-B-C,D为:\t" << D;

    A -= B += C;
    cout << "A-=B+=C,A为:\t" << A;
    cout << "                B为:\t" << B;

    A = B;
    cout << "A=B，      A为:\t" << A;

    D = A * B * C;
    cout << "D=A*B*C,D为:\t" << D;

    D = D / B / C;
    cout << "D=D/B/C,D为:\t" << D;

    A *= B *= C;
    cout << "A*=B*=C,A为:\t" << A;
    cout << "                B为:\t" << B;
    cout << "                C为:\t" << C;

    A /= B /= C /= C;
    cout << "A/=B/=C/=C,A为:\t" << A;
    cout << "                B为:\t" << B;
    cout << "                C为:\t" << C;

    if (A > C)
        cout << " A > C " << endl;
    else
        cout << " A <= C " << endl;

    B = C = A;
    cout << "B    =C = A,A为:\t" << A;
    cout << "                B为:\t" << B;
    cout << "                C为:\t" << C;

    C = -D;
    cout << "C = -D,C为:\t" << C;
    cout << "                D为:\t" << D;

    if (A == B)
        cout << "A==B" << endl;
    else
        cout << "A!=B" << endl;
}

void Ctest(complex2 A, complex2 B, complex2 C, complex2 D)
{
    cout << "A为:\t\t" << A;
    cout << "B为:\t\t" << B;
    cout << "C为:\t\t" << C;
    cout << "D为:\t\t" << D;
    C = A++; // 后置++运算
    cout << "C=A++，  C为:\t" << C;
    cout << "A为：\t\t" << A;

    C = ++A; // 前置++运算
    cout << "C=++A，  C为:\t" << C;
    cout << "                A为:\t" << A;

    cout << "                B为:\t" << B;
    C = A * B; // 乘法运算
    cout << "C=A*B，  C为:\t" << C;

    A *= B;
    cout << "A*=B，    A为:\t" << A;

    C = A / B;
    cout << "C=A/B，  C为:\t" << C;

    A /= B;
    cout << "A/=B，    A为:\t" << A;

    D = A + B + C;
    cout << "D=A+B+C,D为:\t" << D;

    A += B += C;
    cout << "A+=B+=C,A为:\t" << A;
    cout << "                B为:\t" << B;

    D = A - B - C;
    cout << "D=A-B-C,D为:\t" << D;

    A -= B += C;
    cout << "A-=B+=C,A为:\t" << A;
    cout << "                B为:\t" << B;

    A = B;
    cout << "A=B，      A为:\t" << A;

    D = A * B * C;
    cout << "D=A*B*C,D为:\t" << D;

    D = D / B / C;
    cout << "D=D/B/C,D为:\t" << D;

    A *= B *= C;
    cout << "A*=B*=C,A为:\t" << A;
    cout << "                B为:\t" << B;
    cout << "                C为:\t" << C;

    A /= B /= C /= C;
    cout << "A/=B/=C/=C,A为:\t" << A;
    cout << "                B为:\t" << B;
    cout << "                C为:\t" << C;

    if (A > C)
        cout << " A > C " << endl;
    else
        cout << " A <= C " << endl;

    B = C = A;
    cout << "B    =C = A,A为:\t" << A;
    cout << "                B为:\t" << B;
    cout << "                C为:\t" << C;

    C = -D;
    cout << "C = -D,C为:\t" << C;
    cout << "                D为:\t" << D;

    if (A == B)
        cout << "A==B" << endl;
    else
        cout << "A!=B" << endl;
}

int main()
{
    complex1 A1(32, -20), B1(12, -7), C1, D1;
    complex2 A2(32, -20), B2(12, -7), C2, D2;

    // Ctest(A1, B1, C1, D1);
    // Ctest(A2, B2, C2, D2);

    complex2 Com;
    cout << "请分别输入复数的实部和虚部：";
    cin >> Com;
    cout << "输入的复数为："
         << Com
         << endl;

    complex2 CC1(Com + 10);
    complex2 CC2(-10 + Com);
    cout << "运算后的复数为" << CC1 << "与" << CC2;
}

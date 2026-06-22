#include <iostream>
using namespace std;
class Parent
{
    int x;

public:
    Parent(int x)
    {
        this->x = x;
    }
};
class Child : public Parent
{
    int y;

public:
    Child(int m) : Parent(1), y(m) {}
};
int main()
{
    Child c(1);
    return 0;
}

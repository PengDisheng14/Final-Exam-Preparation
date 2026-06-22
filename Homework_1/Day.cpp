#include <iostream>
using namespace std;

class Day
{
private:
    int year;
    int month;
    int day;
    int weekday;
    double isLeap;

public:
    Day(int y = 2000, int m = 1, int d = 1, int w = 6);
    void setDay();
    void showDay();
    bool checkLeap(int y);
    int calculateWeek(int y, int m, int d);
};

Day::Day(int y, int m, int d, int w)
{
    year = 2000;
    month = 1;
    day = 1;
    weekday = 6;
}

bool Day::checkLeap(int y)
{
    return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
}

int Day::calculateWeek(int y, int m, int d)
{
    if (m == 1 || m == 2)
    {
        m += 12;
        y--;
    }
    // 基姆拉尔森公式
    int w = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400 + 1) % 7;
    return w;
}

void Day::setDay()
{
    cout << "设置日期，请分别输入年、月、日：" << endl;
    int y, m, d;
    cin >> y >> m >> d;
    bool inputisLeap = checkLeap(y);

    if (m > 12 || m < 0)
    {
        cout << "月份输入错误！" << endl;
        return;
    }

    int maxDay = 31;
    if (m == 4 || 6 || 9 || 11)
        maxDay = 30;
    else if (m == 2)
        maxDay = inputisLeap ? 29 : 28;
    if (d > maxDay || d < 1)
    {
        cout << "日期输入错误" << endl;
        return;
    }

    year = y;
    month = m;
    day = d;
    isLeap = inputisLeap;
    weekday = calculateWeek(y, m, d);
}

void Day::showDay()
{
    const char *weekname[] = {"日", "一", "二", "三", "四", "五", "六"};
    cout << "日期为" << year << "年" << month << "月" << day << "日星期" << weekname[weekday % 7] << "\n";
}

int main()
{
    Day d1;
    d1.showDay();
    d1.setDay();
    d1.showDay();
}

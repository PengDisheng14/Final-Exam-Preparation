#include <iostream>
#include <fstream>
#include <string>

struct student
{
    int student_ID;
    std::string name;
    std::string sex;
    int age;
    std::string address;
    int score;
};

int main()
{
    student Students[10];
    std::ifstream infile("info1.txt");

    std::string dummyLine;
    getline(infile, dummyLine);

    if (!infile.is_open())
    {
        std::cout << "Error: File not found!" << std::endl;
        return -1;
    }

    for (int i = 0; i < 10; i++)
    {
        infile >> Students[i].student_ID >> Students[i].name >> Students[i].sex >> Students[i].age >> Students[i].address >> Students[i].score;
    }
    infile.close();

    // 查找数据中成绩中最高分记录
    int best_score = 0;
    int j = 0;
    for (int i = 1; i < 10; i++)
    {
        if (Students[i].score > best_score)
        {
            best_score = Students[i].score;
            j = i;
        }
    }

    std::cout << "name\tScore" << std::endl;
    std::cout << Students[j].name << "\t" << Students[j].score;
}
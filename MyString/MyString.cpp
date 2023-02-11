#include <iostream>
#include "MyString.h"

int main()
{
    setlocale(LC_ALL, "rus");
    MyString str = "ABCDEFGHIJ";
    MyString str2 = MyString("Hello");
    std::cout << str << std::endl;
    str = str2;
    std::cout << str << std::endl;
    str.insert(2, "21");
    std::cout << str << std::endl;
    std::cout << str.compare("hi") << std::endl;
    str[0] = ')';
    std::cout << str << std::endl;

}
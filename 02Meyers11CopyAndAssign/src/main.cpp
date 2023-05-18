#include <iostream>
#include "meyers/generalclass.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    GeneralClass GeneralClass1;
    std::cout << "GeneralClass1 value is " << GeneralClass1.GetValue() << std::endl;

    GeneralClass GeneralClass2 = GeneralClass1;

    std::cout << "GeneralClass2 value is " << GeneralClass2.GetValue() << std::endl;

    std::cout << "GeneralClass2 GetMegabyte is " << GeneralClass2.GetMegabyte() << std::endl;

    GeneralClass GeneralClass3 = GeneralClass1;
    GeneralClass1 = GeneralClass2;

    return 0;
}

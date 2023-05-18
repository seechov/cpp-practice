#include <iostream>
#include "meyers/extensivememoryuser.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    ExtensiveMemoryUser* ExtensiveMemoryUserEntity = new ExtensiveMemoryUser();
    std::cout << "ExtensiveMemoryUserEntity value is " << ExtensiveMemoryUserEntity->GetValue() << std::endl;

    ExtensiveMemoryUser* ExtensiveMemoryUserEntityCopy = new ExtensiveMemoryUser(*ExtensiveMemoryUserEntity);
    std::cout << "ExtensiveMemoryUserEntityCopy value is " << ExtensiveMemoryUserEntityCopy->GetValue() << std::endl;

    std::cout << "ExtensiveMemoryUserEntityCopy GetMegabyte is " << ExtensiveMemoryUserEntityCopy->GetMegabyte() << std::endl;

    delete ExtensiveMemoryUserEntity;
    delete ExtensiveMemoryUserEntityCopy;
    return 0;
}

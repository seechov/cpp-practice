#include <iostream>
#include "meyers/basictransitionfromc.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    BasicTransformFromC* basicTransformFromCEntity = new BasicTransformFromC();
    std::cout << "basicTransformFromCEntity value is " << basicTransformFromCEntity->GetValue() << std::endl;

    BasicTransformFromC* basicTransformFromCEntityCopy = new BasicTransformFromC(*basicTransformFromCEntity);
    std::cout << "basicTransformFromCEntityCopy value is " << basicTransformFromCEntityCopy->GetValue() << std::endl;

    std::cout << "basicTransformFromCEntityCopy GetMegabyte is " << basicTransformFromCEntityCopy->GetMegabyte() << std::endl;

    int a = 1;
    int b = 2;
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "BasicTransformFromC::MaxWithMacros(a, b) = " << BasicTransformFromC::MaxWithMacros(a, b) << std::endl;
    // how can we be sure that in macros we don't have a lot of (++a) expansions
    std::cout << "BasicTransformFromC::MaxWithMacros(++a, ++b) = " << BasicTransformFromC::MaxWithMacros(++a, ++b) << std::endl;
    std::cout << "a = " << a << "; b = " << b << std::endl;
    std::cout << "MaxFromBasicTransformFromCHeader(a++, b++) = " << MaxFromBasicTransformFromCHeader(a++, b++) << std::endl;
    std::cout << "a = " << a << "; b = " << b << std::endl;

    delete basicTransformFromCEntity;
    delete basicTransformFromCEntityCopy;
    return 0;
}

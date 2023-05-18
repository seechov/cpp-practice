#include <iostream>
#include "generalclass.h"

GeneralClass::GeneralClass() {
    std::cout << "Default constructor" << std::endl;
    ptr_ = new int(kGigabyte);
}

GeneralClass::GeneralClass(const GeneralClass& rhs) {
    std::cout << "Copy constructor" << std::endl;
    ptr_ = new int(*(rhs.ptr_));
}

GeneralClass& GeneralClass::operator= (const GeneralClass& rhs) {
    std::cout << "Assignment operator" << std::endl;
    ptr_ = new int(*(rhs.ptr_));
    return *this;
}

GeneralClass::~GeneralClass() {
    std::cout << "Deleting ptr_ " << ptr_ << std::endl;
    delete ptr_;
}

int GeneralClass::GetValue() {
    return *ptr_;
}

int GeneralClass::GetMegabyte() {
    return kMegabyte;
}

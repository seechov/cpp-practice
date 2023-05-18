#include "extensivememoryuser.h"

ExtensiveMemoryUser::ExtensiveMemoryUser() {
    ptr_ = new int(kGigabyte);
}

ExtensiveMemoryUser::ExtensiveMemoryUser(const ExtensiveMemoryUser& rhs) {
    ptr_ = new int(*(rhs.ptr_));
}

ExtensiveMemoryUser::~ExtensiveMemoryUser() {
    delete ptr_;
}

int ExtensiveMemoryUser::GetValue() {
    return *ptr_;
}

int ExtensiveMemoryUser::GetMegabyte() {
    return kMegabyte;
}

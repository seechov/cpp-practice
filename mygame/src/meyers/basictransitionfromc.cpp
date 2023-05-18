#include "basictransitionfromc.h"

#define kGigaByte 1073741824 // Avoid using macros if you can
#define MAX( X, Y ) ((a) > (b) ? (a) : (b))

BasicTransformFromC::BasicTransformFromC() {
    ptr_ = new int(kGigaByte);
}

BasicTransformFromC::BasicTransformFromC(const BasicTransformFromC& rhs) {
    ptr_ = new int(*(rhs.ptr_));
}

BasicTransformFromC::~BasicTransformFromC() {
    delete ptr_;
}

int BasicTransformFromC::GetValue() {
    return *ptr_;
}

int BasicTransformFromC::GetMegabyte() {
    return kMegabyte;
}

int BasicTransformFromC::MaxWithMacros(int& a, int& b) {
    return MAX(a, b);
}

#undef kGigaByte //  if you use macros, you should undef it right after usage
#undef ADD
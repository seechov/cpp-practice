#ifndef CPPPRACTICE_MEYERS_EXTENSIVEMEMORYUSER_H_
#define CPPPRACTICE_MEYERS_EXTENSIVEMEMORYUSER_H_
// All header files should have #define guards to prevent multiple inclusion.
// https://google.github.io/styleguide/cppguide.html#The__define_Guard

#include "newhandlersupport.h"

class ExtensiveMemoryUser: public NewHandlerSupport<ExtensiveMemoryUser> {
  public:
    ExtensiveMemoryUser();                              // public constructor
    ExtensiveMemoryUser(const ExtensiveMemoryUser&);    // public copy constructor
    virtual ~ExtensiveMemoryUser();                     // public virtual destructor
    int GetValue();
    int GetMegabyte();
  private:
    int* ptr_;                                           // private data member
    static const int kMegabyte = 1048576;
    static const int kGigabyte = 1073741824;
};

#endif  // CPPPRACTICE_MEYERS_EXTENSIVEMEMORYUSER_H_

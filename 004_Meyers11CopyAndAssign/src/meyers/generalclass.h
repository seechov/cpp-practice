#ifndef CPPPRACTICE_MEYERS_GENERALCLASS_H_
#define CPPPRACTICE_MEYERS_GENERALCLASS_H_
// All header files should have #define guards to prevent multiple inclusion.
// https://google.github.io/styleguide/cppguide.html#The__define_Guard

#include "generalclass.h"

class GeneralClass {
  public:
    GeneralClass();                                     // public constructor
    GeneralClass(const GeneralClass&);                  // public copy constructor
    virtual ~GeneralClass();                            // public virtual destructor
    GeneralClass& operator= (const GeneralClass&);      // public assignment operator
    int GetValue();
    int GetMegabyte();
  private:
    int* ptr_;                                          // private data member
    static const int kMegabyte = 1048576;
    static const int kGigabyte = 1073741824;
};

#endif  // CPPPRACTICE_MEYERS_GENERALCLASS_H_

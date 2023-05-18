#ifndef CPPPRACTICE_MEYERS_NEWHANDLERSUPPORT_H_
#define CPPPRACTICE_MEYERS_NEWHANDLERSUPPORT_H_
// All header files should have #define guards to prevent multiple inclusion.
// https://google.github.io/styleguide/cppguide.html#The__define_Guard

#include <iostream>
#include <new>

/******************************************************************************************/
template <class T>
class NewHandlerSupport {
  public:
    /// new operater using this class
    static void* operator new(size_t size);
    /// set a new_handler for this class
    static std::new_handler set_new_handler(std::new_handler);
  private:
    static std::new_handler new_handler_;
};

#endif  // CPPPRACTICE_MEYERS_NEWHANDLERSUPPORT_H_

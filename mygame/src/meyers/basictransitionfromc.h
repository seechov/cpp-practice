#ifndef CPPPRACTICE_MEYERS_BASICTRANSFORMFROMC_H_
#define CPPPRACTICE_MEYERS_BASICTRANSFORMFROMC_H_
// All header files should have #define guards to prevent multiple inclusion.
// https://google.github.io/styleguide/cppguide.html#The__define_Guard

template<class T>
inline static const T& MaxFromBasicTransformFromCHeader(const T& a, const T& b) {
    return a > b ? a : b;
}

class BasicTransformFromC {
  public:
    BasicTransformFromC();                              // public constructor
    BasicTransformFromC(const BasicTransformFromC&);    // public copy constructor
    virtual ~BasicTransformFromC();                     // public virtual destructor
    int GetValue();
    int GetMegabyte();
    static int MaxWithMacros(int&, int&);
  private:
    int* ptr_;                                           // private data member
    static const int kMegabyte = 1048576;
};

#endif  // CPPPRACTICE_MEYERS_BASICTRANSFORMFROMC_H_

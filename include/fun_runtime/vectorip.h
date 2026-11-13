// STAND-IN: pointer-element specialization of the reference cVectorip<T,N>.
// The reference places last_ at 0 and its 16-byte-aligned inline storage at 0x10.
// CD2 cVehicle::RetNumberOfSeats (0x826D5008) confirms the pointer difference.
#ifndef FUN_RUNTIME_VECTORIP_H
#define FUN_RUNTIME_VECTORIP_H
#include "cd2/layout.h"
namespace Fun_Runtime
{
    template <class T, unsigned int N> class cVectorip;
    template <class T, unsigned int N>
    class cVectorip<T *, N>
    {
    public:
        cVectorip() : last_(data_) {}
        unsigned int size() const { return last_ - data_; }
        T *&operator[](unsigned int i) { return data_[i]; }
        // Pointer iterators, as cDocksMission's mission loops (0x82474A40, 0x82474D60) walk the inline storage.
        T **begin() { return data_; }
        T **end() { return last_; }
        T *const *begin() const { return data_; }
        T *const *end() const { return last_; }
    private:
        T **last_;
        __declspec(align(16)) T *data_[N];
        CD2_LAYOUT_CHECKS(cVectorip,
            CD2_SIZE(cVectorip, (16 + N * sizeof(T *) + 15) & ~15)
            CD2_OFFSET(cVectorip, last_, 0)
            CD2_OFFSET(cVectorip, data_, 0x10))
    };
}
#endif

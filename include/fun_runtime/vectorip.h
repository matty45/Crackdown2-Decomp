// STAND-IN: pointer-element specialization of the reference cVectorip<T,N>.
// The reference places last_ at 0 and its 16-byte-aligned inline storage at 0x10.
// CD2 cVehicle::RetNumberOfSeats (0x826D5008) confirms the pointer difference.
#ifndef FUN_RUNTIME_VECTORIP_H
#define FUN_RUNTIME_VECTORIP_H
#include <new>
#include <string.h>
#include "cd2/layout.h"
namespace Fun_Runtime
{
    // RuffKing's uninitialized_array<T,N>: storage for N elements that constructs and destroys none of them, aligned by
    // a 16-byte member of its union (forceAlignStruct).
    template <class T, unsigned int N>
    class uninitialized_array
    {
    public:
        T *begin() { return reinterpret_cast<T *>(buffer_); }
        const T *begin() const { return reinterpret_cast<const T *>(buffer_); }
    private:
        struct __declspec(align(16)) forceAlignStruct { char aByte_; };
        union
        {
            char buffer_[N * sizeof(T)];
            forceAlignStruct dummy2_;
        };
    };

    // Object elements (RuffKing's cVectorip<Vehicle::cVehicleTurret,3>: last_ at 0, its uninitialized_array of the
    // elements at 0x10, 0x1B0 bytes). CD2's cVehicle::RetVehicleTurret (0x826D5020) divides the byte difference by the
    // element size; cVehicle's destructor (0x826CE0E8) destroys the elements from the first to last_, as RuffKing's
    // destructor's destroy(begin, last_) does.
    template <class T, unsigned int N>
    class cVectorip
    {
    public:
        // CD2 expands the destructor's destroy loop in its owner's destructor (cVehicle's, 0x826CE0E8); with ordinary
        // inline, /Ob1 keeps both calls.
        __forceinline ~cVectorip() { destroy(begin(), last_); }
        T *begin() { return data_.begin(); }
        const T *begin() const { return data_.begin(); }
        T *end() { return last_; }
        const T *end() const { return last_; }
        unsigned int size() const { return last_ - data_.begin(); }
        T &operator[](unsigned int i) { return begin()[i]; }
    protected:
        __forceinline void destroy(T *first, T *last)
        {
            while (first != last) (first++)->~T();
        }
    private:
        T *last_;
        uninitialized_array<T, N> data_;
        CD2_LAYOUT_CHECKS(cVectorip,
            CD2_SIZE(cVectorip, (16 + N * sizeof(T) + 15) & ~15)
            CD2_OFFSET(cVectorip, last_, 0)
            CD2_OFFSET(cVectorip, data_, 0x10))
    };
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
        // RuffKing's checks the capacity first; CD2's expansion (cAmbientEventMission::HandleAttributes, 0x8248DFC0)
        // only constructs the element in place, with placement new's null test, and reloads last_ to advance it.
        void push_back(T *const &val)
        {
            ::new (static_cast<void *>(last_)) T *(val);
            ++last_;
        }
        // RuffKing's (out of line there: cVectorip<Damage::Response *,64>::erase 0x82993930, erase_n 0x82991F40);
        // CD2 expands both in cLOD4Environment's destructor (0x82807A38), without erase_n's capacity check.
        T **erase(T **pos)
        {
            if (pos == last_)
                --last_;
            else
                erase_n(pos, 1);
            return pos;
        }
    protected:
        void erase_n(T **pos, unsigned int n)
        {
            T **src = pos + n;
            int count = last_ - src;
            T **newLast = pos + count;
            if (count > 0)
                memmove_s(pos, count * sizeof(T *), src, count * sizeof(T *));
            last_ = newLast;
        }
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

// Shared cVector wrapper, originally reconstructed for cRopes.
// CD2 calls push_back and clear out of line. The 16-byte layout is the XDK vector plus its allocator slot.
#ifndef FUN_RUNTIME_VECTOR_H
#define FUN_RUNTIME_VECTOR_H

#define _SECURE_SCL 0
#include <vector>
#include "fun_runtime/allocator.h"

namespace Fun_Runtime
{
    template <class T>
    class cVector : public std::vector<T, cAllocator<T> >
    {
    public:
        // Reference cvector.h exposes the standard-container base under this name.
        typedef std::vector<T, cAllocator<T> > MyBase;
        void push_back(const T &value);
        void clear();
    };

    template <class T>
    void cVector<T>::clear()
    {
        std::vector<T, cAllocator<T> >::clear();
    }

    template <class T>
    void cVector<T>::push_back(const T &value)
    {
        std::vector<T, cAllocator<T> >::push_back(value);
    }
}

#endif

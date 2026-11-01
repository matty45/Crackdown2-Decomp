// Shared allocator stand-in, originally reconstructed for cRopes' vectors.
// Allocation is out of line; deallocation calls the game's heap release.
#ifndef FUN_RUNTIME_ALLOCATOR_H
#define FUN_RUNTIME_ALLOCATOR_H
#include <stddef.h>
#include <new>
#include "cd2/memory.h"
namespace Fun_Runtime
{
    template <class T>
    class cAllocator
    {
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef T &reference;
        typedef const T &const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        template <class U> struct rebind { typedef cAllocator<U> other; };
        cAllocator() {}
        cAllocator(const cAllocator &) {}
        template <class U> cAllocator(const cAllocator<U> &) {}
        static pointer allocate(size_type n);
        void deallocate(pointer p, size_type) { XDestroyHeapBlock(p); }
        void construct(pointer p, const T &v) { new ((void *)p) T(v); }
        void destroy(pointer) {}
        pointer address(reference r) const { return &r; }
        const_pointer address(const_reference r) const { return &r; }
        size_type max_size() const { return 0x3FFFFFFF; }
    };
}
#endif

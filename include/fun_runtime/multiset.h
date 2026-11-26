// STAND-IN: the reference cMultiSet inherits std::multiset without adding members (RuffKing, cTimeOfDay.h: 12 bytes).
// Like the shared map and vector wrappers, this uses the release allocator interface.
#ifndef FUN_RUNTIME_MULTISET_H
#define FUN_RUNTIME_MULTISET_H
#define _SECURE_SCL 0
#include <set>
#include "fun_runtime/allocator.h"
namespace Fun_Runtime
{
    template <class Key, class Compare = std::less<Key>, class Allocator = cAllocator<Key> >
    class cMultiSet : public std::multiset<Key, Compare, Allocator>
    {
    public:
        typedef std::multiset<Key, Compare, Allocator> MyBase;
    };
}
#endif

// STAND-IN: the reference cMap inherits std::map without adding members.
// Like the shared vector wrapper, this uses the release allocator interface.
#ifndef FUN_RUNTIME_MAP_H
#define FUN_RUNTIME_MAP_H
#define _SECURE_SCL 0
#include <map>
#include "fun_runtime/allocator.h"
namespace Fun_Runtime
{
    template <class Key, class T, class Compare = std::less<Key>,
              class Allocator = cAllocator<std::pair<Key, T> > >
    class cMap : public std::map<Key, T, Compare, Allocator>
    {
    public:
        typedef std::map<Key, T, Compare, Allocator> MyBase;
        // CD2 keeps map construction out of line in the profile's array initializer.
        cMap();
    };
}
#endif

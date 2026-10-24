// Compile-time layout checks for headers reconstructed from the reference PDBs.
//
// MSVC 2008 (the Xbox 360 XDK compiler) has no static_assert. These macros use the negative-array-size trick: a wrong
// size or offset fails the build with error C2118 ("negative subscript") on the offending line.
//
// Put CD2_LAYOUT_CHECKS at the very end of a class body (it opens a public section) and list the checks inside it.
// The checks live in an inline static member function that is never called, so no code is ever emitted for them and
// the class's other members, mangled names and vtable are unaffected. Being a member function, it may name private
// members.
//
//     class cFoo {
//         int m_a;
//         ...
//         CD2_LAYOUT_CHECKS(cFoo,
//             CD2_SIZE(cFoo, 0x50)
//             CD2_OFFSET(cFoo, m_a, 0x04))
//     };
#ifndef CD2_LAYOUT_H
#define CD2_LAYOUT_H

#include <stddef.h>

#define CD2_LAYOUT_CHECKS(T, checks) \
    public: static void cd2_layout_check_() { checks }

#define CD2_SIZE(T, n) \
    { typedef char cd2_size_check_[(sizeof(T) == (n)) ? 1 : -1]; }

#define CD2_OFFSET(T, member, off) \
    { typedef char cd2_offset_check_[(offsetof(T, member) == (off)) ? 1 : -1]; }

#endif // CD2_LAYOUT_H

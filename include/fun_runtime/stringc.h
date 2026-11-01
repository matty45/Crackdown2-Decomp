// STAND-IN for the default cStringc interface. RuffKing cString.h derives this type
// from basic_string with cAllocator; CD2 cLoadingInfo uses its 28-byte layout.
#ifndef FUN_RUNTIME_STRINGC_H
#define FUN_RUNTIME_STRINGC_H
#define _SECURE_SCL 0
#include <string>
#include "fun_runtime/allocator.h"
#include "cd2/layout.h"
namespace Fun_Runtime
{
    class cStringc : public std::basic_string<char, std::char_traits<char>, cAllocator<char> >
    {
        typedef std::basic_string<char, std::char_traits<char>, cAllocator<char> > MyBase;
    public:
        cStringc() {}
        cStringc(const char *text) : MyBase(text) {}
        CD2_LAYOUT_CHECKS(cStringc,
            CD2_SIZE(cStringc, 0x1C))
    };
}
#endif

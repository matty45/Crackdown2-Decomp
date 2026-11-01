// Fun_Runtime::cString: wide counterpart of cStringc from the reference cString.h.
// CD2's cAIAnimEventProfile destructor uses the 28-byte string layout and an 8-wchar small buffer.
#ifndef FUN_RUNTIME_STRING_H
#define FUN_RUNTIME_STRING_H

#define _SECURE_SCL 0
#include <string>
#include "fun_runtime/allocator.h"
#include "cd2/layout.h"

namespace Fun_Runtime
{
    class cString : public std::basic_string<wchar_t, std::char_traits<wchar_t>, cAllocator<wchar_t> >
    {
    public:
        cString() {}
        cString(const char *text);

        CD2_LAYOUT_CHECKS(cString, CD2_SIZE(cString, 0x1C))
    };
}

#endif

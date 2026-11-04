// unknown::cTransforming (Crackdown 2): STAND-IN with only its runtime class descriptor; its layout is not modelled yet.
// Its StaticCreateClass is CD2 0x826A68F8 (names the class "cTransforming"); derived classes register it as their parent.
#ifndef UNKNOWN_CTRANSFORMING_H
#define UNKNOWN_CTRANSFORMING_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cTransforming
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CTRANSFORMING_H

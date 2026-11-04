// unknown::cZone (Crackdown 2): STAND-IN with only its runtime class descriptor; its layout is not modelled yet.
// Its StaticCreateClass is CD2 0x8280B7A0 (names the class "cZone"); derived classes register it as their parent.
#ifndef UNKNOWN_CZONE_H
#define UNKNOWN_CZONE_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cZone
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CZONE_H

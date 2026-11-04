// unknown::cInterestingObject (Crackdown 2): STAND-IN with only its runtime class descriptor; its layout is not modelled yet.
// Its StaticCreateClass is CD2 0x82454A88 (names the class "cInterestingObject"); derived classes register it as their parent.
#ifndef UNKNOWN_CINTERESTINGOBJECT_H
#define UNKNOWN_CINTERESTINGOBJECT_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cInterestingObject
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CINTERESTINGOBJECT_H

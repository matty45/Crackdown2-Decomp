// unknown::cInterestingObject: CD2 stand-in. Constructor 0x82453E98 initializes
// cScriptHost at +0, including its registered-class interface at +0x14, then its
// own fields at +0x1C..0x3C. The descriptor establishes size 0x40.
// Its StaticCreateClass is CD2 0x82454A88 (names the class "cInterestingObject"); derived classes register it as their parent.
#ifndef UNKNOWN_CINTERESTINGOBJECT_H
#define UNKNOWN_CINTERESTINGOBJECT_H

#include "fun_runtime/class.h"
#include "fun_runtime/scripthost.h"

namespace unknown
{
    class cInterestingObject : public Fun_Runtime::cScriptHost
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcInterestingObjectClass;
    private:
        unsigned char m_unmodelled1C[0x40 - 0x1C];
        CD2_LAYOUT_CHECKS(cInterestingObject, CD2_SIZE(cInterestingObject, 0x40))
    };
}

#endif // UNKNOWN_CINTERESTINGOBJECT_H

// unknown::cZone: CD2 stand-in. Constructor 0x8280B838 initializes cScriptHost
// (registered-class interface at +0x14) and a narrow string at +0x1C. Descriptor
// size 0x38 agrees with that layout; the member's descriptive name is ours.
// Its StaticCreateClass is CD2 0x8280B7A0 (names the class "cZone"); derived classes register it as their parent.
#ifndef UNKNOWN_CZONE_H
#define UNKNOWN_CZONE_H

#include "fun_runtime/class.h"
#include "fun_runtime/scripthost.h"
#include "fun_runtime/stringc.h"

namespace unknown
{
    class cZone : public Fun_Runtime::cScriptHost
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        cZone(); // CD2 0x8280B838, out of line
        virtual ~cZone(); // CD2 0x8280B6D0, out of line
    private:
        Fun_Runtime::cStringc m_strName;
        CD2_LAYOUT_CHECKS(cZone,
            CD2_SIZE(cZone, 0x38)
            CD2_OFFSET(cZone, m_strName, 0x1C))
    };
}

#endif // UNKNOWN_CZONE_H

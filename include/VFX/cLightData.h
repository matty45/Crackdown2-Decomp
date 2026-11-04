#ifndef VFX_cLightData_H
#define VFX_cLightData_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace VFX
{
    class cLightData : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x82800828 (MakeNew calls it).
        cLightData();

    private:
        unsigned char m_unmodelled18[0x1A0 - 0x18];

        CD2_LAYOUT_CHECKS(cLightData, CD2_SIZE(cLightData, 0x1A0))

    };
}

#endif

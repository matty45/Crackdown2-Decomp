#ifndef VFX_cSkyDome_H
#define VFX_cSkyDome_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace VFX
{
    class cSkyDome : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x827B8BB0 (MakeNew calls it).
        cSkyDome();

    private:
        unsigned char m_unmodelled18[0x4D0 - 0x18];

        CD2_LAYOUT_CHECKS(cSkyDome, CD2_SIZE(cSkyDome, 0x4D0))

    };
}

#endif

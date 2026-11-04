#ifndef unknown_cHordeBeam_H
#define unknown_cHordeBeam_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace unknown
{
    class cHordeBeam : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x82867970 (MakeNew calls it with the packet).
        cHordeBeam(const RWS::CAttributePacket &packet);

    private:
        unsigned char m_unmodelled18[0xA0 - 0x18];

        CD2_LAYOUT_CHECKS(cHordeBeam, CD2_SIZE(cHordeBeam, 0xA0))

    };
}

#endif

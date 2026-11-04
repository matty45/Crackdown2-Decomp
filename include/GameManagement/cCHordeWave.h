#ifndef GameManagement_cCHordeWave_H
#define GameManagement_cCHordeWave_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace GameManagement
{
    class cCHordeWave : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x82865D00 (MakeNew calls it with the packet).
        cCHordeWave(const RWS::CAttributePacket &packet);

    private:
        unsigned char m_unmodelled18[0x238 - 0x18];

        CD2_LAYOUT_CHECKS(cCHordeWave, CD2_SIZE(cCHordeWave, 0x238))

    };
}

#endif

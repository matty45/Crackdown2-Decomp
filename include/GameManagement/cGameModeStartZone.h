#ifndef GameManagement_cGameModeStartZone_H
#define GameManagement_cGameModeStartZone_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace GameManagement
{
    class cGameModeStartZone : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x821D2840 (MakeNew calls it).
        cGameModeStartZone();

    private:
        unsigned char m_unmodelled18[0x3D0 - 0x18];

        CD2_LAYOUT_CHECKS(cGameModeStartZone, CD2_SIZE(cGameModeStartZone, 0x3D0))

    };
}

#endif

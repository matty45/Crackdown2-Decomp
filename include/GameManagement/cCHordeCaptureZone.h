#ifndef GameManagement_cCHordeCaptureZone_H
#define GameManagement_cCHordeCaptureZone_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace GameManagement
{
    class cCHordeCaptureZone : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x82858D38 (MakeNew calls it with the packet).
        cCHordeCaptureZone(const RWS::CAttributePacket &packet);

    private:
        unsigned char m_unmodelled18[0x390 - 0x18];

        CD2_LAYOUT_CHECKS(cCHordeCaptureZone, CD2_SIZE(cCHordeCaptureZone, 0x390))

    };
}

#endif

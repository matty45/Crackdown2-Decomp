#ifndef AI_cForceFieldProfile_H
#define AI_cForceFieldProfile_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace AI
{
    class cForceFieldProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x82488A08 (MakeNew calls it with the packet).
        cForceFieldProfile(const RWS::CAttributePacket &packet);

    private:
        unsigned char m_unmodelled18[0x130 - 0x18];

        CD2_LAYOUT_CHECKS(cForceFieldProfile, CD2_SIZE(cForceFieldProfile, 0x130))

    };
}

#endif

#ifndef CHARACTER_cGlobalControlsProfile_H
#define CHARACTER_cGlobalControlsProfile_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace CHARACTER
{
    class cGlobalControlsProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x825587D0 (MakeNew calls it).
        cGlobalControlsProfile();

    private:
        unsigned char m_unmodelled18[0x18C - 0x18];

        CD2_LAYOUT_CHECKS(cGlobalControlsProfile, CD2_SIZE(cGlobalControlsProfile, 0x18C))

    };
}

#endif

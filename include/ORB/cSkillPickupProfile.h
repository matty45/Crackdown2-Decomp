#ifndef ORB_cSkillPickupProfile_H
#define ORB_cSkillPickupProfile_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace ORB
{
    class cSkillPickupProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x82756D70 (MakeNew calls it).
        cSkillPickupProfile();

    private:
        unsigned char m_unmodelled18[0xB0 - 0x18];

        CD2_LAYOUT_CHECKS(cSkillPickupProfile, CD2_SIZE(cSkillPickupProfile, 0xB0))

    };
}

#endif

#ifndef ORB_cSkillPickupProfile_H
#define ORB_cSkillPickupProfile_H

#include "rws/attributes.h"

namespace ORB
{
    class cSkillPickupProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

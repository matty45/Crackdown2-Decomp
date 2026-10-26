#ifndef ORB_cSkillPickupProfile_H
#define ORB_cSkillPickupProfile_H

#include "rws/attributes.h"

namespace ORB
{
    class cSkillPickupProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

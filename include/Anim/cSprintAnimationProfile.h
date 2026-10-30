#ifndef Anim_cSprintAnimationProfile_H
#define Anim_cSprintAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cSprintAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

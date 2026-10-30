#ifndef Anim_cCrowdAnimationProfile_H
#define Anim_cCrowdAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cCrowdAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

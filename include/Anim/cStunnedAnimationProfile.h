#ifndef Anim_cStunnedAnimationProfile_H
#define Anim_cStunnedAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cStunnedAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

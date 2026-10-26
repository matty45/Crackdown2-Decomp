#ifndef Anim_cCrowdAnimationProfile_H
#define Anim_cCrowdAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cCrowdAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

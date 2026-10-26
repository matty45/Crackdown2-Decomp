#ifndef Anim_cStandAnimationProfile_H
#define Anim_cStandAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cStandAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

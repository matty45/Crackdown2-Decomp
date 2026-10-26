#ifndef Anim_cDeathAnimationProfile_H
#define Anim_cDeathAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cDeathAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

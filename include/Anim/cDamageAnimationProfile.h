#ifndef Anim_cDamageAnimationProfile_H
#define Anim_cDamageAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cDamageAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

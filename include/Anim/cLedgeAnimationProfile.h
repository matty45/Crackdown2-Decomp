#ifndef Anim_cLedgeAnimationProfile_H
#define Anim_cLedgeAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cLedgeAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

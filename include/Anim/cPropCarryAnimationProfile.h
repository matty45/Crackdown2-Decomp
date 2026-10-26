#ifndef Anim_cPropCarryAnimationProfile_H
#define Anim_cPropCarryAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cPropCarryAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

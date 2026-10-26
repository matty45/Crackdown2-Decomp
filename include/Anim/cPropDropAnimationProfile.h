#ifndef Anim_cPropDropAnimationProfile_H
#define Anim_cPropDropAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cPropDropAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

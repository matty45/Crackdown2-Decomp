#ifndef Anim_cPropPickUpAnimationProfile_H
#define Anim_cPropPickUpAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cPropPickUpAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

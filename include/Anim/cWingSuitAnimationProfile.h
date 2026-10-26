#ifndef Anim_cWingSuitAnimationProfile_H
#define Anim_cWingSuitAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cWingSuitAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

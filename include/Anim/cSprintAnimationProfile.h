#ifndef Anim_cSprintAnimationProfile_H
#define Anim_cSprintAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cSprintAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

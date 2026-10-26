#ifndef Anim_cRunWalkAnimationProfile_H
#define Anim_cRunWalkAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cRunWalkAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

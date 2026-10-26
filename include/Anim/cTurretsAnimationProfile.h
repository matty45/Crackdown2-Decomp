#ifndef Anim_cTurretsAnimationProfile_H
#define Anim_cTurretsAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cTurretsAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

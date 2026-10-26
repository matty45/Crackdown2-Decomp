#ifndef Anim_cRappelAnimationProfile_H
#define Anim_cRappelAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cRappelAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

#ifndef Anim_cJumpLandAnimationProfile_H
#define Anim_cJumpLandAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cJumpLandAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

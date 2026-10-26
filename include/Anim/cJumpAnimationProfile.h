#ifndef Anim_cJumpAnimationProfile_H
#define Anim_cJumpAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cJumpAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

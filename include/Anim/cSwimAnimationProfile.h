#ifndef Anim_cSwimAnimationProfile_H
#define Anim_cSwimAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cSwimAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

#ifndef Anim_cNPCBargeAnimationProfile_H
#define Anim_cNPCBargeAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cNPCBargeAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

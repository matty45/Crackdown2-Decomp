#ifndef Anim_cGenericUpperBodyAnimationProfile_H
#define Anim_cGenericUpperBodyAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cGenericUpperBodyAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

#ifndef Anim_cGenericFullBodyAnimationProfile_H
#define Anim_cGenericFullBodyAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cGenericFullBodyAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

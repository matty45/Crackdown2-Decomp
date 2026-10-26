#ifndef Anim_cBasePoseAnimationProfile_H
#define Anim_cBasePoseAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cBasePoseAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

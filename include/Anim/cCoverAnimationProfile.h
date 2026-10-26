#ifndef Anim_cCoverAnimationProfile_H
#define Anim_cCoverAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cCoverAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

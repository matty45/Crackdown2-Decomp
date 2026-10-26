#ifndef Anim_cGoliathAnimationProfile_H
#define Anim_cGoliathAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cGoliathAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

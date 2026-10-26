#ifndef Anim_cLandVehicleAnimationProfile_H
#define Anim_cLandVehicleAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cLandVehicleAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

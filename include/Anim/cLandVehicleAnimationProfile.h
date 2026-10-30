#ifndef Anim_cLandVehicleAnimationProfile_H
#define Anim_cLandVehicleAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cLandVehicleAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

#ifndef Anim_cEquipmentCarryAnimationProfile_H
#define Anim_cEquipmentCarryAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cEquipmentCarryAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

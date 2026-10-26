#ifndef Anim_cEquipmentReloadAnimationProfile_H
#define Anim_cEquipmentReloadAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cEquipmentReloadAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

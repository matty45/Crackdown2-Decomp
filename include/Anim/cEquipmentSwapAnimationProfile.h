#ifndef Anim_cEquipmentSwapAnimationProfile_H
#define Anim_cEquipmentSwapAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cEquipmentSwapAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

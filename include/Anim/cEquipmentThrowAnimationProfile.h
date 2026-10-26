#ifndef Anim_cEquipmentThrowAnimationProfile_H
#define Anim_cEquipmentThrowAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cEquipmentThrowAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

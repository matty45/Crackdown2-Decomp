#ifndef Anim_cEquipmentAimAndFireAnimationProfile_H
#define Anim_cEquipmentAimAndFireAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cEquipmentAimAndFireAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

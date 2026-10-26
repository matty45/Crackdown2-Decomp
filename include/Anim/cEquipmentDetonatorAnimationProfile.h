#ifndef Anim_cEquipmentDetonatorAnimationProfile_H
#define Anim_cEquipmentDetonatorAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cEquipmentDetonatorAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

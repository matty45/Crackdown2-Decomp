#ifndef Anim_cEquipmentCarryAnimationProfile_H
#define Anim_cEquipmentCarryAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cEquipmentCarryAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

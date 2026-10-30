#ifndef Anim_cEquipmentPickUpAnimationProfile_H
#define Anim_cEquipmentPickUpAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cEquipmentPickUpAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

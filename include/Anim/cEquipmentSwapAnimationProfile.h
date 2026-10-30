#ifndef Anim_cEquipmentSwapAnimationProfile_H
#define Anim_cEquipmentSwapAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cEquipmentSwapAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

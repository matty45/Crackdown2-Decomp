#ifndef Anim_cEquipmentThrowNPCFullAnimationProfile_H
#define Anim_cEquipmentThrowNPCFullAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cEquipmentThrowNPCFullAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

#ifndef Anim_cStunnedAnimationProfile_H
#define Anim_cStunnedAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cStunnedAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

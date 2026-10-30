#ifndef Anim_cStandTurnAnimationProfile_H
#define Anim_cStandTurnAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cStandTurnAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

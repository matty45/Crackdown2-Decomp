#ifndef Anim_cJumpLandFastAnimationProfile_H
#define Anim_cJumpLandFastAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cJumpLandFastAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

#ifndef Anim_cJumpLandAnimationProfile_H
#define Anim_cJumpLandAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cJumpLandAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

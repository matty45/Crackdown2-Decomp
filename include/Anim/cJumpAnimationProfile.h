#ifndef Anim_cJumpAnimationProfile_H
#define Anim_cJumpAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cJumpAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

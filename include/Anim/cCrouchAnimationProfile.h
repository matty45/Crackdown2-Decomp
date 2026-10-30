#ifndef Anim_cCrouchAnimationProfile_H
#define Anim_cCrouchAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cCrouchAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

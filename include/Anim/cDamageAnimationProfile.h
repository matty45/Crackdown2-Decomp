#ifndef Anim_cDamageAnimationProfile_H
#define Anim_cDamageAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cDamageAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

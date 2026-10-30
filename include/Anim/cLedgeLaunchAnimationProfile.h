#ifndef Anim_cLedgeLaunchAnimationProfile_H
#define Anim_cLedgeLaunchAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cLedgeLaunchAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

#ifndef Anim_cPropCarryNPCAnimationProfile_H
#define Anim_cPropCarryNPCAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cPropCarryNPCAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

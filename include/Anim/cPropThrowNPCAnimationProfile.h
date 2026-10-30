#ifndef Anim_cPropThrowNPCAnimationProfile_H
#define Anim_cPropThrowNPCAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cPropThrowNPCAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

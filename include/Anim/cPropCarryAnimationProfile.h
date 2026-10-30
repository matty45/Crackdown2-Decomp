#ifndef Anim_cPropCarryAnimationProfile_H
#define Anim_cPropCarryAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cPropCarryAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

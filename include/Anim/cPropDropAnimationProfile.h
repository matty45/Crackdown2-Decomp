#ifndef Anim_cPropDropAnimationProfile_H
#define Anim_cPropDropAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cPropDropAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

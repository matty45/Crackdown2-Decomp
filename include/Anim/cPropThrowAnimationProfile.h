#ifndef Anim_cPropThrowAnimationProfile_H
#define Anim_cPropThrowAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cPropThrowAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

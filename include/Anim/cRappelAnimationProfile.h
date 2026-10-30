#ifndef Anim_cRappelAnimationProfile_H
#define Anim_cRappelAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cRappelAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

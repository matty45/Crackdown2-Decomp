#ifndef Anim_cGenericUpperBodyAnimationProfile_H
#define Anim_cGenericUpperBodyAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cGenericUpperBodyAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

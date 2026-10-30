#ifndef Anim_cGenericFullBodyAnimationProfile_H
#define Anim_cGenericFullBodyAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cGenericFullBodyAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

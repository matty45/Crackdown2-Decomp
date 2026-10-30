#ifndef Anim_cCoverAnimationProfile_H
#define Anim_cCoverAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cCoverAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

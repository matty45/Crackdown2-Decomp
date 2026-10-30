#ifndef Anim_cNPCBargeAnimationProfile_H
#define Anim_cNPCBargeAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cNPCBargeAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

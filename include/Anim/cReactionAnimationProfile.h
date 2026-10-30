#ifndef Anim_cReactionAnimationProfile_H
#define Anim_cReactionAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cReactionAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

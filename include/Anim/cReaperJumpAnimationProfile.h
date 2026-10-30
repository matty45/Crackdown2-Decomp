#ifndef Anim_cReaperJumpAnimationProfile_H
#define Anim_cReaperJumpAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cReaperJumpAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

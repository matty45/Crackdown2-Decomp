#ifndef Anim_cReaperPropAttackAnimationProfile_H
#define Anim_cReaperPropAttackAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cReaperPropAttackAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

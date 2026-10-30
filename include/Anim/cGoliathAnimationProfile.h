#ifndef Anim_cGoliathAnimationProfile_H
#define Anim_cGoliathAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cGoliathAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

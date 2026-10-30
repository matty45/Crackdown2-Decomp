#ifndef CHARACTER_cGameDamageProfile_H
#define CHARACTER_cGameDamageProfile_H

#include "rws/attributes.h"

namespace CHARACTER
{
    class cGameDamageProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

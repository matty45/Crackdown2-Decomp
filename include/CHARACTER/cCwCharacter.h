#ifndef CHARACTER_cCwCharacter_H
#define CHARACTER_cCwCharacter_H

#include "rws/attributes.h"

namespace CHARACTER
{
    class cCwCharacter : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

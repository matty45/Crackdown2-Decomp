#ifndef CHARACTER_cCwGoliathCharacterWrapper_H
#define CHARACTER_cCwGoliathCharacterWrapper_H

#include "rws/attributes.h"

namespace CHARACTER
{
    class cCwGoliathCharacterWrapper : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

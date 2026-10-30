#ifndef CHARACTER_cCwCharacterStateProfile_H
#define CHARACTER_cCwCharacterStateProfile_H

#include "rws/attributes.h"

namespace CHARACTER
{
    class cCwCharacterStateProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

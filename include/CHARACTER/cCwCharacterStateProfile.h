#ifndef CHARACTER_cCwCharacterStateProfile_H
#define CHARACTER_cCwCharacterStateProfile_H

#include "rws/attributes.h"

namespace CHARACTER
{
    class cCwCharacterStateProfile : public RWS::CAttributeHandler
    {
    public:
        // CD2 0x82540550: attribute-handler vtable slot 5, returning Ret_OK.
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual const char *RetCharacterStates() const;
    };
}

#endif

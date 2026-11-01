#ifndef CHARACTER_cCharacterProfile_H
#define CHARACTER_cCharacterProfile_H

#include "rws/attributes.h"

namespace CHARACTER
{
    class cCharacterProfile : public RWS::CAttributeHandler
    {
    public:
        // CD2 0x82553650: attribute-handler vtable slot 5, returning Ret_OK.
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

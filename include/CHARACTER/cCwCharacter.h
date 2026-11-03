#include "fun_runtime/class.h"
#ifndef CHARACTER_cCwCharacter_H
#define CHARACTER_cCwCharacter_H

#include "rws/attributes.h"

namespace CHARACTER
{
    class cCwCharacter : public RWS::CAttributeHandler
    {
    public:
        // CD2 0x8253F4D8 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

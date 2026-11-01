#ifndef CHARACTER_cStrengthSkillProfile_H
#define CHARACTER_cStrengthSkillProfile_H

#include "rws/attributes.h"

namespace CHARACTER
{
    class cStrengthSkillProfile : public RWS::CAttributeHandler
    {
    public:
        // CD2 0x8255A778: attribute-handler vtable slot 6, returning Ret_OK.
        virtual Fun_Runtime::RetVal Term();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

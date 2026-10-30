#ifndef CHARACTER_cStrengthSkillProfile_H
#define CHARACTER_cStrengthSkillProfile_H

#include "rws/attributes.h"

namespace CHARACTER
{
    class cStrengthSkillProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

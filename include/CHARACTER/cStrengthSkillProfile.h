#ifndef CHARACTER_cStrengthSkillProfile_H
#define CHARACTER_cStrengthSkillProfile_H

#include "rws/attributes.h"

namespace CHARACTER
{
    class cStrengthSkillProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

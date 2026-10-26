#ifndef CHARACTER_cCwCharacter_H
#define CHARACTER_cCwCharacter_H

#include "rws/attributes.h"

namespace CHARACTER
{
    class cCwCharacter : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

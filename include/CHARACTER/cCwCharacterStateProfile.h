#ifndef CHARACTER_cCwCharacterStateProfile_H
#define CHARACTER_cCwCharacterStateProfile_H

#include "rws/attributes.h"

namespace CHARACTER
{
    class cCwCharacterStateProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

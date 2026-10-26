#ifndef CHARACTER_cCharacterProfile_H
#define CHARACTER_cCharacterProfile_H

#include "rws/attributes.h"

namespace CHARACTER
{
    class cCharacterProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

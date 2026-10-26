#ifndef CHARACTER_cCharacterGlobalDlcProfile_H
#define CHARACTER_cCharacterGlobalDlcProfile_H

#include "rws/attributes.h"

namespace CHARACTER
{
    class cCharacterGlobalDlcProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

#ifndef RPG_cRPGGlobalsInterface_H
#define RPG_cRPGGlobalsInterface_H

#include "rws/attributes.h"

namespace RPG
{
    class cRPGGlobalsInterface : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

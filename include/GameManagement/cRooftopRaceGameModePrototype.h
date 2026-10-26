#ifndef GameManagement_cRooftopRaceGameModePrototype_H
#define GameManagement_cRooftopRaceGameModePrototype_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cRooftopRaceGameModePrototype : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

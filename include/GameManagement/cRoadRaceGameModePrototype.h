#ifndef GameManagement_cRoadRaceGameModePrototype_H
#define GameManagement_cRoadRaceGameModePrototype_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cRoadRaceGameModePrototype : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

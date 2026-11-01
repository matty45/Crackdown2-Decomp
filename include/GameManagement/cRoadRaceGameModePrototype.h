#ifndef GameManagement_cRoadRaceGameModePrototype_H
#define GameManagement_cRoadRaceGameModePrototype_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cRoadRaceGameModePrototype : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

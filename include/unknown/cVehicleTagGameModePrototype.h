#ifndef unknown_cVehicleTagGameModePrototype_H
#define unknown_cVehicleTagGameModePrototype_H

#include "rws/attributes.h"

namespace unknown
{
    class cVehicleTagGameModePrototype : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

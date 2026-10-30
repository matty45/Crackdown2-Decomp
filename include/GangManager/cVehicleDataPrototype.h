#ifndef GangManager_cVehicleDataPrototype_H
#define GangManager_cVehicleDataPrototype_H

#include "rws/attributes.h"

namespace GangManager
{
    class cVehicleDataPrototype : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

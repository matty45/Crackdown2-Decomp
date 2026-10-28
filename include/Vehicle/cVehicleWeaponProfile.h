#ifndef Vehicle_cVehicleWeaponProfile_H
#define Vehicle_cVehicleWeaponProfile_H

#include "rws/attributes.h"
#include "cd2/layout.h"

namespace Vehicle
{
    class cVehicleWeaponProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif

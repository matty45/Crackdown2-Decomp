#ifndef Vehicle_cVehicleWeaponProfile_H
#define Vehicle_cVehicleWeaponProfile_H

#include "rws/attributes.h"

namespace Vehicle
{
    class cVehicleWeaponProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif

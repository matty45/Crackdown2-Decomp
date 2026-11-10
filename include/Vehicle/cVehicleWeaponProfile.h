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
        // CD2: cVehicleWeaponProfile's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x826E1190
    };
}

#endif

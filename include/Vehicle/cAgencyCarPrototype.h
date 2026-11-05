// Vehicle::cAgencyCarPrototype (Crackdown 2): namespace-level prototype, name, base, overrides and size (0x4C0) from
// RuffKing, which has m_ExhaustFlameData (tAgencyExhaustFlameData) at 0x4B0. CD2's cAgencyCar::MakeNew (0x826EC108)
// allocates 0x4C0 bytes, calls cCarPrototype's constructor (0x826B7BE0) and then stores this class's tables, so the
// constructor is inline and initializes no field. The destructor is compiler-generated, as in RuffKing.
#ifndef VEHICLE_CAGENCYCARPROTOTYPE_H
#define VEHICLE_CAGENCYCARPROTOTYPE_H

#include "cd2/layout.h"
#include "fun_runtime/retval.h"
#include "Vehicle/cCar.h"

namespace Vehicle
{
    class cAgencyCarPrototype : public cCar::cCarPrototype
    {
    public:
        cAgencyCarPrototype(const RWS::CAttributePacket &packet) : cCarPrototype(packet) {}
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

    private:
        unsigned char m_unmodelledExhaustFlameData[0x4C0 - 0x4B0];   // RuffKing's m_ExhaustFlameData

        CD2_LAYOUT_CHECKS(cAgencyCarPrototype,
            CD2_SIZE(cAgencyCarPrototype, 0x4C0))
    };
}

#endif

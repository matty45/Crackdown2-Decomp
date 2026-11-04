#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Vehicle/cWheelGroup.h"
// Vehicle::cCar (Crackdown 2): STAND-IN with only what its matched functions need; its bases are not modelled yet.
// Its class-factory registrar (0x82FE7AE0) registers "cCar" with MakeNew (0x826B5D18) and size 0x3070.
#ifndef VEHICLE_CCAR_H
#define VEHICLE_CCAR_H

namespace Vehicle
{
    class cCar
    {
    public:
        // Interface-only prototype hierarchy from RuffKing; storage is unrecovered.
        class cCarPrototype : public cWheelGroup::cWheelGroupPrototype {};
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // VEHICLE_CCAR_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
// Vehicle::cAgencyCar (Crackdown 2): STAND-IN with only what its matched functions need; its bases are not modelled yet.
// Its class-factory registrar (0x82FEB4F8) registers "cAgencyCar" with MakeNew (0x826EC108) and size 0x30B0.
#ifndef VEHICLE_CAGENCYCAR_H
#define VEHICLE_CAGENCYCAR_H

namespace Vehicle
{
    class cAgencyCar
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // VEHICLE_CAGENCYCAR_H

// Method-only STAND-IN, not an allocation layout. Reference cPickup.h gives
// cPickup and cReplicatedClass as the bases. CD2 constructor 0x8270ACC8 calls
// cPickup first and constructs replication at +0x150. Descriptor 0x8270A670
// registers cDynamicPickup with size 0x3B0; its own fields remain unmodelled.
#pragma once
#include "PHYSICS/cPickup.h"
#include "network/cReplicatedClass.h"
namespace PHYSICS
{
    class cDynamicPickup : public cPickup, public cReplicatedClass
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2 initializer 0x82FF0728 stores this pointer at 0x83849534.
        static const Fun_Runtime::cClass *ms_pcDynamicPickupClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
    };
}

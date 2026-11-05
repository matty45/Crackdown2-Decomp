#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Vehicle::cAgencySUV (Crackdown 2): base cAgencyCar (RuffKing; CD2 inheritance registrar 0x82FEC170). Fields not modelled.
// StaticCreateClass (0x826FBC38) builds cClass(0x12060, "cAgencySUV", 0x30C0); 0x30C0 is the size its registrar gives.
#ifndef VEHICLE_CAGENCYSUV_H
#define VEHICLE_CAGENCYSUV_H

#include "fun_runtime/class.h"
#include "cd2/layout.h"
#include "Vehicle/cAgencyCar.h"

namespace Vehicle
{
    class cAgencySUV : public cAgencyCar
    {
    public:
        // CD2 0x826FBA68: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FEC228 names placement factory 0x826fba78.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 placement factory forwards only this.
        cAgencySUV();                                     // CD2 0x826FBCD8
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcAgencySUVClass;
        static Fun_Runtime::cClass &StaticCreateClass();

    private:
        unsigned char m_unmodelled30B0[0x30C0 - 0x30B0];

        CD2_LAYOUT_CHECKS(cAgencySUV,
            CD2_SIZE(cAgencySUV, 0x30C0))
    };
}

#endif // VEHICLE_CAGENCYSUV_H

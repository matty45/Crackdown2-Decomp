#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Vehicle::cAgencyTank (Crackdown 2): base cAgencyCar (RuffKing; CD2 inheritance registrar 0x82FEC5A8). Fields not modelled.
// StaticCreateClass (0x826FC730) builds cClass(0x120AB, "cAgencyTank", 0x3150); 0x3150 is the size its registrar gives.
#ifndef VEHICLE_CAGENCYTANK_H
#define VEHICLE_CAGENCYTANK_H

#include "fun_runtime/class.h"
#include "cd2/layout.h"
#include "Vehicle/cAgencyCar.h"

namespace Vehicle
{
    class cAgencyTank : public cAgencyCar
    {
    public:
        // CD2 0x826FC708: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FEC660 names placement factory 0x826fc718.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 placement factory forwards only this.
        cAgencyTank();                                     // CD2 0x826FCD08
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcAgencyTankClass;
        static Fun_Runtime::cClass &StaticCreateClass();

    private:
        unsigned char m_unmodelled30B0[0x3150 - 0x30B0];

        CD2_LAYOUT_CHECKS(cAgencyTank,
            CD2_SIZE(cAgencyTank, 0x3150))
    };
}

#endif // VEHICLE_CAGENCYTANK_H

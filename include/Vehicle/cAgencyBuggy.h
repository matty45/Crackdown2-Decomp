#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Vehicle::cAgencyBuggy (Crackdown 2): base cAgencyCar (RuffKing; CD2 inheritance registrar 0x82FEB0E0). Fields not modelled.
// StaticCreateClass (0x826E9EB8) builds cClass(0x12064, "cAgencyBuggy", 0x30C0); 0x30C0 is the size its registrar gives.
#ifndef VEHICLE_CAGENCYBUGGY_H
#define VEHICLE_CAGENCYBUGGY_H

#include "fun_runtime/class.h"
#include "cd2/layout.h"
#include "Vehicle/cAgencyCar.h"

namespace Vehicle
{
    class cAgencyBuggy : public cAgencyCar
    {
    public:
        // CD2 0x826E9960: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FEB198 names placement factory 0x826e9970.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 placement factory forwards only this.
        cAgencyBuggy();                                     // CD2 0x826E9F58
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcAgencyBuggyClass;
        static Fun_Runtime::cClass &StaticCreateClass();

    private:
        unsigned char m_unmodelled30B0[0x30C0 - 0x30B0];

        CD2_LAYOUT_CHECKS(cAgencyBuggy,
            CD2_SIZE(cAgencyBuggy, 0x30C0))
    };
}

#endif // VEHICLE_CAGENCYBUGGY_H

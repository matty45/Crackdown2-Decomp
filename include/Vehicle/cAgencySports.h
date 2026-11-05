#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Vehicle::cAgencySports (Crackdown 2): base cAgencyCar (RuffKing; CD2 inheritance registrar 0x82FEB8C8). Fields not modelled.
// StaticCreateClass (0x826ED348) builds cClass(0x12061, "cAgencySports", 0x30C0); 0x30C0 is the size its registrar gives.
#ifndef VEHICLE_CAGENCYSPORTS_H
#define VEHICLE_CAGENCYSPORTS_H

#include "fun_runtime/class.h"
#include "cd2/layout.h"
#include "Vehicle/cAgencyCar.h"

namespace Vehicle
{
    class cAgencySports : public cAgencyCar
    {
    public:
        // CD2 0x826ECEC8: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x826ECF90: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FEB980 names placement factory 0x826ecfa0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 placement factory forwards only this.
        cAgencySports();                                     // CD2 0x826ED3E8
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcAgencySportsClass;
        static Fun_Runtime::cClass &StaticCreateClass();

    private:
        unsigned char m_unmodelled30B0[0x30C0 - 0x30B0];

        CD2_LAYOUT_CHECKS(cAgencySports,
            CD2_SIZE(cAgencySports, 0x30C0))
    };
}

#endif // VEHICLE_CAGENCYSPORTS_H

// Vehicle::cAgencyCar (Crackdown 2): base cCar (RuffKing), size 0x30B0: its class-factory registrar (0x82FEB4F8)
// registers "cAgencyCar" with MakeNew (0x826EC108) and that size. Fields not modelled.
#ifndef VEHICLE_CAGENCYCAR_H
#define VEHICLE_CAGENCYCAR_H

#include "rws/attributes.h"
#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "gom/object_prototype.h"
#include "Vehicle/cCar.h"

namespace Vehicle
{
    class cAgencyCar : public cCar
    {
    public:
        // CD2 0x826EC3C0; the placement factory (0x826EC188) forwards only this.
        cAgencyCar();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 0x826EC320 creates the named runtime descriptor; 0x82FEB468 initializes ms_pcAgencyCarClass from it.
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcAgencyCarClass;
        // Registered-class table 0x82136C3C: slot 0 (0x826EC098) and slot 1 (0x826EC0A8).
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);

        // CD2: cAgencyCar's own virtuals. Each slot below holds, in this class's CD2 vtable 0x8201C090 (and its derived
        // classes'), an address its base's table does not hold there, so the class overrides it; names and signatures
        // are the bases'. Its destructor slot holds cCar's: the class declares no destructor.
        virtual void vf140();                                   // 140: 0x826EC4F0
        virtual void vf296();                                   // 296: 0x826EC588
        virtual void UpdateExhaustVFX(float);                   // 469: 0x826EC648

    private:
        unsigned char m_unmodelled3070[0x30B0 - 0x3070];

        CD2_LAYOUT_CHECKS(cAgencyCar,
            CD2_SIZE(cAgencyCar, 0x30B0))
    };
}

#endif // VEHICLE_CAGENCYCAR_H

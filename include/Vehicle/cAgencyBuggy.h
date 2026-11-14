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

        // Registered-class table 0x82136B54: slot 0 (0x826E9860) and slot 1 (0x826E9870).
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;

        // CD2: cAgencyBuggy's own virtuals. Each slot below holds, in this class's CD2 vtable 0x8201B110, an address its
        // base's table does not hold there, so the class overrides it; names and signatures are the bases'. The
        // destructor slot holds cCar's folded copy: the class declares no destructor.
        virtual Fun_Runtime::RetVal Init(const GOM::cSpawner *);    // 18: 0x826EA150
        virtual void Slot23();                                  // 23: 0x826EA020
        virtual void Slot24();                                  // 24: 0x826EA098
        virtual Fun_Runtime::RetVal Slot37();                                  // 37: 0x826EA200
        virtual Fun_Runtime::RetVal Reinitialise(const GOM::cSpawner *);    // 38: 0x826EA1A8
        virtual Fun_Runtime::RetVal TermForReuse();             // 39: 0x826EA258
        virtual void vf488();                                   // 488: 0x826EA2B8
        // RuffKing's name; CD2 0x826EBF38 (ReplicateInitialFields calls it).
        void UpdateBuggyWeapon();
        virtual void ReplicateInitialFields();                  // cReplicatedClass 8: 0x826EA058
        virtual void ReplicateFields();                         // cReplicatedClass 9: 0x826EA090

    private:
        // RuffKing's members (0x2FB0 and 0x2FB1 there).
        bool m_bWeaponsInitialised;                             // 0x30B0
        bool m_bMarkerAdded;                                    // 0x30B1

        CD2_LAYOUT_CHECKS(cAgencyBuggy,
            CD2_SIZE(cAgencyBuggy, 0x30C0)
            CD2_OFFSET(cAgencyBuggy, m_bWeaponsInitialised, 0x30B0)
            CD2_OFFSET(cAgencyBuggy, m_bMarkerAdded, 0x30B1))
    };
}

#endif // VEHICLE_CAGENCYBUGGY_H

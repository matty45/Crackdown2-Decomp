#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Vehicle::cAgencyTank (Crackdown 2): base cAgencyCar (RuffKing; CD2 inheritance registrar 0x82FEC5A8). Fields not modelled.
// StaticCreateClass (0x826FC730) builds cClass(0x120AB, "cAgencyTank", 0x3150); 0x3150 is the size its registrar gives.
#ifndef VEHICLE_CAGENCYTANK_H
#define VEHICLE_CAGENCYTANK_H

#include "fun_runtime/class.h"
#include "cd2/layout.h"
#include "Vehicle/cAgencyCar.h"
#include "Vehicle/cFixedVehicleTurret.h"

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

        // Registered-class table 0x82139234: slot 0 (0x826FC640) and slot 1 (0x826FC650).
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;

        // CD2: cAgencyTank's own virtuals. Each slot below holds, in this class's CD2 vtable 0x82138A70, an address its
        // base's table does not hold there, so the class overrides it; names and signatures are the bases'. The
        // destructor slot holds cCar's folded copy: the class declares no destructor.
        virtual void Slot14();                                  // 14: 0x826FD360
        virtual Fun_Runtime::RetVal Init(const GOM::cSpawner *);    // 18: 0x82700130
        virtual void Slot23();                                  // 23: 0x826FCEA8
        virtual void Slot24();                                  // 24: 0x826FCF10
        virtual Fun_Runtime::RetVal Slot37();                                  // 37: 0x827001E0
        virtual Fun_Runtime::RetVal Reinitialise(const GOM::cSpawner *);    // 38: 0x82700188
        virtual Fun_Runtime::RetVal TermForReuse();             // 39: 0x826FCE28
        virtual void vf380();                                   // 380: 0x826FD3A8
        virtual void vf392();                                   // 392: 0x826FD3F0
        // Slots 495 and 496 are the tank's own virtuals (RuffKing declares two: CheckForRocketGuns and
        // UpdateTurretTransforms); their bodies are not identified yet.
        virtual void vf495();                                   // 495: 0x826FD3F8
        virtual void vf496();                                   // 496: 0x826FF890
        virtual void ReplicateInitialFields();                  // cReplicatedClass 8: 0x826FF820
        virtual void ReplicateFields();                         // cReplicatedClass 9: 0x826FF858
        virtual unsigned int GetMaxReplicatedFields() const;    // cReplicatedClass 23: 0x82889198

    private:
        // RuffKing's members (0x2FB0 and 0x3030 there).
        cFixedVehicleTurret m_Turret;                           // 0x30B0
        bool m_bMarkerAdded;                                    // 0x3140

        CD2_LAYOUT_CHECKS(cAgencyTank,
            CD2_SIZE(cAgencyTank, 0x3150)
            CD2_OFFSET(cAgencyTank, m_Turret, 0x30B0)
            CD2_OFFSET(cAgencyTank, m_bMarkerAdded, 0x3140))
    };
}

#endif // VEHICLE_CAGENCYTANK_H

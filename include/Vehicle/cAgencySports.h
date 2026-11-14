#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Vehicle::cAgencySports (Crackdown 2): base cAgencyCar (RuffKing; CD2 inheritance registrar 0x82FEB8C8). Fields not modelled.
// StaticCreateClass (0x826ED348) builds cClass(0x12061, "cAgencySports", 0x30C0); 0x30C0 is the size its registrar gives.
#ifndef VEHICLE_CAGENCYSPORTS_H
#define VEHICLE_CAGENCYSPORTS_H

#include "fun_runtime/class.h"
#include "cd2/layout.h"
#include "Vehicle/cAgencyCar.h"
#include "Vehicle/cVehicleWedge.h"

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

        virtual bool IsA(const Fun_Runtime::cClass &) const;    // CD2 0x826ECED8

        // CD2: cAgencySports's own virtuals. Each slot below holds, in this class's CD2 vtable 0x82136D00, an address its
        // base's table does not hold there, so the class overrides it; names and signatures are the bases'. RuffKing's
        // class overrides TickUpdate, PostTickUpdate, ActionUpdate and TermForReuse; Burn's UpdateWedge.
        virtual void Slot23();                                  // 23: 0x826ED5D0
        virtual void Slot24();                                  // 24: 0x826ED978
        virtual void LeavePhysicalState();                                  // 27: 0x826ED540 (RuffKing: LeavePhysicalState)
        virtual Fun_Runtime::RetVal TermForReuse();             // 39: 0x826ED578
        virtual void ActionUpdate(float);                       // 448: 0x826ED980 (RuffKing: updates the wedge)

    private:
        // RuffKing's members (0x2FB0 and 0x2FB8 there).
        cVehicleWedge m_Wedge;                                  // 0x30B0
        float m_fCurretCombatCooldownTimer;                     // 0x30B8

        CD2_LAYOUT_CHECKS(cAgencySports,
            CD2_SIZE(cAgencySports, 0x30C0)
            CD2_OFFSET(cAgencySports, m_Wedge, 0x30B0)
            CD2_OFFSET(cAgencySports, m_fCurretCombatCooldownTimer, 0x30B8))
    };
}

#endif // VEHICLE_CAGENCYSPORTS_H

// Activity::cSquadMemberSpawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x823DC6B0, MakeNew 0x823DC750, from its registrars in CD2's
// initializer run); RuffKing names the class in cSquadMemberSpawnPoint.obj. No layout or virtuals are modelled yet;
// base Activity::cSquadMemberSpawnPointBase from CD2's inheritance registrar.
#ifndef ACTIVITY_CSQUADMEMBERSPAWNPOINT_H
#define ACTIVITY_CSQUADMEMBERSPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSquadMemberSpawnPointBase.h"
#include "editor/guid_event_handler.h"

namespace Activity
{
    class cSquadMemberSpawnPoint : public cSquadMemberSpawnPointBase
    {
    public:
        // CD2 0x823DC640 / 0x823DC650: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcSquadMemberSpawnPointClass;
        // CD2 0x823579A8 (outside the scaffolded files); MakeNew applies the packet afterwards.
        cSquadMemberSpawnPoint();
        virtual cNonGameBase *Spawn();

    protected:
        virtual void HandleAttributes(const RWS::CAttributePacket &attr);
        bool m_bRespawnPointBindOverride;
    private:
        const cSquadMemberSpawnPoint *m_pRegisteredVehicleSpawnPoint;
        float m_fMaxPatrolVehicleSpeed;
        float m_fInitialVehicleSpawnSpeed;
        float m_fSpawnHealthScalar;
        bool m_bForceInVehicle;
        bool m_bDoVehicleOrientation;
        Editor::cGUIDEventHandler<cSquadMemberSpawnPoint> m_EventHandler;

        CD2_LAYOUT_CHECKS(cSquadMemberSpawnPoint,
            CD2_SIZE(cSquadMemberSpawnPoint, 0xA0)
            CD2_OFFSET(cSquadMemberSpawnPoint, m_bRespawnPointBindOverride, 0x70)
            CD2_OFFSET(cSquadMemberSpawnPoint, m_fSpawnHealthScalar, 0x80)
            CD2_OFFSET(cSquadMemberSpawnPoint, m_EventHandler, 0x88))
    };
}

#endif // ACTIVITY_CSQUADMEMBERSPAWNPOINT_H

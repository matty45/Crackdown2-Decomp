// Activity::cTurretSquadMemberSpawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x823DF088, MakeNew 0x823DF128, from its registrars in CD2's
// initializer run); RuffKing names the class in cTurretSquadMemberSpawnPoint.obj. No layout or virtuals are modelled yet;
// base Activity::cSquadMemberSpawnPoint from CD2's inheritance registrar.
#ifndef ACTIVITY_CTURRETSQUADMEMBERSPAWNPOINT_H
#define ACTIVITY_CTURRETSQUADMEMBERSPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSquadMemberSpawnPoint.h"
#include "fun_runtime/pointer_list.h"

namespace Activity
{
    class cTurretSpawnPoint;

    // Fields: RuffKing's, 0x40 below its offsets, as for its base (cSquadMemberSpawnPointBase.h); CD2's registrar gives
    // 0xC0 bytes, RuffKing's less 0x40.
    class cTurretSquadMemberSpawnPoint : public cSquadMemberSpawnPoint
    {
    public:
        // CD2 0x823DF018 / 0x823DF028: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcTurretSquadMemberSpawnPointClass;
        // CD2 0x823DF188; MakeNew applies the packet afterwards.
        cTurretSquadMemberSpawnPoint();
        virtual cNonGameBase *Spawn();

    protected:
        virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    private:
        Editor::cGUIDEventHandler<cTurretSquadMemberSpawnPoint> m_EventHandler;
        Fun_Runtime::cPointerList<cTurretSpawnPoint *> m_lAvailableTurrets;

        CD2_LAYOUT_CHECKS(cTurretSquadMemberSpawnPoint,
            CD2_SIZE(cTurretSquadMemberSpawnPoint, 0xC0)
            CD2_OFFSET(cTurretSquadMemberSpawnPoint, m_EventHandler, 0xA0)
            CD2_OFFSET(cTurretSquadMemberSpawnPoint, m_lAvailableTurrets, 0xB4))
    };
}

#endif // ACTIVITY_CTURRETSQUADMEMBERSPAWNPOINT_H

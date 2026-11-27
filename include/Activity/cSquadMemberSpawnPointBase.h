// Activity::cSquadMemberSpawnPointBase (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x823DD270, from its registrars in CD2's
// initializer run); RuffKing names the class in cSquadMemberSpawnPointBase.obj. No layout or virtuals are modelled yet;
// base Activity::cSpawnPointBase from CD2's inheritance registrar.
// Fields: RuffKing's names and order, 0x40 below RuffKing's offsets (CD2's cSpawnPointBase is 0x50, RuffKing's 0x90); the
// sizes CD2's registrars give (cSquadMemberSpawnPoint 0xA0, cSquadMemberRespawnPoint 0x90, cTurretSquadMemberSpawnPoint
// 0xC0) are RuffKing's less 0x40 too. cSquadMemberSpawnPoint's constructor (0x823579A8) stores 0x50..0x61, 0x70..0x85
// and the GUID handler at 0x88.
#ifndef ACTIVITY_CSQUADMEMBERSPAWNPOINTBASE_H
#define ACTIVITY_CSQUADMEMBERSPAWNPOINTBASE_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSpawnPointBase.h"

namespace AI { class cPatrolRoute; }

namespace Activity
{
    class cSquadSpawnPoint;

    class cSquadMemberSpawnPointBase : public cSpawnPointBase
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcSquadMemberSpawnPointBaseClass;

    protected:
        virtual void HandleAttributes(const RWS::CAttributePacket &attr);
        cSquadSpawnPoint *m_pSquadSpawn;
        cSquadMemberSpawnPointBase *m_pRespawnPoint;
    private:
        cSquadMemberSpawnPointBase *m_pParentPoint;
        const AI::cPatrolRoute *m_pPatrolRoute;
        unsigned char m_nGameImportance;
    protected:
        unsigned char m_nSquadIndex;

        CD2_LAYOUT_CHECKS(cSquadMemberSpawnPointBase,
            CD2_SIZE(cSquadMemberSpawnPointBase, 0x70)
            CD2_OFFSET(cSquadMemberSpawnPointBase, m_pSquadSpawn, 0x50)
            CD2_OFFSET(cSquadMemberSpawnPointBase, m_nSquadIndex, 0x61))
    };
}

#endif // ACTIVITY_CSQUADMEMBERSPAWNPOINTBASE_H

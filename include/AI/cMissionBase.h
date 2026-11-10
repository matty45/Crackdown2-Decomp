// STAND-IN: standalone mission-framework interfaces and order from RuffKing cMissionBase.h.
// CD2 constructor 0x8245A748 uses replication at +0x10, net role at +0x240,
// attributes at +0x248 and save/load at +0x260. This is not a cNonGameBase-derived GOM entity.
// Instance fields after these interfaces are unrecovered; sizeof is not an allocation layout.
#ifndef AI_CMISSIONBASE_H
#define AI_CMISSIONBASE_H
#include "fun_runtime/class.h"
#include "Network/cReplicatedClass.h"
#include "Network/netrole.h"
#include "rws/systemcommands.h"
#include "rws/attributes.h"
#include "rws/dynamicallocationpolicy.h"
#include "SaveGame/cLoadSaveObject.h"
namespace Activity { class cSquadSpawnPoint; }
namespace Damage { class cDamage; }
namespace AI
{
    class cMissionCriticalPropSpawnPoint;

    class cMissionBase : public Fun_Runtime::cRegisteredClass, public cReplicatedClass,
        public Network::cNetRoleObject, public RWS::CSystemCommands, public RWS::CAttributeHandler,
        public RWS::DynamicAllocationPolicy, public SaveGame::cLoadSaveObject
    {
    public:
        // CD2 0x8245A6A8 names the runtime class; constructor ABI takes only this.
        static Fun_Runtime::cClass &StaticCreateClass();
        cMissionBase();
        virtual ~cMissionBase();
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual bool IsSequential() const;
        virtual void SetPingedFieldStatesForNode(unsigned char);
        // Primary slots 2..16 (after cRegisteredClass's RetClass/IsA), in RuffKing's order. CD2's mission tables
        // (cTacticalObjective 0x820073D8, cCellStrongholdMission 0x82007478) agree up to slot 16; CD2 has none of
        // RuffKing's three debug-page virtuals (DebugPageEnter, RenderDebugPage, RetMenuText) after them.
        virtual void Activate();
        virtual void Deactivate();
        virtual void ResetMission() = 0;
        virtual void NotifySquadDead(Activity::cSquadSpawnPoint *);
        virtual void NotifySquadDelete(Activity::cSquadSpawnPoint *);
        virtual void NotifySquadSpawn(Activity::cSquadSpawnPoint *);
        virtual void TickUpdate(float) = 0;
        virtual unsigned short RetMissionID() const;
        virtual void OnMissionCriticalPropTakeDamage(cMissionCriticalPropSpawnPoint *, Damage::cDamage &);
        virtual void OnMissionCriticalPropDestroyed(cMissionCriticalPropSpawnPoint *);
        virtual void OnMissionCriticalPropUsed(cMissionCriticalPropSpawnPoint *, unsigned char);
        virtual void OnMissionCriticalPropDetached(cMissionCriticalPropSpawnPoint *);
        virtual void OnMissionCriticalPropApproachedByLocalPlayer(cMissionCriticalPropSpawnPoint *);
        virtual void OnClientMissionStateNotification(unsigned char, unsigned char);
        virtual void OnSquadGroupBlockedMessage(bool, unsigned char);
        CD2_LAYOUT_CHECKS(cMissionBase,
            CD2_OFFSET(cMissionBase, m_eNetRole, 0x244)
            CD2_OFFSET(cMissionBase, m_Flags, 0x24C))
    };
}
#endif

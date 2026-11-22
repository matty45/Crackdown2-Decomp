// AI::cMissionCriticalPropSpawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x8245B740, MakeNew 0x8245B7D8, from its registrars in CD2's
// initializer run); RuffKing names the class in cMissionCriticalPropSpawnPoint.obj.
// Base Activity::cSpawnPoint comes from CD2's inheritance registrar; the additional
// replication bases and instance fields remain unrecovered here.
// Reconstruction update: CD2 constructor 0x8245B838 confirms the bases and
// fields below; the registrar allocates 0x2D0 bytes.
#ifndef AI_CMISSIONCRITICALPROPSPAWNPOINT_H
#define AI_CMISSIONCRITICALPROPSPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSpawnPoint.h"
#include "network/cReplicatedClass.h"
#include "network/netrole.h"
#include "editor/guid_event_handler.h"

namespace AI
{
    class cMission;
    class cMissionCriticalPropSpawnPoint : public Activity::cSpawnPoint,
        public cReplicatedClass, public Network::cNetRoleObject
    {
    public:
        // CD2 0x8245B6D0 / 0x8245B6E0: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcMissionCriticalPropSpawnPointClass;
        // CD2 0x8245B838; the factory applies attributes after construction.
        cMissionCriticalPropSpawnPoint();
        // cSpawnPointBase supplies primary slots 0..10. CD2's Docks mission
        // calls these two new slots through its collection-object pointer
        // (0x824746F0 / 0x82474740); names/signatures agree with RuffKing.
        virtual void InitReplication(); // primary slot 11
        virtual void TermReplication(); // primary slot 12
        virtual ~cMissionCriticalPropSpawnPoint();
        virtual cNonGameBase *Spawn();
        virtual bool IsOwnedLocally();
        virtual bool IsSequential() const;
        virtual void ReplicateInitialFields();
        virtual void ReplicateFields();
        virtual unsigned int GetNumObjectIDBits() const;
        virtual void SetPingedFieldStatesForNode(unsigned char);
        virtual SNetworkHeader::etNetworkDataType GetReplicatedObjectType() const;
        virtual unsigned int GetMaxReplicatedFields() const;
        cMission *RetMission() const { return m_pMission; }
    protected:
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        cMission *m_pMission;
        Editor::cGUIDEventHandler<cMissionCriticalPropSpawnPoint> m_EventHandler;
        unsigned char m_nPropState;

        CD2_LAYOUT_CHECKS(cMissionCriticalPropSpawnPoint,
            CD2_SIZE(cMissionCriticalPropSpawnPoint, 0x2D0)
            CD2_OFFSET(cMissionCriticalPropSpawnPoint, m_pMission, 0x2A8)
            CD2_OFFSET(cMissionCriticalPropSpawnPoint, m_EventHandler, 0x2AC)
            CD2_OFFSET(cMissionCriticalPropSpawnPoint, m_nPropState, 0x2C0))
    };
}

#endif // AI_CMISSIONCRITICALPROPSPAWNPOINT_H

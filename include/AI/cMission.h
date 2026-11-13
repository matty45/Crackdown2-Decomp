// STAND-IN: RuffKing cMission derives from cMissionBase. CD2 constructor 0x824592E8
// calls 0x8245A748 first; descriptor 0x82459250 names cMission (complete size 0x3C0).
// Fields beyond the known interfaces are not modelled; this is not an allocation layout.
#ifndef AI_CMISSION_H
#define AI_CMISSION_H
#include "AI/cMissionBase.h"
namespace AI
{
    class cMission : public cMissionBase
    {
    public:
        enum etGlobalMissionState
        {
            eGMS_Uncompletable = 0,
            eGMS_Incomplete = 1,
            eGMS_Complete = 2,
            eGMS_NumStates = 3,
            eGMS_Invalid = 3
        };
        static Fun_Runtime::cClass &StaticCreateClass();
        cMission();
        virtual ~cMission();
        // Overrides named by the reference mission interface.
        virtual bool IsOwnedLocally();
        virtual SNetworkHeader::etNetworkDataType GetReplicatedObjectType() const;
        virtual unsigned int GetMaxReplicatedFields() const;
        virtual void TickUpdate(float);
        virtual void ResetMission();
        // Primary slots 17..38 in RuffKing's order, without its debug-only CompleteMission: CD2's mission tables
        // have RetClassName at 17 and Destruct at 18 (RuffKing 20/21), and cTacticalObjective's overrides fall on
        // IsComplete 20, IsLocalPlayerNearby 24, the delivery notifications 25..27, the mission-state handlers
        // 29..33 and GetSaveStateForMissionState/InitReplication/TermReplication 36..38 (39 slots in all).
        virtual const char *RetClassName() const;
        virtual void Destruct();
        virtual void EnableCompletion();
        virtual bool IsComplete() const;
        virtual bool IsCompletable() const;
        virtual void OnChildMissionCompleted(cMission *);
        virtual bool ArePrerequisitesComplete() const;
        virtual bool IsLocalPlayerNearby() const;
        virtual void NotifyDeliveryStart(int);
        virtual void NotifyDeliveryDrop(bool);
        virtual void NotifyDeliveryFinish(bool);
    protected:
        virtual void TriggerCompletionVOA();
        virtual void OnLeaveMissionState(unsigned char);
        virtual void OnTransitionMissionState(unsigned char);
        virtual void OnEnterMissionState(unsigned char);
        virtual void OnLeaveGlobalMissionState(etGlobalMissionState);
        virtual void OnEnterGlobalMissionState(etGlobalMissionState);
        virtual void OnEnterComplete();
        virtual void OnMissionUnlocked();
        virtual void GetSaveStateForMissionState(unsigned char &, unsigned char &);
    public:
        virtual void InitReplication();
        virtual void TermReplication();
    protected:
        // Fields in RuffKing's names and order (cMission.h); complete size 0x3C0 as CD2's descriptor gives.
        etGlobalMissionState m_eGlobalMissionState;
        float m_fSquadSwitchTimer;
        unsigned int m_SecondaryObjectiveCompletionStatus;
        bool m_bLocallyBlocked;
        unsigned short m_nBlockedNodes;
        unsigned int m_lChildMissions[3];         // RuffKing: cList<cMission *>; not modelled
        cMission *m_pParentMission;
        unsigned int m_lMissionCriticalProps[3];  // RuffKing: cList<cMissionCriticalPropSpawnPoint *>; not modelled
        void *m_pCompletionZone;                   // RuffKing: cMissionCompletionZone *
        unsigned char m_eMissionState;
        int m_nMissionTier;
        unsigned int m_EventHandler[5];           // RuffKing: Editor::cGUIDEventHandler<cMission>; not modelled
        void *m_aAssociatedZoneGUIDs;              // RuffKing: RWS::RWSGUID *
        void *m_apAssociatedARZone;                // RuffKing: GangManager::tARZoneData **
        bool *m_abAssociatedZonesEnabled;
        unsigned int m_nNumAssociatedARZones;
        unsigned int m_nLocNameID;
        void *m_pSecondaryObjectivesInfo;          // RuffKing: cSecondaryObjectivesInfo *
        CD2_LAYOUT_CHECKS(cMission,
            CD2_OFFSET(cMission, m_eGlobalMissionState, 0x350)
            CD2_OFFSET(cMission, m_pParentMission, 0x36C)
            CD2_OFFSET(cMission, m_eMissionState, 0x380)
            CD2_OFFSET(cMission, m_EventHandler, 0x388)
            CD2_OFFSET(cMission, m_pSecondaryObjectivesInfo, 0x3B0)
            CD2_SIZE(cMission, 0x3C0))
    };
}
#endif

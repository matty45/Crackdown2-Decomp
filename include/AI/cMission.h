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
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // RuffKing names these overrides; CD2 primary slots 0/1 read 0x8381C38C.
        static const Fun_Runtime::cClass *ms_pcMissionClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        cMission();
        virtual ~cMission();
        // Overrides named by the reference mission interface.
        virtual bool IsOwnedLocally();
        virtual SNetworkHeader::etNetworkDataType GetReplicatedObjectType() const;
        virtual unsigned int GetMaxReplicatedFields() const;
        virtual void ReplicateInitialFields(); // cReplicatedClass 8: 0x8245A230
        virtual void ReplicateFields(); // cReplicatedClass 9: 0x8230E318
        virtual unsigned int GetNumObjectIDBits() const; // cReplicatedClass 16: 0x8288AD98
        virtual void TickUpdate(float);
        virtual void ResetMission();
        // RuffKing's name and signature; CD2 0x82459BE0, called by cTacticalObjective::NotifyDeliveryStart.
        void SetMissionState(unsigned char nMissionState, bool bAllowAutoSave);
        // RuffKing's name and signature; CD2 0x82459F08, which cCellStrongholdMission::TickUpdate (0x824750A0) calls
        // first, as RuffKing's does.
        void TickSquadSwitch(float dT);
        // RuffKing name/signature; CD2 0x82459A60 updates the global state and invokes its callbacks.
        void SetGlobalMissionState(etGlobalMissionState, bool bAutoSave);
        // RuffKing's name; CD2 0x8245A390 (outside the scaffolded files), called by cDocksMission's Activate/Deactivate.
        void SetAssociatedZonesEnabled(bool bEnabled);
        // CD2's cMission table (0x82102D28) holds its own Activate (0x82459568) and Deactivate (0x82459618) in slots 2
        // and 3; the missions' overrides call them.
        virtual void Activate();
        virtual void Deactivate();
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
        // cLoadSaveObject overrides: the table CD2's constructor installs at +0x260 (0x82104564) holds 0x82459CF0 and
        // 0x82459DC8; cPebbleDashMission, which overrides neither, has the same table.
        virtual void Load(SaveGame::cLoadStream *pStream);
        virtual void Save(SaveGame::cSaveStream *pStream);
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

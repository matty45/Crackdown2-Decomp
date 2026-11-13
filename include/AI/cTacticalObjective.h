// AI::cTacticalObjective (Crackdown 2): RuffKing cTacticalObjective.h gives the bases (CEventHandler, cMission) and
// the size 0x530, which CD2's registrar and StaticCreateClass (0x824759A8) confirm. CD2's constructor 0x82475A48
// stores CEventHandler's table at 0 and constructs cMission at +0x10 (0x824592E8). The primary table 0x821044A0 has
// CEventHandler's six slots, then HasBackupBeenCalled (6, 0x82475880, as in RuffKing). cMission's table at +0x10
// (0x820073D8) carries the mission overrides. Own fields (0x3D0..) are not modelled yet: cMission's are not.
#ifndef AI_CTACTICALOBJECTIVE_H
#define AI_CTACTICALOBJECTIVE_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "rws/eventhandler.h"
#include "AI/cMission.h"
#include "fun_runtime/vectorip.h"
#include "PLAYER/cPlayer.h"
#include "AI/cHeliCallZone.h"
#include "AI/cMissionActivationCylinder.h"

namespace GameManagement { class cCampaignPlayerSpawnGroup; }
namespace VEHICLE_CONTROL { class cVehicleCollectionZone; }
namespace Cam { class cCameraMarker; }

namespace AI
{
    class cHeliDropPoint;
    class cHeliCallZone;
    class cMissionActivationCylinder;

    class cTacticalObjective : public RWS::CEventHandler, public cMission
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcTacticalObjectiveClass;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void Destruct();
        // RuffKing's mission states; CD2's IsComplete (0x82475860) and HasBackupBeenCalled (0x82475880) compare
        // cMission's state byte with 5 and 2.
        enum eTOState
        {
            eTOS_Inactive = 0,
            eTOS_InTO,
            eTOS_Backup,
            eTOS_AwaitingDrop,
            eTOS_DropCameraCut,
            eTOS_Complete,
            eTOS_NumStates,
            eTOS_Invalid,
        };
        // CD2's MakeNew (0x824757F8) passes only this: the constructor (0x82475A48) takes no packet.
        cTacticalObjective();
        virtual ~cTacticalObjective();
        virtual void HandleEvents(RWS::CMsg &);
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual void TickUpdate(float);
        virtual void ResetMission();
        virtual bool IsComplete() const;
        virtual bool HasBackupBeenCalled() const;
        virtual bool IsLocalPlayerNearby() const;
        virtual void NotifyDeliveryStart(int nHeliID);
        virtual void NotifyDeliveryFinish(bool bSuccess);
        virtual void InitReplication();
        virtual void TermReplication();
    protected:
        virtual void OnLeaveGlobalMissionState(etGlobalMissionState nState);
        virtual void GetSaveStateForMissionState(unsigned char &nGlobalMissionState, unsigned char &nMissionState);
    public:

        bool IsPlayerInsideInner(const PLAYER::cPlayer &player) const;   // CD2 0x82477550
        // CD2 expands it into IsLocalPlayerNearby (0x82478A80); RuffKing has it out of line.
        bool IsLocalPlayerInsideInner() const
        {
            if (!PLAYER::cPlayer::g_pLocalPlayer)
                return false;
            return IsPlayerInsideInner(*PLAYER::cPlayer::g_pLocalPlayer);
        }

        enum eDrivingLevel
        {
            eDL_1 = 0,
            eDL_2,
            eDL_3,
            eDL_4,
            eDL_5,
            eNumLevels,
        };

    private:
        // RuffKing's fields, names and offsets; CD2's registrar gives the same size (0x530).
        unsigned int m_nMinRemainingCell;               // 0x3D0
        unsigned int m_nMinActiveCell;                  // 0x3D4
        unsigned int m_nMinActiveCellCutoff;            // 0x3D8
        float m_fLastPlayerNearbyTimer;                 // 0x3DC
        float m_fNetUpdateTimer;                        // 0x3E0
        float m_fCurrentTimer;                          // 0x3E4
        float m_fCurrResetTime;                         // 0x3E8
        float m_fResetTimer;                            // 0x3EC
        float m_fCallZoneCoolDown;                      // 0x3F0
        eDrivingLevel m_eCurrentLevel;                  // 0x3F4
        unsigned int m_SquadData[3];                    // 0x3F8 RuffKing: cMap<unsigned char, SquadNetData_t>; not modelled
        unsigned char m_nAuthSquadCount;                // 0x404
        float m_fPKPerc;                                // 0x408
        unsigned short m_nNumActiveCell;                // 0x40C
        unsigned short m_nNumRemainingCell;             // 0x40E
        unsigned short m_nInitialNumCell;               // 0x410
        float m_fLastCompletionRatio;                   // 0x414
        unsigned int m_nHeliID;                         // 0x418
        bool m_bCheckForSufficientAI;                   // 0x41C
        GameManagement::cCampaignPlayerSpawnGroup *m_pSpawnGroup;       // 0x420
        cHeliCallZone *m_pActivationZone;               // 0x424
        cMissionActivationCylinder *m_pContainmentZone; // 0x428
        VEHICLE_CONTROL::cVehicleCollectionZone *m_pCollectionZone;     // 0x42C
        Fun_Runtime::cVectorip<cHeliDropPoint *, 6> m_vHeliDropPoints;  // 0x430
        Fun_Runtime::cVectorip<cMission *, 20> m_vMissions;             // 0x460
        unsigned int m_lLevelBasedSquads[5][3];         // 0x4C0 RuffKing: cList<Activity::cSquadSpawnPoint *>[5]; not modelled
        unsigned int m_lCriticalGuySquads[3];           // 0x4FC RuffKing: cList<Activity::cSquadSpawnPoint *>; not modelled
        bool m_bBackupHasDropped;                       // 0x508
        bool m_bProgressMessage;                        // 0x509
        bool m_bDayHasPassed;                           // 0x50A
        float m_fPrevPhase;                             // 0x50C
        float m_fWarningDist;                           // 0x510
        Cam::cCameraMarker *m_pCameraMarker;            // 0x514
        Cam::cCameraMarker *m_pCameraLookAtMarker;      // 0x518
        float m_fCameraCutTriggerRadiusSq;              // 0x51C
        float m_fCameraCutHoldTime;                     // 0x520
        unsigned int m_nCameraCutEndTime;               // 0x524
        bool m_bInCameraCut;                            // 0x528
        unsigned int m_nNumDrops;                       // 0x52C

        CD2_LAYOUT_CHECKS(cTacticalObjective,
            CD2_SIZE(cTacticalObjective, 0x530)
            CD2_OFFSET(cTacticalObjective, m_nMinRemainingCell, 0x3D0)
            CD2_OFFSET(cTacticalObjective, m_SquadData, 0x3F8)
            CD2_OFFSET(cTacticalObjective, m_nHeliID, 0x418)
            CD2_OFFSET(cTacticalObjective, m_vHeliDropPoints, 0x430)
            CD2_OFFSET(cTacticalObjective, m_vMissions, 0x460)
            CD2_OFFSET(cTacticalObjective, m_lLevelBasedSquads, 0x4C0)
            CD2_OFFSET(cTacticalObjective, m_bBackupHasDropped, 0x508)
            CD2_OFFSET(cTacticalObjective, m_nNumDrops, 0x52C))
    };
}

#endif // AI_CTACTICALOBJECTIVE_H

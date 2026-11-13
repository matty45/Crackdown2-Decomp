#include "AI/cMission.h"
// Mission base restored from the registered parent and reference hierarchy; instance fields remain incomplete.
#ifndef AI_CAUMISSION_H
#define AI_CAUMISSION_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "fun_runtime/vec3.h"
namespace VFX { class cParticleEffectInstance; }

namespace AI
{
    class cBeaconMission;

    class cAUMission : public AI::cMission
    {
    public:
        // RuffKing's mission states; CD2's GetSaveStateForMissionState (0x8245F380) saves them in RuffKing's groups.
        enum eAUMissionState
        {
            eAUMS_UnpluggedOpen = 0,
            eAUMS_UnpluggedClosing = 1,
            eAUMS_UnpluggedClosed = 2,
            eAUMS_Pending_Unconfigured = 3,
            eAUMS_Unconfigured = 4,
            eAUMS_ConfiguringPaused = 5,
            eAUMS_Configuring0x = 6,
            eAUMS_Configuring1x = 7,
            eAUMS_Configuring2x = 8,
            eAUMS_Configuring3x = 9,
            eAUMS_Configuring4x = 10,
            eAUMS_Blocked = 11,
            eAUMS_Complete = 12,
            eAUMS_DebugStateOffset = 13,
            eAUMS_NumStates = 13,
        };
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcAUMissionClass;

        cAUMission();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2: cAUMission's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Activate(); // cRegisteredClass 2: 0x8245E200
        virtual void ResetMission(); // cRegisteredClass 4: 0x8245F428
        virtual void OnMissionCriticalPropTakeDamage(AI::cMissionCriticalPropSpawnPoint *,Damage::cDamage &); // cRegisteredClass 10: 0x8245E240
        virtual void OnMissionCriticalPropDestroyed(AI::cMissionCriticalPropSpawnPoint *); // cRegisteredClass 11: 0x8245E310
        virtual void OnMissionCriticalPropUsed(AI::cMissionCriticalPropSpawnPoint *,unsigned char); // cRegisteredClass 12: 0x8245E368
        virtual void OnMissionCriticalPropDetached(AI::cMissionCriticalPropSpawnPoint *); // cRegisteredClass 13: 0x8245E4B0
        virtual void OnMissionCriticalPropApproachedByLocalPlayer(AI::cMissionCriticalPropSpawnPoint *); // cRegisteredClass 14: 0x8245E530
        virtual void OnClientMissionStateNotification(unsigned char,unsigned char); // cRegisteredClass 15: 0x822ACAB0
        virtual void InitReplication(); // cRegisteredClass 37: 0x8245E000
        virtual void TermReplication(); // cRegisteredClass 38: 0x8245E100
    protected:
        virtual void TriggerCompletionVOA(); // cRegisteredClass 28: 0x8245DDE0
        virtual void OnTransitionMissionState(unsigned char); // cRegisteredClass 30: 0x8245E888
        virtual void OnEnterMissionState(unsigned char); // cRegisteredClass 31: 0x8245E9B8
        virtual void OnEnterGlobalMissionState(AI::cMission::etGlobalMissionState); // cRegisteredClass 33: 0x8245EBC0
        virtual void OnEnterComplete(); // cRegisteredClass 34: 0x822AC510
        virtual void GetSaveStateForMissionState(unsigned char &,unsigned char &); // cRegisteredClass 36: 0x8245F380
        // CD2: cAUMission's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void TickUpdate(float); // cRegisteredClass 8: 0x82271FD8
        virtual void Deactivate(); // cRegisteredClass 3: 0x8245E238

        // Own virtuals, RuffKing's three in its order: CD2 slots 39..41 (0x8245F460, 0x82312890, 0x8245F540); slot 41
        // returns m_bLocalPlayerOnPad as RuffKing's IsLocalPlayerOnAnyPad does.
        virtual bool IsLocalPlayerNearby(float fDist) const;
        virtual bool IsLocalPlayerNearBlocker() const;
        virtual bool IsLocalPlayerOnAnyPad() const;
    protected:
        // RuffKing's fields up to its beacon beam, at the same offsets in CD2 (ResetMission 0x8245F428 reads the blocker
        // spawn point and flag at 0x3F0/0x3F8). CD2's class is 0x5F0 bytes (registrar) where RuffKing's is 0x550: the
        // flags RuffKing has at 0x509/0x50A are at 0x559/0x55A in CD2 (IsLocalPlayerOnAnyPad, ResetMission).
        float m_fCloseTime;                                             // 0x3C0
        float m_fConfigureTime;                                         // 0x3C4
        float m_fCloseCountdown;                                        // 0x3C8
        float m_fConfigureCountdown;                                    // 0x3CC
        unsigned char m_nConfiguringPlayers;                            // 0x3D0
        cBeaconMission *m_pBeaconMission;                               // 0x3D4
        cMissionCriticalPropSpawnPoint *m_pPad1Spawn;                   // 0x3D8
        cMissionCriticalPropSpawnPoint *m_pPad2Spawn;                   // 0x3DC
        cMissionCriticalPropSpawnPoint *m_pPad3Spawn;                   // 0x3E0
        cMissionCriticalPropSpawnPoint *m_pPad4Spawn;                   // 0x3E4
        cMissionCriticalPropSpawnPoint *m_pPluggedUnitSpawn;            // 0x3E8
        cMissionCriticalPropSpawnPoint *m_pUnpluggedUnitSpawn;          // 0x3EC
        cMissionCriticalPropSpawnPoint *m_pBlockerSpawn;                // 0x3F0
        VFX::cParticleEffectInstance *m_pConfiguredVFX;                 // 0x3F4
        bool m_bBlockerDestroyed;                                       // 0x3F8
        unsigned int m_nConfiguredVFXID;                                // 0x3FC
        float m_fConfiguredVFXFadeTime;                                 // 0x400
        Fun_Runtime::Vec3 m_vConfiguredScale;                           // 0x410
        Fun_Runtime::Vec3 m_vConfiguredRotation;                        // 0x420
        Fun_Runtime::Vec3 m_vConfiguredOffset;                          // 0x430
        float m_fDrawCompletedVFXDistance;                              // 0x440
        unsigned char m_unmodelled444[0x559 - 0x444];
        bool m_bLocalPlayerOnPad;                                       // 0x559
        bool m_bBlockedIntroducedToLocalPlayer;                         // 0x55A
        unsigned char m_unmodelled55B[0x5F0 - 0x55B];
        CD2_LAYOUT_CHECKS(cAUMission,
            CD2_SIZE(cAUMission, 0x5F0)
            CD2_OFFSET(cAUMission, m_pBlockerSpawn, 0x3F0)
            CD2_OFFSET(cAUMission, m_bBlockerDestroyed, 0x3F8)
            CD2_OFFSET(cAUMission, m_fDrawCompletedVFXDistance, 0x440)
            CD2_OFFSET(cAUMission, m_bLocalPlayerOnPad, 0x559))
    };
}

#endif


// STAND-IN: RuffKing's cPlayerTriggerZone base and fields. CD2 start-zone getters
// establish primary slots 23..25 and constructor 0x821D2840 places replication at
// +0x120; the preceding trigger fields have the reference offsets below.
#ifndef GAMEMANAGEMENT_CGAMEMODETRIGGERZONE_H
#define GAMEMANAGEMENT_CGAMEMODETRIGGERZONE_H
#include "ZoneManager/cPlayerTriggerZone.h"
#include "fun_runtime/string.h"
#include "GameManagement/game_types.h"
namespace VFX { class cParticleEffectInstance; }
namespace GameManagement
{
    class cGameModePrototype;
    class cGameModeStartZone;
    class cGameModeTriggerZone : public ZoneManager::cPlayerTriggerZone
    {
    public:
        // CD2 0x82883AB8 takes only this, unlike the later reference constructor.
        cGameModeTriggerZone();
        virtual ~cGameModeTriggerZone();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual void OnPlayerEnter(CHARACTER::cCharacter *);
        virtual void OnPlayerLeave(CHARACTER::cCharacter *);
        virtual void SpawnVFX(etGameModeType, int);
        virtual void ReleaseVFX();
        virtual void TermVFX();
        virtual void TickCheckpointFading(float);
        virtual bool IsStartZone() const;
        virtual cGameModePrototype *RetGameModePrototype() const = 0;
        virtual unsigned char RetMinimumAgilityLevel() const;
        virtual unsigned char RetMinNumParticipants() const;
        etGameModeType RetGameType() const;
        const cGameModeStartZone *RetStartZone() const;
    protected:
        Fun_Runtime::cString m_sArenaName;
        VFX::cParticleEffectInstance *m_pCheckPointVFX;
        bool m_bRenderCheckpoint;
        float m_fFadeTimer;
        float m_fVFXHeightModifier;
        etGameModeType m_eGameType;
        int m_nCheckpointType;
        CD2_LAYOUT_CHECKS(cGameModeTriggerZone,
            CD2_SIZE(cGameModeTriggerZone, 0x120)
            CD2_OFFSET(cGameModeTriggerZone, m_sArenaName, 0xE0)
            CD2_OFFSET(cGameModeTriggerZone, m_pCheckPointVFX, 0xFC)
            CD2_OFFSET(cGameModeTriggerZone, m_bRenderCheckpoint, 0x100)
            CD2_OFFSET(cGameModeTriggerZone, m_fFadeTimer, 0x104)
            CD2_OFFSET(cGameModeTriggerZone, m_fVFXHeightModifier, 0x108)
            CD2_OFFSET(cGameModeTriggerZone, m_eGameType, 0x10C)
            CD2_OFFSET(cGameModeTriggerZone, m_nCheckpointType, 0x110))
    };
}
#endif

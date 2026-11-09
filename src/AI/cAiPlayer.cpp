// AI/cAiPlayer.cpp. Names and layouts: include/AI/cAiPlayer.h. Some functions in this file's range belong to other
// classes: the linker folded identical getters and kept the copies from this object (Sim::cTimeOfDay::RetPhase,
// AI::cAiTargetInfo::IsPrimaryFireBlocked / IsTargetVisible, AI::cAIEvent::RetSource, AI::cObjectInstigatorEvent::
// RetInstigator, AI::cDamageTakenEvent::RetInstigator; their headers give the evidence).
// Not named yet:
//   - SetFields4F8 (0x823E92B8) and m_n4F8/m_n4FC/m_n500 are unnamed (slot 125 of cAiPlayer vtable).
//   - RetConstantC8 (0x823E7B30) is slot 26 of the vtable 0x820FB114, whose object 0x82377190 builds; its class is not
//     known.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/script_type_registrar.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cCharacterEntityIF.h"
#include "AI/cAiPlayer.h"
#include "AI/cMapStatusScriptRegistration.h"
#include "AI/cEnemyStatusScriptRegistration.h"
#include "AI/cTriggerEventFlagsScriptRegistration.h"
#include "rws/classfactory.h"
#include "AI/AIUtil.h"
#include "AI/cAiTargetInfo.h"
#include "AI/cAIEvent.h"
#include "AI/cDamageTakenEvent.h"
#include "AI/cObjectInstigatorEvent.h"
#include "AI/cShotsCounterEvent.h"
#include "AI/cAttackedEvent.h"
#include "AI/cVocalEvent.h"
#include "AI/cPainVocalEvent.h"
#include "AI/cDangerVocalEvent.h"
#include "AI/cGrenadeVocalEvent.h"
#include "Sim/cTimeOfDay.h"
#include "cd2/memory.h"
#include <new>

Fun_Runtime::cScriptTypeRegistrar<AI::cAiPlayer> g_cAiPlayer("cAIPlayer", "cCharacterEntityIF");     // global at 0x83803448

namespace AI
{
    AIDamageCache::AIDamageCache()
    {
        Flush();
    }

    cAiPlayer::cAiPlayer()
        : m_nUnknown5A0(0), m_nUnknown5A4(0), m_nUnknown5A8(0), m_nUnknown5AC(0), m_nUnknown5B0(0), m_nUnknown5B4(0),
          m_nUnknown5B8(0), m_nUnknown5BC(0), m_nUnknown5C0(0), m_nUnknown5C4(0), m_nUnknown5C8(0), m_nUnknown5CC(0),
          m_nUnknown5D0(0), m_nUnknown5D4(0), m_fFriendlyFireTolerance(0.3f), m_fCombatFriendlyFireTolerance(1.0f),
          m_fUnknown600(20.0f), m_fUnknown604(20.0f), m_fUnknown608(0.0f), m_nMapStatus(kMS_Passive), m_nUnknown610(0),
          m_nShotsRemaining(0), m_bInterestingObjectReactionEnabled(true), m_nInterestingObjectPriority(2),
          m_bUnknown618(false), m_bUnknown619(false), m_bUnknown61A(false), m_bUnknown61B(false)
    {
        if (!Ext_82223708(0x18, this))
            Ext_82887CB8(0x18, new cUnknown828891A0(this));
        ++g_838015E0;
        Ext_828396F8(this);
        --g_838015E0;
    }

    RWS::CAttributeHandler *cAiPlayer::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cAiPlayer;
        return 0;
    }

    // CD2 0x82F604A8 initializes the descriptor at 0x8380343C through StaticCreateClass.
    const Fun_Runtime::cClass *cAiPlayer::ms_pcAiPlayerClass = &cAiPlayer::StaticCreateClass();

    Fun_Runtime::cClass &cAiPlayer::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAiPlayerClass = new Fun_Runtime::cClass(5, "cAiPlayer", 0x620);
        return *cAiPlayerClass;
    }

    const Fun_Runtime::cClass &cAiPlayer::RetClass() const
    {
        return *ms_pcAiPlayerClass;
    }

    const char *cAiPlayer::RetClassName() const
    {
        return "cAiPlayer";
    }

    const Fun_Runtime::cScriptTypeRegistration *cAiPlayer::RetScriptTypeRegistration() const
    {
        return &g_cAiPlayer;
    }

    const char *cTriggerEventFlagsScriptRegistration::RetName() const
    {
        return "eTriggerEventFlags";
    }

    const char *cEnemyStatusScriptRegistration::RetName() const
    {
        return "eEnemyStatus";
    }

    const char *cMapStatusScriptRegistration::RetName() const
    {
        return "eMapStatus";
    }

    void cAiPlayer::SetMapStatus(unsigned int nMapStatus)
    {
        m_nMapStatus = (etMapStatus)nMapStatus;
    }

    void cAiPlayer::SetFriendlyFireTolerance(float fTolerance)
    {
        m_fFriendlyFireTolerance = fTolerance;
    }

    void cAiPlayer::SetCombatFriendlyFireTolerance(float fTolerance)
    {
        m_fCombatFriendlyFireTolerance = fTolerance;
    }

    bool cAiPlayer::IsInterestingObjectReactionEnabled() const
    {
        return m_bInterestingObjectReactionEnabled;
    }

    void cAiPlayer::SetInterestingObjectReactionEnabled(bool bEnabled)
    {
        m_bInterestingObjectReactionEnabled = bEnabled;
    }

    unsigned char cAiPlayer::RetInterestingObjectPriority() const
    {
        return m_nInterestingObjectPriority;
    }

    void cAiPlayer::SetInterestingObjectPriority(unsigned char nPriority)
    {
        m_nInterestingObjectPriority = nPriority;
    }

    void cAiPlayer::SetShotsRemaining(short nShots)
    {
        m_nShotsRemaining = nShots;
    }

    cNonGameBase *cAiPlayer::RetOwnedVehicle() const
    {
        return m_pOwnedVehicle.m_pPtr ? static_cast<cNonGameBase *>(m_pOwnedVehicle.m_pPtr) : 0;
    }

    Fun_Runtime::cScriptHost *cAIEvent::RetSource() const
    {
        return m_pSource;
    }

    cCharacterEntityIF *cObjectInstigatorEvent::RetInstigator()
    {
        return m_pInstigator;
    }

    const Fun_Runtime::cScriptTypeRegistration *cShotsCounterEvent::RetScriptTypeRegistration() const
    {
        return &g_cShotsCounterEvent;
    }

    const Fun_Runtime::cScriptTypeRegistration *cAttackedEvent::RetScriptTypeRegistration() const
    {
        return &g_cAttackedEvent;
    }

    const Fun_Runtime::cScriptTypeRegistration *cVocalEvent::RetScriptTypeRegistration() const
    {
        return &g_cVocalEvent;
    }

    int cAiPlayer::RetConstantC8()
    {
        return 0xC8;
    }

    const Fun_Runtime::cScriptTypeRegistration *cPainVocalEvent::RetScriptTypeRegistration() const
    {
        return &g_cPainVocalEvent;
    }

    const Fun_Runtime::cScriptTypeRegistration *cDangerVocalEvent::RetScriptTypeRegistration() const
    {
        return &g_cDangerVocalEvent;
    }

    const Fun_Runtime::cScriptTypeRegistration *cGrenadeVocalEvent::RetScriptTypeRegistration() const
    {
        return &g_cGrenadeVocalEvent;
    }

    cCharacterEntityIF *cDamageTakenEvent::RetInstigator()
    {
        return m_pInstigator;
    }

    bool cAiTargetInfo::IsPrimaryFireBlocked() const
    {
        return m_bPrimaryFireBlocked;
    }

    bool cAiTargetInfo::IsTargetVisible() const
    {
        return m_bVisible;
    }
}

namespace Sim
{
    float cTimeOfDay::RetPhase()
    {
        return m_fPhase;
    }
}

namespace AI
{
    float cAiPlayer::RecallDamageCaused(CHARACTER::cCharacter *pCharacter)
    {
        return m_DamageCache.Read(pCharacter);
    }

    void cAiPlayer::SetFields4F8(int v, int w)
    {
        m_n4F8 = v;
        m_n4FC = v;
        m_n500 = w;
    }

    Fun_Runtime::RetVal cAiPlayer::cAiPlayerPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    const char *cAiPlayer::RetName() const
    {
        return m_pAIEntity->m_name;
    }

    void cAiPlayer::Slot20()
    {
        CHARACTER::cCharacter *character = RetCharacter();
        if (character)
            character->Slot20();
    }

    void cAiPlayer::Slot54()
    {
        RetCharacter()->Slot54();
    }

    void cAiPlayer::Slot60()
    {
        RetCharacter()->Slot60();
    }

    bool cAiPlayer::ShouldTriggerFootStepEvent()
    {
        if (RetCharacter()->RetLODLevel() <= 1)
        {
            float fTime = RetGameTime();
            if (m_fLastFootStepSoundTime < fTime - 10.0f)
            {
                m_fLastFootStepSoundTime = fTime;
                return true;
            }
        }
        return false;
    }

    bool cAiPlayer::ShouldTriggerBulletSoundEvent()
    {
        float fTime = RetGameTime();
        if (m_fLastBulletSoundTime < fTime - 3.0f)
        {
            m_fLastBulletSoundTime = fTime;
            return true;
        }
        return false;
    }

    static RWS::CClassFactory::CRegistrar cAiPlayerRegistrar(
        "cAiPlayer", cAiPlayer::MakeNew, 0x620, false);

    // CD2 0x82F604D0: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cAiPlayercCharacterEntityIFInheritRegistrar(
        AI::cAiPlayer::StaticCreateClass(), AI::cCharacterEntityIF::StaticCreateClass());

    // CD2 0x82F60588: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cAiPlayerSpawningRegistrar(
        cAiPlayer::StaticCreateClass(), cAiPlayer::SpawnFromPrototype);
}

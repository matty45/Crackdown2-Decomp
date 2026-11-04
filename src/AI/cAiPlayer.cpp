#include "fun_runtime/inheritance_registrar.h"
#include "AI/cCharacterEntityIF.h"
// AI/cAiPlayer.cpp. Names and layouts: include/AI/cAiPlayer.h. Some functions in this file's range belong to other
// classes: the linker folded identical getters and kept the copies from this object (Sim::cTimeOfDay::RetPhase,
// AI::cAiTargetInfo::IsPrimaryFireBlocked / IsTargetVisible, AI::cAIEvent::RetSource, AI::cObjectInstigatorEvent::
// RetInstigator, AI::cDamageTakenEvent::RetInstigator; their headers give the evidence).
// Not named yet:
//   - RetTriggerEventFlags / RetEnemyStatus / RetMapStatus (0x823E7988 / 0x823E7998 / 0x823E79A8) return the names of
//     script enums. They are slot 1 of three small registrar vtables (0x820FB0F0, 0x820FB0FC, 0x820FB108), not
//     cAiPlayer methods; the registrar classes have no known name.
//   - SetFields4F8 (0x823E92B8) and m_n4F8/m_n4FC/m_n500 are unnamed (slot 125 of cAiPlayer vtable).
//   - RetConstantC8 (0x823E7B30) is slot 26 of the vtable 0x820FB114, whose object 0x82377190 builds; its class is not
//     known.
#include "AI/cAiPlayer.h"
#include "rws/classfactory.h"
#include "AI/AIUtil.h"
#include "AI/cAiTargetInfo.h"
#include "AI/cAIEvent.h"
#include "AI/cDamageTakenEvent.h"
#include "AI/cObjectInstigatorEvent.h"
#include "Sim/cTimeOfDay.h"
#include "cd2/memory.h"

#include <new>

unsigned char g_cAiPlayer;     // global at 0x83803448
unsigned char g_AIE_SHOTS_COUNTER;     // global at 0x83817824
unsigned char g_AIE_ATTACKED;     // global at 0x8381798C
unsigned char g_AIE_VOCAL;     // global at 0x83818B7C
unsigned char g_AIE_PAIN_VOCAL;     // global at 0x83818BA0
unsigned char g_AIE_DANGER_VOCAL;     // global at 0x83818BC4
unsigned char g_AIE_GRENADE_VOCAL;     // global at 0x83818BE8

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

    const char *cAiPlayer::RetTriggerEventFlags() const
    {
        return "eTriggerEventFlags";
    }

    const char *cAiPlayer::RetEnemyStatus() const
    {
        return "eEnemyStatus";
    }

    const char *cAiPlayer::RetMapStatus() const
    {
        return "eMapStatus";
    }

    void *cAiPlayer::GetPtrcAiPlayer() const
    {
        return &g_cAiPlayer;
    }

    void *cAiPlayer::GetPtrAIE_SHOTS_COUNTER() const
    {
        return &g_AIE_SHOTS_COUNTER;
    }

    void *cAiPlayer::GetPtrAIE_ATTACKED() const
    {
        return &g_AIE_ATTACKED;
    }

    void *cAiPlayer::GetPtrAIE_VOCAL() const
    {
        return &g_AIE_VOCAL;
    }

    void *cAiPlayer::GetPtrAIE_PAIN_VOCAL() const
    {
        return &g_AIE_PAIN_VOCAL;
    }

    void *cAiPlayer::GetPtrAIE_DANGER_VOCAL() const
    {
        return &g_AIE_DANGER_VOCAL;
    }

    void *cAiPlayer::GetPtrAIE_GRENADE_VOCAL() const
    {
        return &g_AIE_GRENADE_VOCAL;
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

    cNonGameBase *cAIEvent::RetSource() const
    {
        return m_pSource;
    }

    cCharacterEntityIF *cObjectInstigatorEvent::RetInstigator()
    {
        return m_pInstigator;
    }

    int cAiPlayer::RetConstantC8()
    {
        return 0xC8;
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
        if (RetLODLevel() <= 1)
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
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cAiPlayerRegistrar(
        "cAiPlayer", cAiPlayer::MakeNew, 0x620, false);
}

// CD2 0x82F604D0: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar cAiPlayercCharacterEntityIFInheritRegistrar(
        AI::cAiPlayer::StaticCreateClass(), AI::cCharacterEntityIF::StaticCreateClass());
}

#include "gom/proto_registrar.h"

// CD2 0x82F60588: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace AI
{
    static GOM::cProtoRegistrar cAiPlayerSpawningRegistrar(
        cAiPlayer::StaticCreateClass(), cAiPlayer::SpawnFromPrototype);
}

#include "cd2/memory.h"

// CD2 0x823E78A8: the class factory builds the prototype.
namespace AI
{
    RWS::CAttributeHandler *cAiPlayer::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cAiPlayerPrototype(packet);
    }
}

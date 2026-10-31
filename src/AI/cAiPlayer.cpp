// AI/cAiPlayer.cpp. Names and layouts: include/AI/cAiPlayer.h. Some functions in this file's range belong to other
// classes: the linker folded identical getters and kept the copies from this object (Sim::cTimeOfDay::RetPhase,
// AI::cAiTargetInfo::IsPrimaryFireBlocked / IsTargetVisible, AI::cAIEvent::RetSource; their headers give the evidence).
// Not named yet:
//   - RetTriggerEventFlags / RetEnemyStatus / RetMapStatus (0x823E7988 / 0x823E7998 / 0x823E79A8) return the names of
//     script enums. They are slot 1 of three small registrar vtables (0x820FB0F0, 0x820FB0FC, 0x820FB108), not
//     cAiPlayer methods; the registrar classes have no known name.
//   - RetConstantC8 (0x823E7B30) is slot 26 of the vtable 0x820FB114, whose object 0x82377190 builds; its class is not
//     known.
//   - GetField60 / GetField50 (0x823E7A88 / 0x823E7C18) are AI event getters: CD2's event script registrations use them
//     as "RetInstigator" (0x8243DA44) and as "RetObject", "RetCarrier", "RetKiller" and a dozen more. Which event
//     classes they belong to is not known, so they still read cNonGameBase fields.
#include "AI/cAiPlayer.h"
#include "rws/classfactory.h"
#include "AI/AIUtil.h"
#include "AI/cAiTargetInfo.h"
#include "AI/cAIEvent.h"
#include "Sim/cTimeOfDay.h"
#include "cd2/memory.h"

inline void *operator new(size_t, void *memory) { return memory; }

namespace AI
{
    AIDamageCache::AIDamageCache()
    {
        Flush();
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

    void *cAiPlayer::GetField60() const
    {
        char *p = m_p60;
        if (p != 0)
            return p - 0x1C;
        return 0;
    }

    int cAiPlayer::RetConstantC8()
    {
        return 0xC8;
    }

    void *cAiPlayer::GetField50() const
    {
        char *p = m_p50;
        if (p != 0)
            return p - 0x1C;
        return 0;
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

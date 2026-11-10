// src/PLAYER/cPlayer.cpp
//
// Class: PLAYER::cPlayer. The recovered script accessors are defined below.
// The address range and ownership evidence are in config/splits.txt; RuffKing's object is cPlayer.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Player/cPlayer.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/PLAYER/cPlayer.cpp

// Not named yet: m_byteD99 and m_fEC4 have no script or reference name.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "GDb/cDebugPageHandler.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cCharacterEntityIF.h"
#include "PLAYER/cPlayer.h"
#include "PLAYER/cBreakoutInputScriptRegistration.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include <stddef.h>
#include <new>
#include "fun_runtime/script_type_registrar.h"
#include "GMan/cGameManager.h"
#include "AI/AIUtil.h"
#include "Input/cGameControlManager.h"
#include "Input/InputInitialisation.h"
#include "AI/cPlayerAIBreakoutAttemptEvent.h"
#include "AI/cDeadPlayerEvent.h"
#include "AI/cReincarnatedEvent.h"

namespace PLAYER
{
    // CD2's initializer 0x82FF3C38 calls StaticCreateClass and stores the result in 0x8384A818.
    const Fun_Runtime::cClass *cPlayer::ms_pcPlayerClass = &cPlayer::StaticCreateClass();

    const char *cBreakoutInputScriptRegistration::RetName() const
    {
        return "eBreakoutInput";
    }
}

// CD2 places these AI event getters (0x8271F168..0x8271F188) between cPlayer's own functions, so the AI block sits here.
namespace AI
{
    const Fun_Runtime::cScriptTypeRegistration *cPlayerAIBreakoutAttemptEvent::RetScriptTypeRegistration() const
    {
        return &g_cPlayerAIBreakoutAttemptEvent;
    }

    const Fun_Runtime::cScriptTypeRegistration *cDeadPlayerEvent::RetScriptTypeRegistration() const
    {
        return &g_cDeadPlayerEvent;
    }

    const Fun_Runtime::cScriptTypeRegistration *cReincarnatedEvent::RetScriptTypeRegistration() const
    {
        return &g_cReincarnatedEvent;
    }
}

namespace PLAYER
{
    Fun_Runtime::cClass &cPlayer::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPlayerClass = new Fun_Runtime::cClass(4, "cPlayer", 0x1160);
        return *cPlayerClass;
    }

    RWS::CAttributeHandler *cPlayer::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cPlayerPrototype(packet);
    }

    Fun_Runtime::RetVal cPlayer::cPlayerPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    RWS::CAttributeHandler *cPlayer::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cPlayer;
        return 0;
    }

    const char *cPlayer::RetName() const
    {
        return m_strName;
    }

    const char *cPlayer::RetClassName() const
    {
        return "cPlayer";
    }

    void cPlayer::SetAIActive(bool active)
    {
        m_bIsAIActive = active;
        SetAITargeting(m_bIsAITargeting);
    }

    bool cPlayer::IsAIActive() const
    {
        return m_bIsAIActive;
    }

    bool cPlayer::IsAITargeting() const
    {
        return m_bIsAITargeting;
    }

    void cPlayer::SetAutomaticAIBreakout(bool enabled, unsigned int flags)
    {
        m_bAutomaticAIBreakout = enabled;
        m_nAutomaticAIBreakoutFlags = flags;
    }

    bool cPlayer::IsAutomaticAIBreakout() const
    {
        return m_bAutomaticAIBreakout;
    }

    int cPlayer::RetAutomaticAIBreakoutFlags() const
    {
        return m_nAutomaticAIBreakoutFlags;
    }

    void *cPlayer::RetCameraPtr() const
    {
        return m_pCamera;
    }

    void cPlayer::SetAITargeting(bool bAITargeting)
    {
        if (m_bIsAIActive || !bAITargeting)
        {
            CHARACTER::cCharacter *pCharacter = RetCharacter();
            if (pCharacter && pCharacter->IsA(*CHARACTER::cCwTransCharacterWrapper::ms_pcCwTransCharacterWrapperClass))
                static_cast<CHARACTER::cCwTransCharacterWrapper *>(pCharacter)->SetAITargeting(bAITargeting);
        }
        m_bIsAITargeting = bAITargeting;
    }

    void cPlayer::ForceCharacterH2HContact()
    {
        m_nH2HContactFrame = GMan::cGameManager::ms_nGameTicks;
    }

    bool cPlayer::HasRecentlyHadH2HContact()
    {
        return GMan::cGameManager::ms_nGameTicks < m_nH2HContactFrame + 30;
    }

    bool cPlayer::vf97()
    {
        return m_byteD99;
    }

    void cPlayer::vf130()
    {
        m_fEC4 = 0.0f;
    }

    void cPlayer::vf131()
    {
        if (m_eNetRole == eNR_Authority)
        {
            Input::cGameController *pController = Input::cGameControlManager::RetInstancePtr()->RetPrimaryController();
            if (pController)
                pController->DebounceAction(GA_CHARACTER_OBJECTDROP);
        }
    }

    void cPlayer::vf134()
    {
        if (m_eNetRole == eNR_Authority)
        {
            Input::cGameController *pController = Input::cGameControlManager::RetInstancePtr()->RetPrimaryController();
            if (pController)
                pController->DebounceAction(GA_CHARACTER_OBJECTINTERACT);
        }
    }

    bool cPlayer::ShouldTriggerFootStepEvent()
    {
        return RetCharacter()->RetLODLevel() <= 1;
    }

    bool cPlayer::ShouldTriggerBulletSoundEvent()
    {
        float fTime = AI::RetGameTime();
        if (m_fLastBulletSoundTime < fTime - 1.0f)
        {
            m_fLastBulletSoundTime = fTime;
            return true;
        }
        return false;
    }

    static RWS::CClassFactory::CRegistrar cPlayerRegistrar(
        "cPlayer", cPlayer::MakeNew, 0x1160, false);

    // CD2 0x82FF3CC8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cPlayercCharacterEntityIFInheritRegistrar(
        PLAYER::cPlayer::StaticCreateClass(), AI::cCharacterEntityIF::StaticCreateClass());

    // CD2 0x82FF3C60: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cPlayercDebugPageHandlerInheritRegistrar(
        PLAYER::cPlayer::StaticCreateClass(), GDb::cDebugPageHandler::StaticCreateClass());

    // CD2 0x82FF3D80: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cPlayerSpawningRegistrar(
        cPlayer::StaticCreateClass(), cPlayer::SpawnFromPrototype);

    // CD2 script-type registration; constructor/table evidence identifies the child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cPlayer> cPlayerScriptRegistrar(
        "cPlayer", "cCharacterEntityIF");

    const Fun_Runtime::cScriptTypeRegistration *cPlayer::RetScriptTypeRegistration() const
    {
        return &cPlayerScriptRegistrar;
    }
}

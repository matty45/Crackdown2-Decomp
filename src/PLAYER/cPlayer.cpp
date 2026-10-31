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

#include "PLAYER/cPlayer.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include <stddef.h>

inline void *operator new(size_t, void *memory) { return memory; }

namespace PLAYER
{
    // CD2's initializer 0x82FF3C38 calls StaticCreateClass and stores the result in 0x8384A818.
    const Fun_Runtime::cClass *cPlayer::ms_pcPlayerClass = &cPlayer::StaticCreateClass();

    Fun_Runtime::cClass &cPlayer::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPlayerClass = new Fun_Runtime::cClass(4, "cPlayer", 0x1160);
        return *cPlayerClass;
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
}

namespace PLAYER
{
    static RWS::CClassFactory::CRegistrar cPlayerRegistrar(
        "cPlayer", cPlayer::MakeNew, 0x1160, false);
}

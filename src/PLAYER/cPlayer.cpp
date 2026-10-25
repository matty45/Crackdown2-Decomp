// src/PLAYER/cPlayer.cpp
//
// Class: cPlayer (namespace: PLAYER). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cPlayer.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code):
// include/ref/ruffking/PLAYER_cPlayer.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/PLAYER/cPlayer.cpp

#include "PLAYER/cPlayer.h"

namespace PLAYER
{
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

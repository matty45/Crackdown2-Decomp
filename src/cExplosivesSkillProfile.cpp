// src/cExplosivesSkillProfile.cpp
//
// Class: cExplosivesSkillProfile (namespace: unknown). Set up automatically: no function is matched yet. The address
// range and the evidence for it are in config/splits.txt; RuffKing's object for it is cExplosivesSkillProfile.obj.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cExplosivesSkillProfile.cpp


// CD2 0x82753190.

#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "rws/classfactory.h"
#include "unknown/cExplosivesSkillProfile.h"

namespace unknown
{
    const char *cExplosivesSkillProfile::RetClassName() const
    {
        return "cExplosivesSkillProfile";
    }

    // CD2 0x82FFD408 (initializer) and 0x83041D40 (at-exit destructor).
    static RWS::CClassFactory::CRegistrar cExplosivesSkillProfileRegistrar(
        "cExplosivesSkillProfile", cExplosivesSkillProfile::MakeNew, 0xA4, false);
}

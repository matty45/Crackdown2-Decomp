// RPG/cPvPSkillset.cpp: RuffKing's Libraries/Shared/RPG/cPvPSkillset.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "fun_runtime/class.h"
#include "rws/classfactory.h"
#include "RPG/cPvPLevelSetup.h"
#include "RPG/cPvPSkillsetProfile.h"
#include "cd2/memory.h"

namespace RPG
{
    static RWS::CClassFactory::CRegistrar cPvPLevelSetupRegistrar(
        "cPvPLevelSetup", cPvPLevelSetup::MakeNew, 0x10C, false);

    static RWS::CClassFactory::CRegistrar cPvPSkillsetProfileRegistrar(
        "cPvPSkillsetProfile", cPvPSkillsetProfile::MakeNew, 0x34, false);
}

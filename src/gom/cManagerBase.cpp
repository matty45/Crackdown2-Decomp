// gom/cManagerBase.cpp: RuffKing's Libraries/Shared/GameObjectManager/cManagerBase.cpp.
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
#include "gom/cManagerBase.h"
#include "cd2/memory.h"

namespace GOM
{
    Fun_Runtime::cClass &cManagerBase::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cManagerBaseClass = new Fun_Runtime::cClass(0x7432AF5E, "cManagerBase", 0x54);
        return *cManagerBaseClass;
    }

    const Fun_Runtime::cClass *cManagerBase::ms_pcManagerBaseClass = &cManagerBase::StaticCreateClass();
}

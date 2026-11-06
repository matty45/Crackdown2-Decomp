// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "VFX/cReflectionMesh.h"

namespace VFX
{
    const char *cReflectionMesh::RetClassName() const
    {
        return "cReflectionMesh";
    }

    static RWS::CClassFactory::CRegistrar cReflectionMeshRegistrar(
        "cReflectionMesh", cReflectionMesh::MakeNew, 0x20, false);
}

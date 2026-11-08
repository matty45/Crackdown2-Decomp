// src/Prop/cProp.cpp
//
// Class: cProp (namespace: Prop). Set up automatically: no function is matched yet. The address range and the evidence
// for it are in config/splits.txt; RuffKing's object for it is cProp.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Props/cProp.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Prop/cProp.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "Prop/cProp.h"
#include "rws/classfactory.h"
#include "fun_runtime/script_type_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/proto_registrar.h"
#include "cd2/memory.h"
#include <new>

namespace Prop
{
    RWS::CAttributeHandler *cProp::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cPropPrototype(packet);
    }

    const char *cProp::RetClassName() const
    {
        return "cProp";
    }

    // CD2 0x82FF5298 registers the prototype factory 0x82729378 for a 0xE30-byte cProp.
    static RWS::CClassFactory::CRegistrar cPropRegistrar(
        "cProp", cProp::MakeNew, 0xE30, false);

    static GOM::cProtoRegistrar cPropSpawningRegistrar(
        cProp::StaticCreateClass(), cProp::SpawnFromPrototype);

    // CD2 script-type registration names this child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cProp> cPropScriptRegistrar(
        "cProp", "cDynamicBody");

    RWS::CAttributeHandler *cProp::SpawnFromPrototype(GOM::cObjectPrototype *pPrototype, void *pMem)
    {
        if (pMem)
            return new (pMem) cProp(pPrototype);
        return 0;
    }

    Fun_Runtime::cClass &cProp::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x2, "cProp", 0xE30);
        return *descriptor;
    }

    const Fun_Runtime::cClass *cProp::ms_pcPropClass = &cProp::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cPropcNetDynamicBodyInheritRegistrar(
        cProp::StaticCreateClass(), PHYSICS::cNetDynamicBody::StaticCreateClass());

    const Fun_Runtime::cClass &cProp::RetClass() const
    {
        return *ms_pcPropClass;
    }
}

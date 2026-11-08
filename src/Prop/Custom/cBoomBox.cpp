// src/Prop/Custom/cBoomBox.cpp
//
// Class: cBoomBox (namespace: Prop). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cBoomBox.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Props/Custom/cBoomBox.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Prop/Custom/cBoomBox.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "rws/classfactory.h"
#include "Prop/cBoomBox.h"
#include "Prop/cBoomBoxPrototype.h"
#include <new>
#include "fun_runtime/inheritance_registrar.h"
#include "gom/proto_registrar.h"
#include "cd2/memory.h"

namespace Prop
{
    RWS::CAttributeHandler *cBoomBox::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cBoomBoxPrototype(packet);
    }

    const char *cBoomBox::RetClassName() const
    {
        return "cBoomBox";
    }

    const Fun_Runtime::cClass *cBoomBox::ms_pcBoomBoxClass = &cBoomBox::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cBoomBoxcPropInheritRegistrar(
        cBoomBox::StaticCreateClass(), cProp::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cBoomBoxRegistrar(
        "cBoomBox", cBoomBox::MakeNew, 0xe30, false);

    static GOM::cProtoRegistrar cBoomBoxSpawningRegistrar(
        cBoomBox::StaticCreateClass(), cBoomBox::SpawnFromPrototype);

    Fun_Runtime::cClass &cBoomBox::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cBoomBoxClass = new Fun_Runtime::cClass(0xD433, "cBoomBox", 0xE30);
        return *cBoomBoxClass;
    }
}

// src/Equip/Gadget/Refractor/cRefractor.cpp
//
// Class: cRefractor (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cRefractor.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Gadget/Refractor/cRefractor.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Gadget/Refractor/cRefractor.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Equip/cCWWeapon.h"
#include "rws/classfactory.h"
#include "Equip/cRefractor.h"
#include "cd2/memory.h"

namespace Equip
{
    const Fun_Runtime::cClass *cRefractor::ms_pcRefractorClass = &cRefractor::StaticCreateClass();

    Fun_Runtime::cClass &cRefractor::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cRefractorClass = new Fun_Runtime::cClass(0x27415, "cRefractor", 0xA60);
        return *cRefractorClass;
    }

    static RWS::CClassFactory::CRegistrar cRefractorRegistrar(
        "cRefractor", cRefractor::MakeNew, 0xA60, false);

    // CD2 0x82FCD658: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cRefractorcCWWeaponInheritRegistrar(
        Equip::cRefractor::StaticCreateClass(), Equip::cCWWeapon::StaticCreateClass());

    // CD2 0x82FCD710: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cRefractorSpawningRegistrar(
        cRefractor::StaticCreateClass(), cRefractor::SpawnFromPrototype);

    const char *cRefractor::RetClassName() const
    {
        return "cRefractor";
    }

    const Fun_Runtime::cClass &cRefractor::RetClass() const
    {
        return *ms_pcRefractorClass;
    }

    bool cRefractor::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcRefractorClass->IsA(c);
    }

    cRefractor::cRefractor()
    {
    }

    RWS::CAttributeHandler *cRefractor::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cRefractor;
        return 0;
    }
}

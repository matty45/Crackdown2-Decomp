#include "fun_runtime/retval.h"
#include "Equip/cCWSatchelCharge.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/proto_registrar.h"
#include "rws/classfactory.h"
// src/Equip/Gadget/cPortableLaunchPad.cpp
//
// Class: cPortableLaunchPad (namespace: Equip). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cPortableLaunchPad.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Gadget/cPortableLaunchPad.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Gadget/cPortableLaunchPad.cpp

#include "Equip/cPortableLaunchPad.h"
#include "cd2/memory.h"

namespace Equip
{
    const Fun_Runtime::cClass *cPortableLaunchPad::ms_pcPortableLaunchPadClass = &cPortableLaunchPad::StaticCreateClass();

    Fun_Runtime::cClass &cPortableLaunchPad::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPortableLaunchPadClass = new Fun_Runtime::cClass(0x27412, "cPortableLaunchPad", 0xCA0);
        return *cPortableLaunchPadClass;
    }
}

namespace Equip
{
    static RWS::CClassFactory::CRegistrar cPortableLaunchPadRegistrar(
        "cPortableLaunchPad", cPortableLaunchPad::MakeNew, 0xCA0, false);
}

// CD2 0x82FCCEA0: register the class descriptor and placement factory.
namespace Equip
{
    static GOM::cProtoRegistrar cPortableLaunchPadSpawningRegistrar(
        cPortableLaunchPad::StaticCreateClass(), cPortableLaunchPad::SpawnFromPrototype);
}

// CD2 0x82FCCDE8: runtime class inheritance registration.
namespace Equip
{
    static Fun_Runtime::cInheritanceRegistrar cPortableLaunchPadcCWSatchelChargeInheritRegistrar(
        Equip::cPortableLaunchPad::StaticCreateClass(), Equip::cCWSatchelCharge::StaticCreateClass());
}

namespace Equip
{
    const char *cPortableLaunchPad::RetClassName() const
    {
        return "cPortableLaunchPad";
    }
}

namespace Equip
{
    RWS::CAttributeHandler *cPortableLaunchPad::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cPortableLaunchPad;
        return 0;
    }
}

namespace Equip
{
    Fun_Runtime::RetVal cPortableLaunchPad::cJumpPadPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}

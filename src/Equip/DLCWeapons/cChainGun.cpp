// src/Equip/DLCWeapons/cChainGun.cpp
//
// Class: cChainGun (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cChainGun.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/DLCWeapons/cChainGun.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/DLCWeapons/cChainGun.cpp

#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Equip/cCWFirearm.h"
#include "rws/classfactory.h"
#include "Equip/cChainGun.h"
#include "cd2/memory.h"
#include <new>

namespace Equip
{
    const Fun_Runtime::cClass *cChainGun::ms_pcChainGunClass = &cChainGun::StaticCreateClass();

    RWS::CAttributeHandler *cChainGun::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cChainGun;
        return 0;
    }

    Fun_Runtime::cClass &cChainGun::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cChainGunClass = new Fun_Runtime::cClass(0x13266, "cChainGun", 0xAC0);
        return *cChainGunClass;
    }

    static RWS::CClassFactory::CRegistrar cChainGunRegistrar(
        "cChainGun", cChainGun::MakeNew, 0xAC0, false);

    // CD2 0x82FCE550: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cChainGuncCWFirearmInheritRegistrar(
        Equip::cChainGun::StaticCreateClass(), Equip::cCWFirearm::StaticCreateClass());

    // CD2 0x82FCE608: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cChainGunSpawningRegistrar(
        cChainGun::StaticCreateClass(), cChainGun::SpawnFromPrototype);

    RWS::CAttributeHandler *cChainGun::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cChainGunPrototype(packet);
    }

    const char *cChainGun::RetClassName() const
    {
        return "cChainGun";
    }

    // CD2 0x82616780 has no derived cleanup beyond vtable restoration.
    cChainGun::~cChainGun()
    {
    }
}

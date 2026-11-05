// src/Equip/Weapon/cUVTurret.cpp
//
// Class: cUVTurret (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cUVTurret.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Weapon/cUVTurret.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Weapon/cUVTurret.cpp

#include "fun_runtime/retval.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Equip/cCWFirearm.h"
#include "rws/classfactory.h"
#include "Equip/cUVTurret.h"
#include "cd2/memory.h"

namespace Equip
{
    const Fun_Runtime::cClass *cUVTurret::ms_pcUVTurretClass = &cUVTurret::StaticCreateClass();

    Fun_Runtime::cClass &cUVTurret::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cUVTurretClass = new Fun_Runtime::cClass(0x1326A, "cUVTurret", 0xAB0);
        return *cUVTurretClass;
    }

    static RWS::CClassFactory::CRegistrar cUVTurretRegistrar(
        "cUVTurret", cUVTurret::MakeNew, 0xAB0, false);

    // CD2 0x82FD4A98: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cUVTurretcCWFirearmInheritRegistrar(
        Equip::cUVTurret::StaticCreateClass(), Equip::cCWFirearm::StaticCreateClass());

    // CD2 0x82FD4B50: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cUVTurretSpawningRegistrar(
        cUVTurret::StaticCreateClass(), cUVTurret::SpawnFromPrototype);

    const char *cUVTurret::RetClassName() const
    {
        return "cUVTurret";
    }

    const Fun_Runtime::cClass &cUVTurret::RetClass() const
    {
        return *ms_pcUVTurretClass;
    }

    bool cUVTurret::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcUVTurretClass->IsA(c);
    }

    // CD2 0x8263BD10 has no derived cleanup beyond vtable restoration.
    cUVTurret::~cUVTurret()
    {
    }

    Fun_Runtime::RetVal cUVTurret::cUVTurretPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}

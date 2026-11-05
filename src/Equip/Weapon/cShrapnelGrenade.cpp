// src/Equip/Weapon/cShrapnelGrenade.cpp
//
// Class: cShrapnelGrenade (namespace: Equip). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cShrapnelGrenade.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Weapon/cShrapnelGrenade.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Weapon/cShrapnelGrenade.cpp

#include "fun_runtime/retval.h"
#include "Equip/cExplosiveGrenade.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/proto_registrar.h"
#include "rws/classfactory.h"
#include "Equip/cShrapnelGrenade.h"
#include "cd2/memory.h"

namespace Equip
{
    const Fun_Runtime::cClass *cShrapnelGrenade::ms_pcShrapnelGrenadeClass = &cShrapnelGrenade::StaticCreateClass();

    Fun_Runtime::cClass &cShrapnelGrenade::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cShrapnelGrenadeClass = new Fun_Runtime::cClass(0x3E8C, "cShrapnelGrenade", 0x9D0);
        return *cShrapnelGrenadeClass;
    }

    static RWS::CClassFactory::CRegistrar cShrapnelGrenadeRegistrar(
        "cShrapnelGrenade", cShrapnelGrenade::MakeNew, 0x9D0, false);

    // CD2 0x82FD0998: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cShrapnelGrenadeSpawningRegistrar(
        cShrapnelGrenade::StaticCreateClass(), cShrapnelGrenade::SpawnFromPrototype);

    // CD2 0x82FD08E0: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cShrapnelGrenadecExplosiveGrenadeInheritRegistrar(
        Equip::cShrapnelGrenade::StaticCreateClass(), Equip::cExplosiveGrenade::StaticCreateClass());

    const char *cShrapnelGrenade::RetClassName() const
    {
        return "cShrapnelGrenade";
    }

    RWS::CAttributeHandler *cShrapnelGrenade::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cShrapnelGrenade;
        return 0;
    }

    const Fun_Runtime::cClass &cShrapnelGrenade::RetClass() const
    {
        return *ms_pcShrapnelGrenadeClass;
    }

    bool cShrapnelGrenade::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcShrapnelGrenadeClass->IsA(c);
    }

    // CD2 0x82621D08 has no derived cleanup beyond vtable restoration.
    cShrapnelGrenade::~cShrapnelGrenade()
    {
    }

    Fun_Runtime::RetVal cShrapnelGrenade::cShrapnelGrenadePrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}

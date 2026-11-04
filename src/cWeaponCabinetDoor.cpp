#include "fun_runtime/retval.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cPrismaticProp.h"
#include "rws/classfactory.h"
// src/cWeaponCabinetDoor.cpp
//
// Class: cWeaponCabinetDoor (namespace: unknown). Set up automatically: no function is matched yet. The address range
// and the evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cWeaponCabinetDoor.cpp

#include "unknown/cWeaponCabinetDoor.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass *cWeaponCabinetDoor::ms_pcWeaponCabinetDoorClass = &cWeaponCabinetDoor::StaticCreateClass();

    Fun_Runtime::cClass &cWeaponCabinetDoor::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cWeaponCabinetDoorClass = new Fun_Runtime::cClass(0x1021, "cWeaponCabinetDoor", 0xEE0);
        return *cWeaponCabinetDoorClass;
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cWeaponCabinetDoorRegistrar(
        "cWeaponCabinetDoor", cWeaponCabinetDoor::MakeNew, 0xEE0, false);
}

// CD2 0x82FF9D50: runtime class inheritance registration.
namespace unknown
{
    static Fun_Runtime::cInheritanceRegistrar cWeaponCabinetDoorcPrismaticPropInheritRegistrar(
        unknown::cWeaponCabinetDoor::StaticCreateClass(), Prop::cPrismaticProp::StaticCreateClass());
}

// CD2 0x82FF9E08: register the class descriptor and placement factory.
namespace unknown
{
    static GOM::cProtoRegistrar cWeaponCabinetDoorSpawningRegistrar(
        cWeaponCabinetDoor::StaticCreateClass(), cWeaponCabinetDoor::SpawnFromPrototype);
}

namespace unknown
{
    const char *cWeaponCabinetDoor::RetClassName() const
    {
        return "cWeaponCabinetDoor";
    }
}

namespace unknown
{
    const Fun_Runtime::cClass &cWeaponCabinetDoor::RetClass() const
    {
        return *ms_pcWeaponCabinetDoorClass;
    }
}

namespace unknown
{
    Fun_Runtime::RetVal cWeaponCabinetDoor::cWeaponCabinetDoorPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}

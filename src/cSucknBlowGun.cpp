// src/cSucknBlowGun.cpp
//
// Class: cSucknBlowGun (namespace: unknown). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cSucknBlowGun.cpp

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
#include "unknown/cSucknBlowGun.h"
#include "cd2/memory.h"
#include "unknown/cSucknBlowGunPrototype.h"

namespace unknown
{
    const Fun_Runtime::cClass *cSucknBlowGun::ms_pcSucknBlowGunClass = &cSucknBlowGun::StaticCreateClass();

    Fun_Runtime::cClass &cSucknBlowGun::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSucknBlowGunClass = new Fun_Runtime::cClass(0x27418, "cSucknBlowGun", 0xDF0);
        return *cSucknBlowGunClass;
    }

    static RWS::CClassFactory::CRegistrar cSucknBlowGunRegistrar(
        "cSucknBlowGun", cSucknBlowGun::MakeNew, 0xDF0, false);

    // CD2 0x82FD3F00: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cSucknBlowGuncCWWeaponInheritRegistrar(
        unknown::cSucknBlowGun::StaticCreateClass(), Equip::cCWWeapon::StaticCreateClass());

    // CD2 0x82FD3FB8: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cSucknBlowGunSpawningRegistrar(
        cSucknBlowGun::StaticCreateClass(), cSucknBlowGun::SpawnFromPrototype);

    RWS::CAttributeHandler *cSucknBlowGun::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cSucknBlowGunPrototype(packet);
    }

    bool cSucknBlowGun::InitiateReload()
    {
        return cWeapon::InitiateReload();
    }

    const char *cSucknBlowGun::RetClassName() const
    {
        return "cSucknBlowGun";
    }

    RWS::CAttributeHandler *cSucknBlowGun::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cSucknBlowGun;
        return 0;
    }

    Fun_Runtime::RetVal cSucknBlowGunPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}

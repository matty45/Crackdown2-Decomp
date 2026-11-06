// src/cSticklerGrenade.cpp
//
// Class: cSticklerGrenade (namespace: unknown). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cSticklerGrenade.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "Equip/cExplosiveGrenade.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/proto_registrar.h"
#include "rws/classfactory.h"
#include "unknown/cSticklerGrenade.h"
#include "cd2/memory.h"
#include "fun_runtime/script_type_registrar.h"

namespace unknown
{
    const Fun_Runtime::cClass *cSticklerGrenade::ms_pcSticklerGrenadeClass = &cSticklerGrenade::StaticCreateClass();

    Fun_Runtime::cClass &cSticklerGrenade::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSticklerGrenadeClass = new Fun_Runtime::cClass(0x10144, "cSticklerGrenade", 0x9E0);
        return *cSticklerGrenadeClass;
    }

    static RWS::CClassFactory::CRegistrar cSticklerGrenadeRegistrar(
        "cSticklerGrenade", cSticklerGrenade::MakeNew, 0x9E0, false);

    // CD2 0x82FD14E0: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cSticklerGrenadeSpawningRegistrar(
        cSticklerGrenade::StaticCreateClass(), cSticklerGrenade::SpawnFromPrototype);

    // CD2 0x82FD1428: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cSticklerGrenadecExplosiveGrenadeInheritRegistrar(
        unknown::cSticklerGrenade::StaticCreateClass(), Equip::cExplosiveGrenade::StaticCreateClass());

    const char *cSticklerGrenade::RetClassName() const
    {
        return "cSticklerGrenade";
    }

    // CD2 0x82623420 has no derived cleanup beyond vtable restoration.
    cSticklerGrenade::~cSticklerGrenade()
    {
    }

    // CD2 script-type registration; constructor/table evidence identifies the child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cSticklerGrenade> cSticklerGrenadeScriptRegistrar(
        "cSticklerGrenade", "cExplosiveGrenade");

    const Fun_Runtime::cScriptTypeRegistration *cSticklerGrenade::RetScriptTypeRegistration() const
    {
        return &cSticklerGrenadeScriptRegistrar;
    }
}

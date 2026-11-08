// src/Equip/Gadget/cCloakingDevice.cpp
//
// Class: cCloakingDevice (namespace: Equip). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cCloakingDevice.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Gadget/cCloakingDevice.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Gadget/cCloakingDevice.cpp

// CD2 0x82FCC770: class descriptor and placement factory.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "fun_runtime/retval.h"
#include "Equip/cCloakingDevice.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/script_type_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "cd2/memory.h"
#include "rws/classfactory.h"
#include <new>

namespace Equip
{
    // CD2 0x82FCC720: register the class factory.
    static RWS::CClassFactory::CRegistrar cCloakingDeviceRegistrar(
        "cCloakingDevice", cCloakingDevice::MakeNew, 0x9C0, false);

    static GOM::cProtoRegistrar cCloakingDeviceSpawningRegistrar(
        cCloakingDevice::StaticCreateClass(), cCloakingDevice::SpawnFromPrototype);

    const char *cCloakingDevice::RetClassName() const
    {
        return "cCloakingDevice";
    }

    Fun_Runtime::RetVal cCloakingDevice::cCloakingDevicePrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    // CD2 script-type registration names this child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cCloakingDevice> cCloakingDeviceScriptRegistrar(
        "cCloakingDevice", "cGrenade");

    Fun_Runtime::cClass &cCloakingDevice::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x10140, "cCloakingDevice", 0x9C0);
        return *descriptor;
    }

    const Fun_Runtime::cClass *cCloakingDevice::ms_pcCloakingDeviceClass = &cCloakingDevice::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cCloakingDevicecGrenadeInheritRegistrar(
        cCloakingDevice::StaticCreateClass(), cGrenade::StaticCreateClass());

    const Fun_Runtime::cClass &cCloakingDevice::RetClass() const
    {
        return *ms_pcCloakingDeviceClass;
    }

    bool cCloakingDevice::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcCloakingDeviceClass->IsA(c);
    }

    // CD2 0x8260B4B0 has no derived cleanup beyond vtable restoration.
    cCloakingDevice::~cCloakingDevice()
    {
    }

    RWS::CAttributeHandler *cCloakingDevice::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cCloakingDevice;
        return 0;
    }

    const Fun_Runtime::cScriptTypeRegistration *cCloakingDevice::RetScriptTypeRegistration() const
    {
        return &cCloakingDeviceScriptRegistrar;
    }
}

// src/Equip/cEquipment.cpp
//
// Class: cEquipment (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cEquipment.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/cEquipment.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/cEquipment.cpp

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
#include "PHYSICS/cNetDynamicBody.h"
#include "rws/classfactory.h"
#include "Equip/cEquipment.h"
#include "cd2/memory.h"
#include "fun_runtime/script_type_registrar.h"

namespace Equip
{
    const Fun_Runtime::cClass *cEquipment::ms_pcEquipmentClass = &cEquipment::StaticCreateClass();

    Fun_Runtime::cClass &cEquipment::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cEquipmentClass = new Fun_Runtime::cClass(0x6, "cEquipment", 0x870);
        return *cEquipmentClass;
    }

    static RWS::CClassFactory::CRegistrar cEquipmentRegistrar(
        "cEquipment", cEquipment::MakeNew, 0x870, false);

    // CD2 0x82FCB1E8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cEquipmentcNetDynamicBodyInheritRegistrar(
        Equip::cEquipment::StaticCreateClass(), PHYSICS::cNetDynamicBody::StaticCreateClass());

    // CD2 0x82FCB2A0: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cEquipmentSpawningRegistrar(
        cEquipment::StaticCreateClass(), cEquipment::SpawnFromPrototype);

    RWS::CAttributeHandler *cEquipment::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cEquipmentPrototype(packet);
    }

    const char *cEquipment::RetClassName() const
    {
        return "cEquipment";
    }

    RWS::CAttributeHandler *cEquipment::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cEquipment;
        return 0;
    }

    // CD2 script-type registration; constructor/table evidence identifies the child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cEquipment> cEquipmentScriptRegistrar(
        "cEquipment", "cDynamicBody");

    const Fun_Runtime::cScriptTypeRegistration *cEquipment::RetScriptTypeRegistration() const
    {
        return &cEquipmentScriptRegistrar;
    }

    float cEquipment::cEquipmentPrototype::RetDroppedDeletionTime() const
    {
        return m_fDroppedDeletionTime;
    }

    bool cEquipment::cEquipmentPrototype::CanZoom() const
    {
        return m_bCanZoom && m_fMaxZoomFactor > 0.0f;
    }

    float cEquipment::cEquipmentPrototype::RetMaxZoomFactor() const
    {
        return m_fMaxZoomFactor;
    }

    float cEquipment::cEquipmentPrototype::RetZoomSpeed() const
    {
        return m_fZoomSpeed;
    }

    int cEquipment::cEquipmentPrototype::RetInInvPickupVFXID() const
    {
        return m_nInInvPickupId;
    }

    int cEquipment::cEquipmentPrototype::RetNotInInvPickupVFXID() const
    {
        return m_nNotInInvPickupId;
    }

    bool cEquipment::cEquipmentPrototype::RetLoadedCmdSpawn() const
    {
        return m_bLoadedCmdSpawn;
    }
}

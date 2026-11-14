// src/CHARACTER/cCharacterInterface.cpp
//
// Class: CHARACTER::cCharacterInterface. Script setters and registration are reconstructed below.
// The address range and ownership evidence are in config/splits.txt; RuffKing's object is cCharacterInterface.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Character/cCharacterInterface.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/CHARACTER/cCharacterInterface.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/script_type_registrar.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "CHARACTER/cCharacterInterface.h"
#include "CHARACTER/cLODLevelScriptRegistration.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include <new>

Fun_Runtime::cScriptTypeRegistrar<CHARACTER::cCharacterInterface> g_cCharacterInterface("cCharacterInterface", "cNonGameBase");     // global at 0x838241E0

namespace CHARACTER
{
    const Fun_Runtime::cClass *cCharacterInterface::ms_pcCharacterInterfaceClass =
        &cCharacterInterface::StaticCreateClass();

    cCharacterInterface::cCharacterInterface()
        : m_pCharacter(0)
    {
        // m_pCharacter(0): CD2 stores the null payload before the typed pointer's vptr, as the converting constructor
        // does (the default one leaves the vptr first). CD2 reloads CONST_FLOAT_0 for each timestamp; the centre
        // vector uses literal zero instead.
        m_fLastFootStepSoundTime = Fun_Runtime::g_GlobalConstants.CONST_FLOAT_0;
        m_fLastVocalSoundTime = Fun_Runtime::g_GlobalConstants.CONST_FLOAT_0;
        m_fLastBulletSoundTime = Fun_Runtime::g_GlobalConstants.CONST_FLOAT_0;
        m_bInitialState = false;
        m_bCanShareVehicleWithPlayer = false;
        m_bCanBePickedUpWhenAlive = false;
        m_bAlive = true;
    }

    cCharacterInterface::~cCharacterInterface()
    {
    }

    Fun_Runtime::cClass &cCharacterInterface::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cCharacterInterfaceClass =
            new Fun_Runtime::cClass(0x5ED, "cCharacterInterface", 0xC0);
        return *cCharacterInterfaceClass;
    }

    const Fun_Runtime::cClass &cCharacterInterface::RetClass() const
    {
        return *ms_pcCharacterInterfaceClass;
    }

    RWS::CAttributeHandler *cCharacterInterface::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cCharacterInterfacePrototype(packet);
    }

    RWS::CAttributeHandler *cCharacterInterface::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cCharacterInterface;
        return 0;
    }

    const Fun_Runtime::cScriptTypeRegistration *cCharacterInterface::RetScriptTypeRegistration() const
    {
        return &g_cCharacterInterface;
    }

    const char *cLODLevelScriptRegistration::RetName() const
    {
        return "eLODLevel";
    }

    unsigned char cCharacterInterface::RetLODLevel() const
    {
        return RetCharacter()->RetLODLevel();
    }

    bool cCharacterInterface::RetIsOnFire() const
    {
        return RetCharacter()->RetIsOnFire();
    }

    cGameBase *cCharacterInterface::RetVehicleTarget()
    {
        return RetCharacter()->RetTargeting()->RetVehicleTarget();
    }

    Equip::cEquipment *cCharacterInterface::RetEquipmentOfType(unsigned int type)
    {
        return RetCharacter()->RetEquipmentOfType(type);
    }

    Equip::cEquipment *cCharacterInterface::RetRealCurrentPrimaryEquipment()
    {
        return RetCharacter()->RetRealCurrentPrimaryEquipment();
    }

    Equip::cEquipment *cCharacterInterface::AddDefaultEquipmentByName(const char *sProtoName, bool bAutoEquip)
    {
        return AddEquipment(sProtoName, bAutoEquip, false, 0, false);
    }

    bool cCharacterInterface::IsEquipmentTypeInInventory(unsigned int type)
    {
        return RetCharacter()->RetEquipmentOfType(type) != 0;
    }

    const char *cCharacterInterface::RetClassName() const
    {
        return "cCharacterInterface";
    }

    void cCharacterInterface::SetCanShareVehicleWithPlayer(bool enabled)
    {
        m_bCanShareVehicleWithPlayer = enabled;
    }

    void cCharacterInterface::SetCanBePickedUpWhenAlive(bool enabled)
    {
        m_bCanBePickedUpWhenAlive = enabled;
    }

    bool cCharacterInterface::ForceOutOfVehicle()
    {
        return RetCharacter()->RetActionManager().ForceOutOfVehicle();
    }

    static RWS::CClassFactory::CRegistrar cCharacterInterfaceRegistrar(
        "cCharacterInterface", cCharacterInterface::MakeNew, 0xC0, false);

    // CD2 0x82FADC18: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cCharacterInterfacecNonGameBaseInheritRegistrar(
        CHARACTER::cCharacterInterface::StaticCreateClass(), cNonGameBase::StaticCreateClass());

    // CD2 0x82FADCD0: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cCharacterInterfaceSpawningRegistrar(
        cCharacterInterface::StaticCreateClass(), cCharacterInterface::SpawnFromPrototype);
    // CD2 0x82FADD70 registers enum object 0x83824204 with table 0x82113E60.
    static cLODLevelScriptRegistration g_cLODLevelScriptRegistration;

}

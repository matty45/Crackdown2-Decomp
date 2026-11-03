#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
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

#include "CHARACTER/cCharacterInterface.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

#include <new>

unsigned char g_cCharacterInterface;     // global at 0x838241E0

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

    bool cCharacterInterface::RetIsOnFire() const
    {
        return RetCharacter()->RetIsOnFire();
    }

    void *cCharacterInterface::GetPtrcCharacterInterface() const
    {
        return &g_cCharacterInterface;
    }

    const char *cCharacterInterface::GetPtrELODLevel() const
    {
        return "eLODLevel";
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

    static RWS::CClassFactory::CRegistrar cCharacterInterfaceRegistrar(
        "cCharacterInterface", cCharacterInterface::MakeNew, 0xC0, false);
}


// CD2 0x82FADC18: runtime class inheritance registration.
namespace CHARACTER
{
    static Fun_Runtime::cInheritanceRegistrar cCharacterInterfacecNonGameBaseInheritRegistrar(
        CHARACTER::cCharacterInterface::StaticCreateClass(), cNonGameBase::StaticCreateClass());
}

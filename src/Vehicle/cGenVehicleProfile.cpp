// src/Vehicle/cGenVehicleProfile.cpp
//
// Class: cGenVehicleProfile (namespace: Vehicle). Set up automatically: no function is matched yet. The address range
// and the evidence for it are in config/splits.txt; RuffKing's object for it is cGenVehicleProfile.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Vehicle/cGenVehicleProfile.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Vehicle/cGenVehicleProfile.cpp

#include "rws/classfactory.h"
#include "Vehicle/cGenVehicleProfile.h"
#include "fun_runtime/inheritance_registrar.h"
#include "cd2/memory.h"

namespace Vehicle
{
    int cGenVehicleProfile::m_aVehicleVFX[26];
    float cGenVehicleProfile::m_fAICharacterDamageThreshold[12];
    float cGenVehicleProfile::m_fPlayerCharacterDamageThreshold[12];
    float cGenVehicleProfile::m_fAICharacterDamageModifier[12];
    float cGenVehicleProfile::m_fPlayerCharacterDamageModifier[12];
    float cGenVehicleProfile::m_fAIGearChangeRatio = 0.6f;

    cGenVehicleProfile::cGenVehicleProfile()
    {
        for (int i = 0; i < 26; ++i)
            m_aVehicleVFX[i] = -1;
        for (int i = 0; i < 12; ++i)
            m_fAICharacterDamageThreshold[i] = 0.0f;
        for (int i = 0; i < 12; ++i)
            m_fPlayerCharacterDamageThreshold[i] = 0.0f;
        for (int i = 0; i < 12; ++i)
            m_fAICharacterDamageModifier[i] = 0.0f;
        for (int i = 0; i < 12; ++i)
            m_fPlayerCharacterDamageModifier[i] = 0.0f;
        m_fAIGearChangeRatio = 0.6f;
    }

    bool cGenVehicleProfile::IsA(const Fun_Runtime::cClass &testClass) const
    {
        return ms_pcGenVehicleProfileClass->IsA(testClass);
    }

    const char *cGenVehicleProfile::RetClassName() const
    {
        return "cGenVehicleProfile";
    }

    Fun_Runtime::cClass &cGenVehicleProfile::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cGenVehicleProfileClass = new Fun_Runtime::cClass(0x707, "cGenVehicleProfile", 0x7C);
        return *cGenVehicleProfileClass;
    }

    const Fun_Runtime::cClass *cGenVehicleProfile::ms_pcGenVehicleProfileClass = &cGenVehicleProfile::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cGenVehicleProfilecNonGameBaseInheritRegistrar(
        cGenVehicleProfile::StaticCreateClass(), cNonGameBase::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cGenVehicleProfileRegistrar(
        "cGenVehicleProfile", cGenVehicleProfile::MakeNew, 0x7c, false);

    const Fun_Runtime::cClass &cGenVehicleProfile::RetClass() const
    {
        return *ms_pcGenVehicleProfileClass;
    }

    RWS::CAttributeHandler *cGenVehicleProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cGenVehicleProfile;
    }
}

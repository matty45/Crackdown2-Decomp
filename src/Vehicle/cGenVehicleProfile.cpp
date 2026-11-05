#include "rws/classfactory.h"
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

#include "Vehicle/cGenVehicleProfile.h"

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
}

namespace Vehicle
{
    bool cGenVehicleProfile::IsA(const Fun_Runtime::cClass &testClass) const
    {
        return ms_pccGenVehicleProfileClass->IsA(testClass);
    }
}

namespace Vehicle
{
    const char *cGenVehicleProfile::RetClassName() const
    {
        return "cGenVehicleProfile";
    }
}

namespace Vehicle
{
    static RWS::CClassFactory::CRegistrar cGenVehicleProfileRegistrar(
        "cGenVehicleProfile", cGenVehicleProfile::MakeNew, 0x7c, false);
}

namespace Vehicle
{
    const Fun_Runtime::cClass &cGenVehicleProfile::RetClass() const
    {
        return *ms_pccGenVehicleProfileClass;
    }
}

#include "cd2/memory.h"

namespace Vehicle
{
    RWS::CAttributeHandler *cGenVehicleProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cGenVehicleProfile;
    }
}

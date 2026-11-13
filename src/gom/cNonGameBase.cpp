// Script registrar source ownership: CD2 initializer 0x82FD6D78 names cNonGameBase,
// and cleanup 0x8303FDA0 destroys the same descriptor. Shared interface names are ours.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/non_game_base.h"
#include "fun_runtime/script_type_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "rws/classfactory.h"
#include "gom/proto_registrar.h"
#include "cd2/memory.h"
#include "gom/cGameImportanceScriptRegistration.h"

    const char *cGameImportanceScriptRegistration::RetName() const
    {
        return "eGameImportance";
    }

    const char *cNonGameBase::RetProtoTypeName() const
    {
        if (m_pPrototype)
            return m_pPrototype->m_pName;
        return RetClassName();
    }

    Fun_Runtime::Vec3 cNonGameBase::RetCentre() const
    {
        return RetPosition();
    }

    Fun_Runtime::cClass &cNonGameBase::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x3EE, "cNonGameBase", 0x7C);
        return *descriptor;
    }

    const Fun_Runtime::cClass *cNonGameBase::ms_pcNonGameBaseClass = &cNonGameBase::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cNonGameBasecScriptHostInheritRegistrar(
        cNonGameBase::StaticCreateClass(), Fun_Runtime::cScriptHost::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cNonGameBaseRegistrar(
        "cNonGameBase", cNonGameBase::MakeNew, 0x7C, false);

    static GOM::cProtoRegistrar cNonGameBaseSpawningRegistrar(
        cNonGameBase::StaticCreateClass(), cNonGameBase::SpawnFromPrototype);

    static Fun_Runtime::cScriptTypeRegistrar<cNonGameBase> cNonGameBaseScriptRegistrar(
        "cNonGameBase", "cScriptHost");

    const Fun_Runtime::cClass &cNonGameBase::RetClass() const
    {
        return *ms_pcNonGameBaseClass;
    }

    Fun_Runtime::Vec3 cNonGameBase::RetPosition() const
    {
        return RetScriptPosition();
    }

    // CD2 0x82FD6DD0: enum object at 0x8383ABB4, table 0x8212CF1C.
    static cGameImportanceScriptRegistration g_cGameImportanceScriptRegistration;

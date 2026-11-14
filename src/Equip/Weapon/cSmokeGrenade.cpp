// src/Equip/Weapon/cSmokeGrenade.cpp
//
// Class: cSmokeGrenade (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cSmokeGrenade.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Weapon/cSmokeGrenade.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Weapon/cSmokeGrenade.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "fun_runtime/retval.h"
#include "fun_runtime/quat.h"
#include "Equip/cGrenade.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/proto_registrar.h"
#include "rws/classfactory.h"
#include "Equip/cSmokeGrenade.h"
#include "cd2/memory.h"
#include "rw/rwmem.h"
#include "VFX/cParticleEffectManager.h"

namespace Equip
{
    const Fun_Runtime::cClass *cSmokeGrenade::ms_pcSmokeGrenadeClass = &cSmokeGrenade::StaticCreateClass();

    Fun_Runtime::cClass &cSmokeGrenade::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSmokeGrenadeClass = new Fun_Runtime::cClass(0x3E8D, "cSmokeGrenade", 0x9D0);
        return *cSmokeGrenadeClass;
    }

    static RWS::CClassFactory::CRegistrar cSmokeGrenadeRegistrar(
        "cSmokeGrenade", cSmokeGrenade::MakeNew, 0x9D0, false);

    // CD2 0x82FD0C70: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cSmokeGrenadeSpawningRegistrar(
        cSmokeGrenade::StaticCreateClass(), cSmokeGrenade::SpawnFromPrototype);

    // CD2 0x82FD0BB8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cSmokeGrenadecGrenadeInheritRegistrar(
        Equip::cSmokeGrenade::StaticCreateClass(), Equip::cGrenade::StaticCreateClass());

    RWS::CAttributeHandler *cSmokeGrenade::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cSmokeGrenadePrototype(packet);
    }

    const char *cSmokeGrenade::RetClassName() const
    {
        return "cSmokeGrenade";
    }

    const Fun_Runtime::cClass &cSmokeGrenade::RetClass() const
    {
        return *ms_pcSmokeGrenadeClass;
    }

    bool cSmokeGrenade::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcSmokeGrenadeClass->IsA(c);
    }

    RWS::CAttributeHandler *cSmokeGrenade::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cSmokeGrenade;
        return 0;
    }

    void cSmokeGrenade::cSmokeGrenadePrototype::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cGrenadePrototype::HandleAttributes(packet);
        for (RWS::CAttributeCommandIterator it(packet, "cSmokeGrenade"); !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case 0:
                {
                    float duration = it->GetAs_float();
                    RwMemNative32(&duration, sizeof(duration));
                    m_nMaxSmokeTime_msec = static_cast<int>(duration * 1000.0f);
                }
                break;
            case 1:
                m_nSmokeEffectID = VFX::g_pParticleEffectManager->RetEffectId(it->GetAs_char_ptr());
                break;
            }
        }
    }

    Fun_Runtime::RetVal cSmokeGrenade::cSmokeGrenadePrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}

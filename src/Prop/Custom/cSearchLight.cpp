// The shared cProp hierarchy now reproduces the inherited vptr stores exactly.
// src/Prop/Custom/cSearchLight.cpp
//
// Class: cSearchLight (namespace: Prop). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cSearchLight.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Props/Custom/cSearchLight.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Prop/Custom/cSearchLight.cpp

#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cProp.h"
#include "rws/classfactory.h"
#include "Prop/cSearchLight.h"
#include <new>
#include "rw/rwmem.h"
#include "cd2/memory.h"

namespace Prop
{
    void cSearchLight::cSearchLightPrototype::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cPropPrototype::HandleAttributes(packet);
        for (RWS::CAttributeCommandIterator it(packet, "cSearchLight"); !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case 0:
                { float value = it->GetAs_float(); RwMemNative32(&value, 4); m_fMaxRotX = value; }
                break;
            case 1:
                { float value = it->GetAs_float(); RwMemNative32(&value, 4); m_fMaxRotY = value; }
                break;
            case 2:
                { float value = it->GetAs_float(); RwMemNative32(&value, 4); m_fDegreesPerSecondX = value; }
                break;
            case 3:
                { float value = it->GetAs_float(); RwMemNative32(&value, 4); m_fDegreesPerSecondY = value; }
                break;
            }
        }
    }

    RWS::CAttributeHandler *cSearchLight::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cSearchLightPrototype(packet);
    }

    Fun_Runtime::RetVal cSearchLight::cSearchLightPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    // CD2 has no derived cleanup here; cProp's secondary bases remain incomplete in the stand-in.
    cSearchLight::~cSearchLight()
    {
    }

    const char *cSearchLight::RetClassName() const
    {
        return "cSearchLight";
    }

    Fun_Runtime::cClass &cSearchLight::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSearchLightClass = new Fun_Runtime::cClass(0x2704, "cSearchLight", 0xE70);
        return *cSearchLightClass;
    }

    const Fun_Runtime::cClass *cSearchLight::ms_pcSearchLightClass = &cSearchLight::StaticCreateClass();

    const Fun_Runtime::cClass &cSearchLight::RetClass() const
    {
        return *ms_pcSearchLightClass;
    }

    bool cSearchLight::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcSearchLightClass->IsA(c);
    }

    static RWS::CClassFactory::CRegistrar cSearchLightRegistrar(
        "cSearchLight", cSearchLight::MakeNew, 0xE70, false);

    RWS::CAttributeHandler *cSearchLight::SpawnFromPrototype(GOM::cObjectPrototype *prototype, void *memory)
    {
        if (memory)
            return new (memory) cSearchLight(prototype);
        return 0;
    }

    // CD2 0x82FFB948: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cSearchLightcPropInheritRegistrar(
        Prop::cSearchLight::StaticCreateClass(), Prop::cProp::StaticCreateClass());

    // CD2 0x82FFBA00: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cSearchLightSpawningRegistrar(
        cSearchLight::StaticCreateClass(), cSearchLight::SpawnFromPrototype);
}

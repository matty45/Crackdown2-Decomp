#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cProp.h"
#include "rws/classfactory.h"
// src/Prop/Custom/cTurretBase.cpp
//
// Class: cTurretBase (namespace: Prop). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cTurretBase.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Props/Custom/cTurretBase.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Prop/Custom/cTurretBase.cpp

#include "Prop/cTurretBase.h"
#include <new>
#include "rw/rwmem.h"

namespace Prop
{
    void cTurretBase::cTurretBasePrototype::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cPropPrototype::HandleAttributes(packet);
        for (RWS::CAttributeCommandIterator it(packet, "cTurretBase"); !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case 0:
                { float value = it->GetAs_float(); RwMemNative32(&value, 4); m_fTurretRotAccel = value; }
                break;
            case 1:
                { float value = it->GetAs_float(); RwMemNative32(&value, 4); m_fGunRotAccel = value; }
                break;
            case 2:
                { float value = it->GetAs_float(); RwMemNative32(&value, 4); m_fTurretRotSpeed = value; }
                break;
            case 3:
                { float value = it->GetAs_float(); RwMemNative32(&value, 4); m_fGunRotSpeed = value; }
                break;
            }
        }
    }

    RWS::CAttributeHandler *cTurretBase::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cTurretBasePrototype(packet);
    }

    Fun_Runtime::RetVal cTurretBase::cTurretBasePrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    // CD2 0x827485B0 unregisters type 0x19, then member destruction unlinks the safe pointers.
    // cProp's inherited secondary base layout is still incomplete.
    cTurretBase::~cTurretBase()
    {
        RemoveObjectTypeRegistration(0x19, this);
    }

    const char *cTurretBase::RetClassName() const
    {
        return "cTurretBase";
    }
}

#include "cd2/memory.h"

namespace Prop
{
    Fun_Runtime::cClass &cTurretBase::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTurretBaseClass = new Fun_Runtime::cClass(0x1027, "cTurretBase", 0x1080);
        return *cTurretBaseClass;
    }
}

namespace Prop
{
    const Fun_Runtime::cClass *cTurretBase::ms_pcTurretBaseClass = &cTurretBase::StaticCreateClass();

    const Fun_Runtime::cClass &cTurretBase::RetClass() const
    {
        return *ms_pcTurretBaseClass;
    }
}

namespace Prop
{
    bool cTurretBase::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcTurretBaseClass->IsA(c);
    }
}

namespace Prop
{
    static RWS::CClassFactory::CRegistrar cTurretBaseRegistrar(
        "cTurretBase", cTurretBase::MakeNew, 0x1080, false);
}

namespace Prop
{
    RWS::CAttributeHandler *cTurretBase::SpawnFromPrototype(GOM::cObjectPrototype *prototype, void *memory)
    {
        if (memory)
            return new (memory) cTurretBase(prototype);
        return 0;
    }
}

// CD2 0x82FFC728: runtime class inheritance registration.
namespace Prop
{
    static Fun_Runtime::cInheritanceRegistrar cTurretBasecPropInheritRegistrar(
        Prop::cTurretBase::StaticCreateClass(), Prop::cProp::StaticCreateClass());
}

// CD2 0x82FFC7E0: register the class descriptor and placement factory.
namespace Prop
{
    static GOM::cProtoRegistrar cTurretBaseSpawningRegistrar(
        cTurretBase::StaticCreateClass(), cTurretBase::SpawnFromPrototype);
}

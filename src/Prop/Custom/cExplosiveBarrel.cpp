// src/Prop/Custom/cExplosiveBarrel.cpp
//
// Class: cExplosiveBarrel (namespace: Prop). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cExplosiveBarrel.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Props/Custom/cExplosiveBarrel.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Prop/Custom/cExplosiveBarrel.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "gom/proto_registrar.h"
#include "rws/classfactory.h"
#include "Prop/cExplosiveBarrel.h"
#include "Prop/cExplosiveBarrelPrototype.h"
#include "rw/rwmem.h"
#include <new>
#include "fun_runtime/inheritance_registrar.h"
#include "cd2/memory.h"

namespace Prop
{
    RWS::CAttributeHandler *cExplosiveBarrel::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cExplosiveBarrelPrototype(packet);
    }

    Fun_Runtime::RetVal cExplosiveBarrelPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    void cExplosiveBarrelPrototype::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cPropPrototype::HandleAttributes(packet);
        for (RWS::CAttributeCommandIterator it(packet, "cExplosiveBarrel"); !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case 1:
                {
                    float seconds = it->GetAs_float();
                    RwMemNative32(&seconds, 4);
                    unsigned int milliseconds = (unsigned int)(seconds * 1000.0f);
                    if (milliseconds <= 1)
                        milliseconds = 1;
                    m_nBarrelFadeDuration = milliseconds;
                }
                break;
            case 0:
                {
                    float seconds = it->GetAs_float();
                    RwMemNative32(&seconds, 4);
                    unsigned int milliseconds = (unsigned int)(seconds * 1000.0f);
                    if (milliseconds <= 1)
                        milliseconds = 1;
                    m_nBarrelDeleteDelay = milliseconds;
                }
                break;
            }
        }
    }

    const char *cExplosiveBarrel::RetClassName() const
    {
        return "cExplosiveBarrel";
    }

    Fun_Runtime::cClass &cExplosiveBarrel::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cExplosiveBarrelClass = new Fun_Runtime::cClass(0xD434, "cExplosiveBarrel", 0xE40);
        return *cExplosiveBarrelClass;
    }

    const Fun_Runtime::cClass *cExplosiveBarrel::ms_pcExplosiveBarrelClass = &cExplosiveBarrel::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cExplosiveBarrelcPropInheritRegistrar(
        cExplosiveBarrel::StaticCreateClass(), cProp::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cExplosiveBarrelRegistrar(
        "cExplosiveBarrel", cExplosiveBarrel::MakeNew, 0xe40, false);

    // CD2 0x82FFA918: class descriptor and placement factory.
    static GOM::cProtoRegistrar cExplosiveBarrelSpawningRegistrar(
        cExplosiveBarrel::StaticCreateClass(), cExplosiveBarrel::SpawnFromPrototype);

    const Fun_Runtime::cClass &cExplosiveBarrel::RetClass() const
    {
        return *ms_pcExplosiveBarrelClass;
    }

    bool cExplosiveBarrel::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcExplosiveBarrelClass->IsA(c);
    }

    RWS::CAttributeHandler *cExplosiveBarrel::SpawnFromPrototype(GOM::cObjectPrototype *pPrototype, void *memory)
    {
        if (memory)
            return new (memory) cExplosiveBarrel(pPrototype);
        return 0;
    }
}

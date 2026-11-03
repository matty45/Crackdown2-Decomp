#include "rws/classfactory.h"
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

#include "Prop/cExplosiveBarrel.h"
#include "Prop/cExplosiveBarrelPrototype.h"
#include "rw/rwmem.h"
#include <new>

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
}

namespace Prop
{
    static RWS::CClassFactory::CRegistrar cExplosiveBarrelRegistrar(
        "cExplosiveBarrel", cExplosiveBarrel::MakeNew, 0xe40, false);
}

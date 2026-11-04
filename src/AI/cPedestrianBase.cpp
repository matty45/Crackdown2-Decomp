#include "fun_runtime/inheritance_registrar.h"
#include "AI/NPCBehaviour.h"
#include "AI/cPedestrianBase.h"
#include "rws/classfactory.h"
#include "AI/BehaviourClassID.h"
#include "cd2/memory.h"

#include <new>

namespace AI
{
    Fun_Runtime::cClass &cPedestrianBase::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPedestrianBaseClass =
            new Fun_Runtime::cClass(g_nBehaviourClassID++, "cPedestrianBase", 0x120);
        return *cPedestrianBaseClass;
    }

    const Fun_Runtime::cClass *cPedestrianBase::ms_pcPedestrianBaseClass = 0;
    const float cPedestrianBase::m_fReactTimer = 8.0f;

    RWS::CAttributeHandler *cPedestrianBase::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cPedestrianBase;
        return 0;
    }

    cPedestrianBase::cPedestrianBase()
        : m_nState(eNull), m_nReactFinState(eFleeing), m_nUnknownE4(0), m_nUnknownE8(0), m_nUnknownEC(0),
          m_vReactionPoint(Fun_Runtime::ZeroVec), m_vVelocity(Fun_Runtime::ZeroVec),
          m_nInitialEdge(0xFFFFFFFF), m_nStoredCollisionFilterInfo(0), m_fCurrentTimer(m_fReactTimer),
          m_bPanicRun(false), m_bAmbEventHasObject(false), m_bDoReactions(true)
    {
    }

    const Fun_Runtime::cClass &cPedestrianBase::RetClass() const
    {
        return *ms_pcPedestrianBaseClass;
    }

    bool cPedestrianBase::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcPedestrianBaseClass->IsA(c);
    }

    const char *cPedestrianBase::RetClassName() const
    {
        return "cPedestrianBase";
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cPedestrianBaseRegistrar(
        "cPedestrianBase", cPedestrianBase::MakeNew, 0x120, false);
}

// CD2 0x82F929B0: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar cPedestrianBaseNPCBehaviourInheritRegistrar(
        AI::cPedestrianBase::StaticCreateClass(), AI::NPCBehaviour::StaticCreateClass());
}

#include "gom/proto_registrar.h"

// CD2 0x82F92A68: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace AI
{
    static GOM::cProtoRegistrar cPedestrianBaseSpawningRegistrar(
        cPedestrianBase::StaticCreateClass(), cPedestrianBase::SpawnFromPrototype);
}

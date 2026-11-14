// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/NPCArmedBehaviour.h"
#include "AI/CellMinigun.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    const Fun_Runtime::cClass *CellMinigun::ms_pCellMinigunClass = &CellMinigun::StaticCreateClass();

    const Fun_Runtime::cClass &CellMinigun::RetClass() const
    {
        return *ms_pCellMinigunClass;
    }

    const char *CellMinigun::RetClassName() const
    {
        return "CellMinigun";
    }

    // CD2 0x824C3228: placement factory; NPCArmedBehaviour's constructor stays out of line, the rest is inlined.
    RWS::CAttributeHandler *CellMinigun::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) CellMinigun;
        return 0;
    }

    bool CellMinigun::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pCellMinigunClass->IsA(c);
    }

    RWS::CAttributeHandler *CellMinigun::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new CellMinigun();
    }

    void CellMinigun::ChangeMainState(eState state)
    {
        if (m_nMainState != state)
        {
            m_nMainState = state;
            OnEnterState(state);
        }
    }

    static RWS::CClassFactory::CRegistrar CellMinigunRegistrar(
        "CellMinigun", CellMinigun::MakeNew, 0x100, false);

    Fun_Runtime::cClass &CellMinigun::StaticCreateClass()
    {
        static Fun_Runtime::cClass *CellMinigunClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "CellMinigun", 0x100);
        return *CellMinigunClass;
    }

    // CD2 0x82F95F08: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar CellMinigunNPCArmedBehaviourInheritRegistrar(
        AI::CellMinigun::StaticCreateClass(), AI::NPCArmedBehaviour::StaticCreateClass());

    // CD2 0x82F95FC0: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar CellMinigunSpawningRegistrar(
        CellMinigun::StaticCreateClass(), CellMinigun::SpawnFromPrototype);
}

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "GameManagement/cFinalMissionBarrier.h"
#include "cd2/memory.h"

namespace GameManagement
{
    RWS::CAttributeHandler *cFinalMissionBarrier::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cFinalMissionBarrier;
    }

    const char *cFinalMissionBarrier::RetClassName() const
    {
        return "cFinalMissionBarrier";
    }

    void cFinalMissionBarrier::Create()
    {
        if (m_pBarrier && !m_pBarrier->IsEnabled())
        {
            m_pBarrier->SetMesh(GetBarrierMesh(), m_mXForm, GetBarrierSettings());
            m_pBarrier->EnableKillzone(false);
        }
    }

    static RWS::CClassFactory::CRegistrar cFinalMissionBarrierRegistrar(
        "cFinalMissionBarrier", cFinalMissionBarrier::MakeNew, 0x80, false);
}

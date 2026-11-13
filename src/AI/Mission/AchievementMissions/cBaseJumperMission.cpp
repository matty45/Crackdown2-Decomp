// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "AI/cBaseJumperMission.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cBaseJumperMission::ms_pcBaseJumperMissionClass = &cBaseJumperMission::StaticCreateClass();

    // The running mission (CD2 0x838009C0; the name is ours). Only the constructor and destructor touch it, and CD2
    // schedules both stores freely around the member accesses, as the compiler does for a variable whose address
    // nothing else can see: an external variable keeps them in source order.
    static cBaseJumperMission *s_pInstance;

    // __forceinline: CD2 expands both into their callers, MakeNew (passing no packet) and the deleting destructor; as
    // with cBeaconProp's, ordinary inline leaves the destructor a separate call.
    __forceinline cBaseJumperMission::cBaseJumperMission()
        : m_eBJState(eBJState_Inactive), m_vFallStartPos(Fun_Runtime::ZeroVec), m_fFallDist(0.0f)
    {
        s_pInstance = this;
    }

    __forceinline cBaseJumperMission::~cBaseJumperMission()
    {
        s_pInstance = 0;
    }

    const Fun_Runtime::cClass &cBaseJumperMission::RetClass() const
    {
        return *ms_pcBaseJumperMissionClass;
    }

    const char *cBaseJumperMission::RetClassName() const
    {
        return "cBaseJumperMission";
    }

    bool cBaseJumperMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcBaseJumperMissionClass->IsA(c);
    }

    RWS::CAttributeHandler *cBaseJumperMission::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cBaseJumperMission;
    }
}

static RWS::CClassFactory::CRegistrar cBaseJumperMissionRegistrar(
    "cBaseJumperMission", AI::cBaseJumperMission::MakeNew, 0x400, false);

// PHYSICS/cPickup.cpp: RuffKing's Libraries/Shared/Physics/cPickup.cpp.
// Its text range and the evidence for it are in config/splits.txt; its own functions are not written yet.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "PHYSICS/cPickupBase.h"
#include "PHYSICS/cPickup.h"
#include "cd2/memory.h"

namespace PHYSICS
{
    // CD2 initializer 0x82FF0698 stores the descriptor used by RetClass at 0x83849530.
    const Fun_Runtime::cClass *cPickup::ms_pcPickupClass = &cPickup::StaticCreateClass();

    RWS::CAttributeHandler *cPickupBase::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cPickupBase;
    }

    const char *cPickupBase::RetClassName() const
    {
        return "cPickupBase";
    }

    Fun_Runtime::Vec3 cPickupBase::RetScriptPosition() const
    {
        return Fun_Runtime::Vec3(m_Position.x, m_Position.y, m_Position.z);
    }

    const Fun_Runtime::cClass &cPickup::RetClass() const
    {
        return *ms_pcPickupClass;
    }

    const char *cPickup::RetClassName() const
    {
        return "cPickup";
    }

    Fun_Runtime::cClass &cPickupBase::StaticCreateClass()
    {
        static Fun_Runtime::cClass *pickupBaseClass = new Fun_Runtime::cClass(0x113, "cPickupBase", 0x150);
        return *pickupBaseClass;
    }

    Fun_Runtime::cClass &cPickup::StaticCreateClass()
    {
        static Fun_Runtime::cClass *pickupClass = new Fun_Runtime::cClass(0x114, "cPickup", 0x150);
        return *pickupClass;
    }
}

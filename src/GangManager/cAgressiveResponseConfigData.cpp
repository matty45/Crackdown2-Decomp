// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "GangManager/cAgressiveResponseConfigData.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace GangManager
{
    // CD2 0x8266F888 (not matched): CD2 also inlines cSafeDeletable's constructor and keeps the object in r3; as in
    // cFactionConfigData::MakeNew, a local inline constructor gives 49% with the object held in r31.
    RWS::CAttributeHandler *cAgressiveResponseConfigData::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cAgressiveResponseConfigData(packet);
    }

    const char *cAgressiveResponseConfigData::RetClassName() const
    {
        return "cAgressiveResponseConfigData";
    }

    cAgressiveResponseConfigData::~cAgressiveResponseConfigData()
    {
    }

    static RWS::CClassFactory::CRegistrar cAgressiveResponseConfigDataRegistrar(
        "cAgressiveResponseConfigData", cAgressiveResponseConfigData::MakeNew, 0x60, false);
}

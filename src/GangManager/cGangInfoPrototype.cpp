// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "GangManager/cGangInfoPrototype.h"
#include "GangManager/cGangInfo.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace GangManager
{
    // CD2 0x82676D60: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cGangInfoPrototype::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cGangInfoPrototype;
    }

    const char *cGangInfoPrototype::RetClassName() const
    {
        return "cGangInfoPrototype";
    }

    const Fun_Runtime::cClass &cGangInfo::RetClass() const
    {
        return *ms_pcGangInfoClass;
    }

    static RWS::CClassFactory::CRegistrar cGangInfoPrototypeRegistrar(
        "cGangInfoPrototype", cGangInfoPrototype::MakeNew, 0xD0, false);

}

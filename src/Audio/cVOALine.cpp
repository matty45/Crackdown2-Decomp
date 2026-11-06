// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "Audio/cVOALine.h"
#include "rws/classfactory.h"

namespace Audio
{
    const Fun_Runtime::cClass *cVOALine::ms_pcVOALineClass = 0;

    cVOALine::cVOALine() {}

    const Fun_Runtime::cClass &cVOALine::RetClass() const
    {
        return *ms_pcVOALineClass;
    }

    const char *cVOALine::RetClassName() const
    {
        return "cVOALine";
    }

    bool cVOALine::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcVOALineClass->IsA(c);
    }

    RWS::CAttributeHandler *cVOALine::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cVOALine();
    }
}

static RWS::CClassFactory::CRegistrar cVOALineRegistrar(
    "cVOALine", Audio::cVOALine::MakeNew, 0xF0, false);

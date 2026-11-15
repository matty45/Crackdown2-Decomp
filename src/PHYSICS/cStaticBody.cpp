// PHYSICS/cStaticBody.cpp: RuffKing's Libraries/Shared/Physics/cStaticBody.cpp.
// Its text range and the evidence for it are in config/splits.txt; its own functions are not written yet.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "PHYSICS/cStaticBody.h"
#include "cd2/memory.h"

namespace PHYSICS
{
    RWS::CAttributeHandler *cStaticBody::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cStaticBody;
    }

    Fun_Runtime::cClass &cStaticBody::StaticCreateClass()
    {
        static Fun_Runtime::cClass *staticBodyClass = new Fun_Runtime::cClass(0x646, "cStaticBody", 0x260);
        return *staticBodyClass;
    }
}

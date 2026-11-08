// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "CHARACTER/cCwCharacter.h"
#include "rws/classfactory.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/proto_registrar.h"
#include "cd2/memory.h"

namespace CHARACTER
{
    const char *cCwCharacter::RetClassName() const
    {
        return "cCwCharacter";
    }

    const Fun_Runtime::cClass *cCwCharacter::ms_pcCwCharacterClass = &cCwCharacter::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cCwCharactercCharacterInheritRegistrar(
        cCwCharacter::StaticCreateClass(), cCharacter::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cCwCharacterRegistrar(
        "cCwCharacter", cCwCharacter::MakeNew, 0x2CE0, false);

    static GOM::cProtoRegistrar cCwCharacterSpawningRegistrar(
        cCwCharacter::StaticCreateClass(), cCwCharacter::SpawnFromPrototype);

    // CD2 0x8253F438: builds the prototype; its constructor stays out of line.
    RWS::CAttributeHandler *cCwCharacter::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cCwCharacterPrototype(packet);
    }

    Fun_Runtime::cClass &cCwCharacter::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cCwCharacterClass = new Fun_Runtime::cClass(0x6A2, "cCwCharacter", 0x2CE0);
        return *cCwCharacterClass;
    }
}

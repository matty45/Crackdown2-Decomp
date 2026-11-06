// src/cPrismaticTrigger.cpp
//
// Class: cPrismaticTrigger (namespace: unknown). Set up automatically: no function is matched yet. The address range
// and the evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cPrismaticTrigger.cpp

#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "unknown/cPhantomBody.h"
#include "rws/classfactory.h"
#include "unknown/cPrismaticTrigger.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass *cPrismaticTrigger::ms_pcPrismaticTriggerClass = &cPrismaticTrigger::StaticCreateClass();

    Fun_Runtime::cClass &cPrismaticTrigger::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPrismaticTriggerClass = new Fun_Runtime::cClass(0xCB57, "cPrismaticTrigger", 0x160);
        return *cPrismaticTriggerClass;
    }

    static RWS::CClassFactory::CRegistrar cPrismaticTriggerRegistrar(
        "cPrismaticTrigger", cPrismaticTrigger::MakeNew, 0x160, false);

    // CD2 0x82FF87D8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cPrismaticTriggercPhantomBodyInheritRegistrar(
        unknown::cPrismaticTrigger::StaticCreateClass(), unknown::cPhantomBody::StaticCreateClass());

    // CD2 0x82FF8890: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cPrismaticTriggerSpawningRegistrar(
        cPrismaticTrigger::StaticCreateClass(), cPrismaticTrigger::SpawnFromPrototype);

    RWS::CAttributeHandler *cPrismaticTrigger::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cPrismaticTriggerPrototype(packet);
    }

    const char *cPrismaticTrigger::RetClassName() const
    {
        return "cPrismaticTrigger";
    }

    const Fun_Runtime::cClass &cPrismaticTrigger::RetClass() const
    {
        return *ms_pcPrismaticTriggerClass;
    }
}

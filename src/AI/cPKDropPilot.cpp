#include "fun_runtime/inheritance_registrar.h"
#include "AI/cPilotBase.h"
#include "AI/cPKDropPilot.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cPKDropPilot::ms_pcPKDropPilotClass = &cPKDropPilot::StaticCreateClass();


    const Fun_Runtime::cClass &cPKDropPilot::RetClass() const
    {
        return *ms_pcPKDropPilotClass;
    }

    const char *cPKDropPilot::RetClassName() const
    {
        return "cPKDropPilot";
    }

    bool cPKDropPilot::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcPKDropPilotClass->IsA(c);
    }

    RWS::CAttributeHandler *cPKDropPilot::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cPKDropPilot();
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cPKDropPilotRegistrar(
        "cPKDropPilot", cPKDropPilot::MakeNew, 0x150, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &cPKDropPilot::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPKDropPilotClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "cPKDropPilot", 0x150);
        return *cPKDropPilotClass;
    }
}

// CD2 0x82F9C5F0: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar cPKDropPilotcPilotBaseInheritRegistrar(
        AI::cPKDropPilot::StaticCreateClass(), AI::cPilotBase::StaticCreateClass());
}

#include <new>

// CD2 0x824D4B88: placement factory; cPilotBase's constructor stays out of line, the rest is inlined.
namespace AI
{
    RWS::CAttributeHandler *cPKDropPilot::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cPKDropPilot;
        return 0;
    }
}

#include "gom/proto_registrar.h"

// CD2 0x82F9C6A8: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace AI
{
    static GOM::cProtoRegistrar cPKDropPilotSpawningRegistrar(
        cPKDropPilot::StaticCreateClass(), cPKDropPilot::SpawnFromPrototype);
}

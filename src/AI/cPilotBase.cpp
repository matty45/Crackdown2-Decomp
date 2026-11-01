#include "AI/cPilotBase.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cPilotBase::ms_pcPilotBaseClass = &cPilotBase::StaticCreateClass();

    cPilotBase::cPilotBase() {}

    const Fun_Runtime::cClass &cPilotBase::RetClass() const
    {
        return *ms_pcPilotBaseClass;
    }

    const char *cPilotBase::RetClassName() const
    {
        return "cPilotBase";
    }

    bool cPilotBase::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcPilotBaseClass->IsA(c);
    }

    RWS::CAttributeHandler *cPilotBase::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cPilotBase();
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cPilotBaseRegistrar(
        "cPilotBase", cPilotBase::MakeNew, 0x140, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &cPilotBase::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPilotBaseClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "cPilotBase", 0x140);
        return *cPilotBaseClass;
    }
}

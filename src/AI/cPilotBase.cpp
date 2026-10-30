#include "AI/cPilotBase.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cPilotBase::ms_pcPilotBaseClass = 0;

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

static RWS::CClassFactory::CRegistrar cPilotBaseRegistrar(
    "cPilotBase", AI::cPilotBase::MakeNew, 0x7C, false);

namespace AI
{
    static RWS::CClassFactory::CRegistrar cPilotBaseRegistrar(
        "cPilotBase", cPilotBase::MakeNew, 0x140, false);
}

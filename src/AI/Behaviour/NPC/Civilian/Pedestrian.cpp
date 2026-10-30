#include "AI/Pedestrian.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *Pedestrian::ms_pcPedestrianClass = 0;

    const Fun_Runtime::cClass &Pedestrian::RetClass() const
    {
        return *ms_pcPedestrianClass;
    }

    bool Pedestrian::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcPedestrianClass->IsA(c);
    }

    const char *Pedestrian::RetClassName() const
    {
        return "Pedestrian";
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar PedestrianRegistrar(
        "Pedestrian", Pedestrian::MakeNew, 0x120, false);
}

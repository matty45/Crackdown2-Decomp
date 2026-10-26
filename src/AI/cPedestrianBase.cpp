#include "AI/cPedestrianBase.h"

namespace AI
{
    const Fun_Runtime::cClass *cPedestrianBase::ms_pcPedestrianBaseClass = 0;

    const Fun_Runtime::cClass &cPedestrianBase::RetClass() const
    {
        return *ms_pcPedestrianBaseClass;
    }

    bool cPedestrianBase::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcPedestrianBaseClass->IsA(c);
    }

    const char *cPedestrianBase::RetClassName() const
    {
        return "cPedestrianBase";
    }
}

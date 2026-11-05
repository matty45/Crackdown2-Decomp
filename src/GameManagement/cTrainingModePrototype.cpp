#include "rws/classfactory.h"
#include "GameManagement/cTrainingModePrototype.h"

namespace GameManagement
{
    const char *cTrainingModePrototype::RetClassName() const
    {
        return "cTrainingModePrototype";
    }

    static RWS::CClassFactory::CRegistrar cTrainingModePrototypeRegistrar(
        "cTrainingModePrototype", cTrainingModePrototype::MakeNew, 0x110, false);
}

#include "rws/classfactory.h"
#include "Billboard/BillboardAudioEmitter.h"

namespace Billboard
{
    const char *BillboardAudioEmitter::RetClassName() const
    {
        return "BillboardAudioEmitter";
    }

    static RWS::CClassFactory::CRegistrar BillboardAudioEmitterRegistrar(
        "BillboardAudioEmitter", BillboardAudioEmitter::MakeNew, 0x70, false);
}

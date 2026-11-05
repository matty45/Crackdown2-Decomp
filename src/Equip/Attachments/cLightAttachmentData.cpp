#include "Equip/cLightAttachmentData.h"
#include "rws/classfactory.h"

namespace Equip
{
    const char *cLightAttachmentData::RetClassName() const
    {
        return "cLightAttachmentData";
    }

    static RWS::CClassFactory::CRegistrar cLightAttachmentDataRegistrar(
        "cLightAttachmentData", cLightAttachmentData::MakeNew, 0x38, false);
}

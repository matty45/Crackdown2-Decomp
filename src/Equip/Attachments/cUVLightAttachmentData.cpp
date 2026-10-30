#include "Equip/cUVLightAttachmentData.h"
#include "rws/classfactory.h"

namespace Equip
{
    const char *cUVLightAttachmentData::RetClassName() const
    {
        return "cUVLightAttachmentData";
    }
}

namespace Equip
{
    static RWS::CClassFactory::CRegistrar cUVLightAttachmentDataRegistrar(
        "cUVLightAttachmentData", cUVLightAttachmentData::MakeNew, 0x3C, false);
}

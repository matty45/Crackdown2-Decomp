#include "rws/attributes.h"
// unknown::cRenderToTextureManager (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x827A9B78) builds cClass(0xCBED, "cRenderToTextureManager", 0x98); 0x98 is the size its registrar gives.
#ifndef UNKNOWN_CRENDERTOTEXTUREMANAGER_H
#define UNKNOWN_CRENDERTOTEXTUREMANAGER_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cRenderToTextureManager
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcRenderToTextureManagerClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CRENDERTOTEXTUREMANAGER_H

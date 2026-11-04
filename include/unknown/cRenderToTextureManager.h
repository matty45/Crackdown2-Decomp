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
        // CD2 0x827A9AB0: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x827A9B68: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcRenderToTextureManagerClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CRENDERTOTEXTUREMANAGER_H

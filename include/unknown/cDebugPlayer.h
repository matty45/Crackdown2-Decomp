#include "rws/attributes.h"
// unknown::cDebugPlayer (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x827147F8) builds cClass(0x63D, "cDebugPlayer", 0x190); 0x190 is the size its registrar gives.
#ifndef UNKNOWN_CDEBUGPLAYER_H
#define UNKNOWN_CDEBUGPLAYER_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cDebugPlayer
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcDebugPlayerClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CDEBUGPLAYER_H

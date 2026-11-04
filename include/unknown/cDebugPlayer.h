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
        // CD2 0x82714668: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x82714720: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcDebugPlayerClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CDEBUGPLAYER_H

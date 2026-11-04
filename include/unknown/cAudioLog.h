#include "rws/attributes.h"
// unknown::cAudioLog (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8270ED30) builds cClass(0x115, "cAudioLog", 0x1A0); 0x1A0 is the size its registrar gives.
#ifndef UNKNOWN_CAUDIOLOG_H
#define UNKNOWN_CAUDIOLOG_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cAudioLog
    {
    public:
        // CD2 0x8270EB50: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x8270EC08: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcAudioLogClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CAUDIOLOG_H

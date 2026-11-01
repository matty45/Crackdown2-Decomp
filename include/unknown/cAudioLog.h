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
        static const Fun_Runtime::cClass *ms_pcAudioLogClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CAUDIOLOG_H

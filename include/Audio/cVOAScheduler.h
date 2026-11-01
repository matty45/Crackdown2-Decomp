// Audio::cVOAScheduler (Crackdown 2): STAND-IN for the class name only. Base RWS::CAttributeHandler, as in RuffKing's
// header; RetClassName (0x82836EA8) is slot 11 of the vtable at 0x8215A420, as cNonGameBase's RetClassName.
#ifndef AUDIO_CVOASCHEDULER_H
#define AUDIO_CVOASCHEDULER_H

#include "rws/attributes.h"

namespace Audio
{
    class cVOAScheduler : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif // AUDIO_CVOASCHEDULER_H

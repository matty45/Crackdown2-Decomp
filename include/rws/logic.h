// RWS main-loop messages (RuffKing's framework/mainloop/logic.cpp defines them in namespace RWS). CD2 registers
// iMsgRunningTick (0x83A05C54) as "iMsgRunningTick" with format "RwUInt32" in 0x82915E10.
#ifndef RWS_LOGIC_H
#define RWS_LOGIC_H

#include "rws/eventid.h"

namespace RWS
{
    extern CEventId iMsgRunningTick;
    // CD2 0x82915E10 registers these exact names at 0x83A05C5C / 0x83A05C84.
    extern CEventId iMsgRunningPostTick;
    extern CEventId iMsgPausedPostTick;
}

#endif // RWS_LOGIC_H

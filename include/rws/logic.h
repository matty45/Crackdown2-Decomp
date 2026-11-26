// RWS main-loop messages (RuffKing's framework/mainloop/logic.cpp defines them in namespace RWS). CD2 registers
// iMsgRunningTick (0x83A05C54) as "iMsgRunningTick" with format "RwUInt32" in 0x82915E10.
#ifndef RWS_LOGIC_H
#define RWS_LOGIC_H

#include "rws/eventid.h"

namespace RWS
{
    // RuffKing's logic.cpp defines it 8 bytes before iMsgRunningTick, as CD2's 0x83A05C4C; RuffKing's and CD2's
    // cWorldManager destructors (0x82809E00 in CD2) unlink iMsgRunningTick and then this one.
    extern CEventId iMsgRunningPreTick;
    extern CEventId iMsgRunningTick;
    // CD2 0x82915E10 registers these exact names at 0x83A05C5C / 0x83A05C84.
    extern CEventId iMsgRunningPostTick;
    extern CEventId iMsgPausedPostTick;
}

#endif // RWS_LOGIC_H

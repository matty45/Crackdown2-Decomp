// CHARACTER::cFrontEndAgent (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8289CF68) builds cClass(0x67D, "cFrontEndAgent", 0x3EC0); 0x3EC0 is the size its registrar gives.
#ifndef CHARACTER_CFRONTENDAGENT_H
#define CHARACTER_CFRONTENDAGENT_H

#include "fun_runtime/class.h"

namespace CHARACTER
{
    class cFrontEndAgent
    {
    public:
        static const Fun_Runtime::cClass *ms_pcFrontEndAgentClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // CHARACTER_CFRONTENDAGENT_H

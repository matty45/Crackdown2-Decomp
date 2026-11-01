// PHYSICS::cBody (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82683318) builds cClass(0x63C, "cBody", 0x250); 0x250 is the size its registrar gives.
#ifndef PHYSICS_CBODY_H
#define PHYSICS_CBODY_H

#include "fun_runtime/class.h"

namespace PHYSICS
{
    class cBody
    {
    public:
        static const Fun_Runtime::cClass *ms_pcBodyClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // PHYSICS_CBODY_H

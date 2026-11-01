// unknown::CCarController (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8277ED80) builds cClass(0x929, "CCarController", 0xA30); 0xA30 is the size its registrar gives.
#ifndef UNKNOWN_CCARCONTROLLER_H
#define UNKNOWN_CCARCONTROLLER_H

#include "fun_runtime/class.h"

namespace unknown
{
    class CCarController
    {
    public:
        static const Fun_Runtime::cClass *ms_pCCarControllerClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CCARCONTROLLER_H

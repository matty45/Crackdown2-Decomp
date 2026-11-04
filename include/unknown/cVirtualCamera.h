#include "rws/attributes.h"
// unknown::cVirtualCamera (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8252CE88) builds cClass(0x637, "cVirtualCamera", 0xF10); 0xF10 is the size its registrar gives.
#ifndef UNKNOWN_CVIRTUALCAMERA_H
#define UNKNOWN_CVIRTUALCAMERA_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cVirtualCamera
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcVirtualCameraClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CVIRTUALCAMERA_H

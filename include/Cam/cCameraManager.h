#include "rws/attributes.h"
// Cam::cCameraManager (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8252C070) builds cClass(0x622, "cCameraManager", 0x170); 0x170 is the size its registrar gives.
#ifndef CAM_CCAMERAMANAGER_H
#define CAM_CCAMERAMANAGER_H

#include "fun_runtime/class.h"

namespace Cam
{
    class cCameraManager
    {
    public:
        // CD2 0x8252BF60: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x8252C018: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcCameraManagerClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // CAM_CCAMERAMANAGER_H

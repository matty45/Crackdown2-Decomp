#include "rws/attributes.h"
// WorldManager::cLOD4Environment (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82807868) builds cClass(0x199E, "cLOD4Environment", 0x2C0); 0x2C0 is the size its registrar gives.
#ifndef WORLDMANAGER_CLOD4ENVIRONMENT_H
#define WORLDMANAGER_CLOD4ENVIRONMENT_H

#include "fun_runtime/class.h"

namespace WorldManager
{
    class cLOD4Environment
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcLOD4EnvironmentClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // WORLDMANAGER_CLOD4ENVIRONMENT_H

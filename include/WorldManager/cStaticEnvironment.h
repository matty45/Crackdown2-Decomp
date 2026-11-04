#include "rws/attributes.h"
// WorldManager::cStaticEnvironment (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82808988) builds cClass(0x3, "cStaticEnvironment", 0x2E0); 0x2E0 is the size its registrar gives.
#ifndef WORLDMANAGER_CSTATICENVIRONMENT_H
#define WORLDMANAGER_CSTATICENVIRONMENT_H

#include "fun_runtime/class.h"

namespace WorldManager
{
    class cStaticEnvironment
    {
    public:
        // CD2 0x82808970: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcStaticEnvironmentClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // WORLDMANAGER_CSTATICENVIRONMENT_H

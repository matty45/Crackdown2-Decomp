#ifndef WorldManager_cWorldManager_H
#define WorldManager_cWorldManager_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace WorldManager
{
    class cWorldManager : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcWorldManagerClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif

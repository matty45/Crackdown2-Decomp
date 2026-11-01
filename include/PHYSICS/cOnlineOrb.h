#ifndef PHYSICS_cOnlineOrb_H
#define PHYSICS_cOnlineOrb_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace PHYSICS
{
    class cOnlineOrb : public RWS::CAttributeHandler
    {
    public:
        static const Fun_Runtime::cClass *ms_pcOnlineOrbClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

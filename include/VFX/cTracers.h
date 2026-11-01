#ifndef VFX_cTracers_H
#define VFX_cTracers_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace VFX
{
    class cTracers : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcTracersClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif

#ifndef PHYSICS_cSurfaceProfile_H
#define PHYSICS_cSurfaceProfile_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace PHYSICS
{
    class cSurfaceProfile : public RWS::CAttributeHandler
    {
    public:
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcSurfaceProfileClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

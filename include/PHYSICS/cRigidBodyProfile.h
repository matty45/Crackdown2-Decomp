#ifndef PHYSICS_cRigidBodyProfile_H
#define PHYSICS_cRigidBodyProfile_H

#include "rws/attributes.h"

namespace PHYSICS
{
    class cRigidBodyProfile : public RWS::CAttributeHandler
    {
    public:
        // CD2 0x826A4358: attribute-handler vtable slot 5, returning Ret_OK.
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

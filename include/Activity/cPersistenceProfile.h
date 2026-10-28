#ifndef ACTIVITY_CPERSISTENCEPROFILE_H
#define ACTIVITY_CPERSISTENCEPROFILE_H

#include "rws/attributes.h"

namespace RWS { class DynamicAllocationPolicy {}; }

namespace Activity
{
    class cPersistenceProfile : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);

        static const char *RetRWSClassName();
    };
}

#endif

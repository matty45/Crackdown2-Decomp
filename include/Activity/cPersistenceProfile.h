#ifndef ACTIVITY_CPERSISTENCEPROFILE_H
#define ACTIVITY_CPERSISTENCEPROFILE_H

#include "rws/attributes.h"

#include "rws/dynamicallocationpolicy.h"

namespace Activity
{
    class cPersistenceProfile : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);

        static const char *RetRWSClassName();
        // CD2: cPersistenceProfile's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x823D9430
        virtual bool HandleDataInNewDesignBuild(); // 9: 0x8288FB78
    };
}

#endif

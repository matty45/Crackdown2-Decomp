#ifndef VFX_cVFXPriorityTable_H
#define VFX_cVFXPriorityTable_H

#include "rws/attributes.h"
#include "cd2/layout.h"

namespace VFX
{
    class cVFXPriorityTable : public RWS::CAttributeHandler
    {
    public:
        // CD2's deleting wrapper inlines the destructor and stores the derived vptr.
        virtual ~cVFXPriorityTable() {}
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        CD2_LAYOUT_CHECKS(cVFXPriorityTable, CD2_SIZE(cVFXPriorityTable, 0x18))
    };
}

#endif

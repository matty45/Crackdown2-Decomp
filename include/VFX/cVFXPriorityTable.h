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
        // CD2: cVFXPriorityTable's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x822CBFC8
        virtual bool HandleDataInNewDesignBuild(); // 9: 0x8288FB78
    public:
        CD2_LAYOUT_CHECKS(cVFXPriorityTable, CD2_SIZE(cVFXPriorityTable, 0x18))
    };
}

#endif

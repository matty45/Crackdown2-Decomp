#ifndef VFX_cVFXPriorityTable_H
#define VFX_cVFXPriorityTable_H

#include "rws/attributes.h"
#include "cd2/layout.h"

namespace VFX
{
    class cVFXPriorityTable : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif

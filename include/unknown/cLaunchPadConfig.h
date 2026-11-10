#ifndef unknown_cLaunchPadConfig_H
#define unknown_cLaunchPadConfig_H

#include "rws/attributes.h"
#include "cd2/layout.h"

namespace unknown
{
    class cLaunchPadConfig : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // CD2: cLaunchPadConfig's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x82713E38
    };
}

#endif

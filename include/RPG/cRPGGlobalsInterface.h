#ifndef RPG_cRPGGlobalsInterface_H
#define RPG_cRPGGlobalsInterface_H

#include "rws/attributes.h"
#include "cd2/layout.h"

namespace RPG
{
    class cRPGGlobalsInterface : public RWS::CAttributeHandler
    {
    public:
        // CD2 0x82754218 inlines this destructor and stores the derived vptr.
        virtual ~cRPGGlobalsInterface() {}
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        CD2_LAYOUT_CHECKS(cRPGGlobalsInterface, CD2_SIZE(cRPGGlobalsInterface, 0x18))
    };
}

#endif

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
        // CD2: cRPGGlobalsInterface's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x82754278
        virtual bool HandleDataInNewDesignBuild(); // 9: 0x8288FB78
    public:
        CD2_LAYOUT_CHECKS(cRPGGlobalsInterface, CD2_SIZE(cRPGGlobalsInterface, 0x18))
    };
}

#endif

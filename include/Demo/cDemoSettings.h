#ifndef Demo_cDemoSettings_H
#define Demo_cDemoSettings_H

#include "rws/attributes.h"
#include "cd2/layout.h"

namespace Demo
{
    class cDemoSettings : public RWS::CAttributeHandler
    {
    public:
        // CD2's deleting destructor (0x82913690) stores this class's vptr before the base call.
        virtual ~cDemoSettings() {}
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // CD2: cDemoSettings's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual bool HandleDataInNewDesignBuild(); // 9: 0x8288FB78
    };
}

#endif

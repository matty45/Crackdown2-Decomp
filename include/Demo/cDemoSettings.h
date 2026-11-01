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
    };
}

#endif

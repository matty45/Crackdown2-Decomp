#ifndef Demo_cDemoSettings_H
#define Demo_cDemoSettings_H

#include "rws/attributes.h"
#include "cd2/layout.h"

namespace Demo
{
    class cDemoSettings : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif

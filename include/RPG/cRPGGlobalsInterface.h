#ifndef RPG_cRPGGlobalsInterface_H
#define RPG_cRPGGlobalsInterface_H

#include "rws/attributes.h"
#include "cd2/layout.h"

namespace RPG
{
    class cRPGGlobalsInterface : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif

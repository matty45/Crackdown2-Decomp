#ifndef unknown_cRenegadesGameModePrototype_H
#define unknown_cRenegadesGameModePrototype_H

#include "rws/attributes.h"

namespace unknown
{
    class cRenegadesGameModePrototype : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

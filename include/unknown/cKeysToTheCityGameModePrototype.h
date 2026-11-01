#ifndef unknown_cKeysToTheCityGameModePrototype_H
#define unknown_cKeysToTheCityGameModePrototype_H

#include "rws/attributes.h"

namespace unknown
{
    class cKeysToTheCityGameModePrototype : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

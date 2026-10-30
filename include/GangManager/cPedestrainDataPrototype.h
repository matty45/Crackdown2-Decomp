#ifndef GangManager_cPedestrainDataPrototype_H
#define GangManager_cPedestrainDataPrototype_H

#include "rws/attributes.h"

namespace GangManager
{
    class cPedestrainDataPrototype : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

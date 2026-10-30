#ifndef GangManager_cTurretDataPrototype_H
#define GangManager_cTurretDataPrototype_H

#include "rws/attributes.h"

namespace GangManager
{
    class cTurretDataPrototype : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

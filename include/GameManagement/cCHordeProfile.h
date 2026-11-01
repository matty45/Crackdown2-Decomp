#ifndef GameManagement_cCHordeProfile_H
#define GameManagement_cCHordeProfile_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cCHordeProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

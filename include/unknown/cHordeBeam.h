#ifndef unknown_cHordeBeam_H
#define unknown_cHordeBeam_H

#include "rws/attributes.h"

namespace unknown
{
    class cHordeBeam : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

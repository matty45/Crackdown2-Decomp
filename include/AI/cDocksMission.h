#ifndef AI_cDocksMission_H
#define AI_cDocksMission_H

#include "rws/attributes.h"

namespace AI
{
    class cDocksMission : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

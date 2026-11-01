#ifndef unknown_cATVAssaultGameModePrototype_H
#define unknown_cATVAssaultGameModePrototype_H

#include "rws/attributes.h"

namespace unknown
{
    class cATVAssaultGameModePrototype : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

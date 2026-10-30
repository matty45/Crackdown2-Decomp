#ifndef Prop_cPintleFaceplate_H
#define Prop_cPintleFaceplate_H

#include "rws/attributes.h"

namespace Prop
{
    class cPintleFaceplate : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

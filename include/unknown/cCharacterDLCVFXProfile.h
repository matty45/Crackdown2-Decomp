#ifndef unknown_cCharacterDLCVFXProfile_H
#define unknown_cCharacterDLCVFXProfile_H

#include "rws/attributes.h"

namespace unknown
{
    class cCharacterDLCVFXProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

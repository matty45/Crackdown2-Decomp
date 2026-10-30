#ifndef CHARACTER_cCharacterGlobalDlcProfile_H
#define CHARACTER_cCharacterGlobalDlcProfile_H

#include "rws/attributes.h"

namespace CHARACTER
{
    class cCharacterGlobalDlcProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

#ifndef GameManagement_cFinalMissionBarrier_H
#define GameManagement_cFinalMissionBarrier_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cFinalMissionBarrier : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif

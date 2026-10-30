#ifndef AI_CPEDESTRIANBASE_H
#define AI_CPEDESTRIANBASE_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"

namespace AI
{
    class cPedestrianBase : public cNonGameBase
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcPedestrianBaseClass;

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

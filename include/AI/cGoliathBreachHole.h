#ifndef AI_CGOLIATHBREACHHOLE_H
#define AI_CGOLIATHBREACHHOLE_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "AI/cBreachHole.h"

namespace AI
{
    class cGoliathBreachHole : public cBreachHole
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcGoliathBreachHoleClass;

        cGoliathBreachHole();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif


#ifndef AI_CGOLIATHBREACHHOLE_H
#define AI_CGOLIATHBREACHHOLE_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "AI/cBreachHole.h"

namespace AI
{
    // RuffKing's base. CD2's table (0x820043E8) holds this class's RetClass, IsA and RetClassName in slots 11 to 13.
    class cGoliathBreachHole : public cBreachHole
    {
    public:
        // CD2's Goliath table differs from cBreachHole at slots 16..19.
        virtual void TickUpdate(float, bool); // 0x824740A8
        virtual void TryKillAllSpawned(); // 0x82474190
        virtual void ExitState(eBreachHoleState); // 0x82474288
        virtual void EnterState(eBreachHoleState); // 0x824742D8
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcGoliathBreachHoleClass;

        cGoliathBreachHole();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2: cGoliathBreachHole's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x82473F90
    };
}

#endif


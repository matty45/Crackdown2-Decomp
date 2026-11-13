#ifndef AI_CBREACHHOLE_H
#define AI_CBREACHHOLE_H

#include "rws/systemcommands.h"
#include "rws/attributes.h"
#include "rws/eventhandler.h"
#include "rws/dynamicallocationpolicy.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/layout.h"

namespace AI
{
    // CD2's table (0x820044D8) has RWS::CAttributeHandler's eleven slots, then RetClass, IsA, RetClassName and Destruct in slots
    // 11 to 14, as RuffKing declares the class: RWS::CSystemCommands, CAttributeHandler, CEventHandler and DynamicAllocationPolicy.
    class cBreachHole : public RWS::CSystemCommands, public RWS::CAttributeHandler, public RWS::CEventHandler,
        public RWS::DynamicAllocationPolicy
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcBreachHoleClass;

        cBreachHole();
        // Out of line (CD2 0x8246EB40): the deleting wrapper calls it.
        virtual ~cBreachHole();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        virtual void Destruct();
        // RWS::CEventHandler's pure virtual (RuffKing declares the override).
        virtual void HandleEvents(RWS::CMsg &);
        // CD2: cBreachHole's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x8246EC00

    private:
        // CD2's registrar and MakeNew (0x8246E758) give 0x1C0 bytes; RuffKing's class (cBreach.h) is 0x170, so its
        // field offsets are not CD2's past the first ones. Not modelled yet.
        unsigned char m_unmodelled20[0x1C0 - 0x20];
        CD2_LAYOUT_CHECKS(cBreachHole, CD2_SIZE(cBreachHole, 0x1C0))
    };
}

#endif


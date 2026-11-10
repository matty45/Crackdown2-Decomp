#include "rws/attributes.h"
// unknown::cOutlines2 (Crackdown 2): STAND-IN. CD2 MakeNew calls cNonGameBase's constructor
// and installs five derived vptrs at 0, 0x18, 0x1C, 0x30 and 0x38; there are no added fields.
// StaticCreateClass (0x827A4090) builds cClass(0x1027FB, "cOutlines2", 0x7C); 0x7C is the size its registrar gives.
#ifndef UNKNOWN_COUTLINES2_H
#define UNKNOWN_COUTLINES2_H

#include "fun_runtime/class.h"
#include "gom/non_game_base.h"

namespace unknown
{
    class cOutlines2 : public cNonGameBase
    {
    public:
        __forceinline cOutlines2() {}
        virtual ~cOutlines2() {}
        virtual const char *RetClassName() const;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcOutlines2Class;
        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2: cOutlines2's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual int RetUniqueID(); // CEventHandler 1: 0x82604E70
    public:
        CD2_LAYOUT_CHECKS(cOutlines2, CD2_SIZE(cOutlines2, 0x7C))
    };
}

#endif // UNKNOWN_COUTLINES2_H

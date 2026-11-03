// Hierarchy correction: CD2 debug subobject at 0x120, cBody size 0x250.
#include "rws/attributes.h"
// PHYSICS::cBody (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82683318) builds cClass(0x63C, "cBody", 0x250); 0x250 is the size its registrar gives.
#ifndef PHYSICS_CBODY_H
#define PHYSICS_CBODY_H

#include "fun_runtime/class.h"
#include "gom/game_base.h"
#include "GDb/cDebugPageHandler.h"

namespace PHYSICS
{
    class cBody : public cGameBase, public GDb::cDebugPageHandler
    {
    public:
        virtual ~cBody();
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcBodyClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    private:
        unsigned char m_unknown124[0x250 - 0x124];
        CD2_LAYOUT_CHECKS(cBody, CD2_SIZE(cBody, 0x250))
    };
}

#endif // PHYSICS_CBODY_H

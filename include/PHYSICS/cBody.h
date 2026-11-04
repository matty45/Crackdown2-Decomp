#include "gom/object_prototype.h"
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
        // Interface-only prototype stand-in: name and base from RuffKing.
        // Instance fields and complete size are not recovered; this is not an allocation layout.
        class cBodyPrototype : public cGameBase::cGameBasePrototype {};

        // CD2 0x826832F0: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FDF730 names placement factory 0x82683300.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
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

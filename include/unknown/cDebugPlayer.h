#include "gom/non_game_base.h"
#include "rws/attributes.h"
// unknown::cDebugPlayer (Crackdown 2): STAND-IN; derived storage is not modelled yet.
// Base cNonGameBase: CD2's inheritance registrar names it, and the destructor 0x82714730 restores only cNonGameBase's subobject vtables before calling ~cNonGameBase.
// StaticCreateClass (0x827147F8) builds cClass(0x63D, "cDebugPlayer", 0x190); 0x190 is the size its registrar gives.
#ifndef UNKNOWN_CDEBUGPLAYER_H
#define UNKNOWN_CDEBUGPLAYER_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cDebugPlayer : public cNonGameBase
    {
    public:
        // CD2 0x82714D38: the allocation factory calls this constructor out of line.
        cDebugPlayer();
        // CD2 0x82714668: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x82714678: registered-class virtual slot 1.
        virtual bool IsA(const Fun_Runtime::cClass &c) const;
        // CD2 0x82714730.
        virtual ~cDebugPlayer();
        // CD2 0x82715180: primary slot 6 (Term); the destructor calls it.
        virtual Fun_Runtime::RetVal Term();
        // CD2 0x82714720: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcDebugPlayerClass;
        static Fun_Runtime::cClass &StaticCreateClass();

    private:
        // Descriptor and factory allocation agree on the complete size; own fields remain unrecovered.
        unsigned char m_unmodelled7C[0x190 - 0x7C];
        // CD2: cDebugPlayer's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x82715470
        virtual Fun_Runtime::RetVal Init(RWS::CAttributePacket const &); // 5: 0x82715070
        virtual bool HandleDataInNewDesignBuild(); // 9: 0x8288FB78
        virtual void Slot51(); // 50: 0x82715908
        virtual int RetUniqueID(); // CEventHandler 1: 0x82604E70
        virtual void HandleEvents(RWS::CMsg &); // CEventHandler 5: 0x82715208
    private:
        CD2_LAYOUT_CHECKS(cDebugPlayer, CD2_SIZE(cDebugPlayer, 0x190))
    };
}

#endif // UNKNOWN_CDEBUGPLAYER_H

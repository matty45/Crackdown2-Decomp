#include "fun_runtime/class.h"
#include "rws/attributes.h"
// VFX::cBloom (Crackdown 2): STAND-IN. Base cNonGameBase, as in RuffKing's header; RetClassName
// (0x82791958) is slot 11 of the vtable at 0x8214C650, as cNonGameBase's RetClassName.
#ifndef VFX_CBLOOM_H
#define VFX_CBLOOM_H

#include "gom/non_game_base.h"
#include "rws/logic.h"
#include "cd2/layout.h"

#include "gom/non_game_base.h"

namespace VFX
{
    class cBloom;

    // RuffKing's singleton pointer (CD2 0x838010E8: set by the constructor, cleared by the destructor).
    extern cBloom *g_pBloom;

    class cBloom : public cNonGameBase
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2's MakeNew (0x827918C8) inlines this constructor: cNonGameBase's constructor, the vtables, the field at 0x7C and
        // g_pBloom. __forceinline: /Ob1 declines a plain inline constructor with this many stores (docs/matching-notes.md).
        __forceinline cBloom(const RWS::CAttributePacket &) : m_unknown7C(0) { g_pBloom = this; }
        // CD2 0x827919B8.
        virtual ~cBloom();
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x82791868: registered-class virtual slot 1.
        virtual bool IsA(const Fun_Runtime::cClass &c) const;
        // CD2 descriptor pointer 0x838f6280; its initializer names cBloom.
        static const Fun_Runtime::cClass *ms_pcBloomClass;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    private:
        // Name ours: RuffKing's dump names no field, but its size leaves room for this one; the constructor zeroes it.
        unsigned int m_unknown7C;

        // CD2: cBloom's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x82580578
        virtual int RetUniqueID(); // CEventHandler 1: 0x82604E70
    private:
        CD2_LAYOUT_CHECKS(cBloom,
            CD2_SIZE(cBloom, 0x80)
            CD2_OFFSET(cBloom, m_unknown7C, 0x7C))
    };
}

#endif // VFX_CBLOOM_H

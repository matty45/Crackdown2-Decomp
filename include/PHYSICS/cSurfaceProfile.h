#ifndef PHYSICS_cSurfaceProfile_H
#define PHYSICS_cSurfaceProfile_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"

namespace PHYSICS
{
    // STAND-IN: RuffKing names; CD2 allocates 0x80 and uses the surface index at 0x7C.
    class cSurfaceProfile : public cNonGameBase
    {
    public:
        // CD2's deleting wrapper inlines the derived destructor and restores all five vptrs.
        __forceinline cSurfaceProfile() {}
        virtual ~cSurfaceProfile() {}
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        // CD2 0x82696150: attribute-handler vtable slot 5, returning Ret_OK.
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcSurfaceProfileClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    protected:
        unsigned int m_nSurfaceIndex;
        // CD2: cSurfaceProfile's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::RetVal Term(); // 6: 0x82696150
        virtual bool HandleDataInNewDesignBuild(); // 9: 0x8288FB78
        virtual int RetUniqueID(); // CEventHandler 1: 0x82604E70
    protected:
        CD2_LAYOUT_CHECKS(cSurfaceProfile,
            CD2_SIZE(cSurfaceProfile, 0x80)
            CD2_OFFSET(cSurfaceProfile, m_nSurfaceIndex, 0x7C))
    };
}

#endif

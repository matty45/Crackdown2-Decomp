#include "rws/attributes.h"
// VFX::cVFXSurfaceProfile (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in RuffKing's header;
// RetClassName (0x827CCC50) is slot 11 of the vtable at 0x82150BA8, as cNonGameBase's RetClassName.
#ifndef VFX_CVFXSURFACEPROFILE_H
#define VFX_CVFXSURFACEPROFILE_H

#include "gom/non_game_base.h"

namespace VFX
{
    class cVFXSurfaceProfile : public cNonGameBase
    {
    public:
        // CD2 inlines the derived constructor/destructor around the out-of-line shared base.
        __forceinline cVFXSurfaceProfile() {}
        virtual ~cVFXSurfaceProfile() {}
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcVFXSurfaceProfileClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    protected:
        // RuffKing name; CD2 HandleAttributes accesses this index at 0x7C.
        unsigned int m_nSurfaceIndex;
        // CD2: cVFXSurfaceProfile's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual bool HandleDataInNewDesignBuild(); // 9: 0x8288FB78
        virtual int RetUniqueID(); // CEventHandler 1: 0x82604E70
    protected:
        CD2_LAYOUT_CHECKS(cVFXSurfaceProfile,
            CD2_SIZE(cVFXSurfaceProfile, 0x80)
            CD2_OFFSET(cVFXSurfaceProfile, m_nSurfaceIndex, 0x7C))
    };
}

#endif // VFX_CVFXSURFACEPROFILE_H

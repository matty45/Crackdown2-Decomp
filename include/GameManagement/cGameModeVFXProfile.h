#ifndef GameManagement_cGameModeVFXProfile_H
#define GameManagement_cGameModeVFXProfile_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cGameModeVFXProfile : public RWS::CAttributeHandler
    {
    public:
        // CD2's deleting wrapper inlines the destructor and stores the derived vptr.
        virtual ~cGameModeVFXProfile() {}
        cGameModeVFXProfile(const RWS::CAttributePacket &) { for (int i = 0; i < 13; ++i) m_aVFXID[i] = -1; }
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
    protected:
        // RuffKing names/count; CD2 MakeNew resets all 13 entries at 0x837C25DC.
        static int m_aVFXID[13];
        // CD2: cGameModeVFXProfile's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual bool HandleDataInNewDesignBuild(); // 9: 0x8288FB78
    protected:
        CD2_LAYOUT_CHECKS(cGameModeVFXProfile, CD2_SIZE(cGameModeVFXProfile, 0x18))
    };
}

#endif

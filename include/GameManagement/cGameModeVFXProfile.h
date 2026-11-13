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
        // CD2 primary table 0x8215B764 slot 12; reference name.
        virtual void Destruct();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        // Reference attribute IDs; CD2's handler uses the same 0..13 sequence.
        enum LoadParameterTypes
        {
            CMD_RoofVFX_Start = 0, CMD_RoofVFX_LOD1, CMD_RoofVFX_LOD2,
            CMD_RoofVFX_End, CMD_RoofVFX_PassThrough,
            CMD_RoadVFX_Start, CMD_RoadVFX_LOD1, CMD_RoadVFX_LOD2,
            CMD_RoadVFX_End, CMD_RoadVFX_PassThrough,
            CMD_TagVFX_Start, CMD_TagVFX_Orb, CMD_TagVFX_OrbTrail,
            CMD_Max_VFX_HeightScale
        };
    protected:
        // RuffKing names/count; CD2 MakeNew resets all 13 entries at 0x837C25DC.
        static int m_aVFXID[13];
        static float m_fMaxHeightScale; // CD2 0x837C25D8; reference name
        // CD2: cGameModeVFXProfile's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual bool HandleDataInNewDesignBuild(); // 9: 0x8288FB78
    protected:
        CD2_LAYOUT_CHECKS(cGameModeVFXProfile, CD2_SIZE(cGameModeVFXProfile, 0x18))
    };
}

#endif

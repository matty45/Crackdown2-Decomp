#include "fun_runtime/class.h"
#include "rws/attributes.h"
// Vehicle::cGenVehicleProfile (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in RuffKing's
// header; RetClassName (0x8269C6C0) is slot 11 of the vtable at 0x821332D0, as cNonGameBase's RetClassName.
#ifndef VEHICLE_CGENVEHICLEPROFILE_H
#define VEHICLE_CGENVEHICLEPROFILE_H

#include "gom/non_game_base.h"

namespace Vehicle
{
    class cGenVehicleProfile : public cNonGameBase
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2 0x8269C760: the allocation factory calls this constructor out of line.
        cGenVehicleProfile();
        // RuffKing defines the destructor inline; CD2's deleting wrapper restores
        // the five derived tables and calls ~cNonGameBase, with no own-field cleanup.
        virtual ~cGenVehicleProfile() {}
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 descriptor pointer 0x838474f0; its initializer names cGenVehicleProfile.
        static const Fun_Runtime::cClass *ms_pcGenVehicleProfileClass;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    private:
        // RuffKing names; CD2 HandleAttributes cases 55..83 select 26 VFX entries.
        // Cases 30..45 distinguish the four damage arrays; each has 12 damage types.
        static int m_aVehicleVFX[26];
        static float m_fAICharacterDamageThreshold[12];
        static float m_fPlayerCharacterDamageThreshold[12];
        static float m_fAICharacterDamageModifier[12];
        static float m_fPlayerCharacterDamageModifier[12];
        static float m_fAIGearChangeRatio; // CD2 case 84; constructor default is 0.6f.
        // Descriptor and factory allocation agree on the complete size; own fields remain unrecovered.
        CD2_LAYOUT_CHECKS(cGenVehicleProfile, CD2_SIZE(cGenVehicleProfile, 0x7C))
    };
}

#endif // VEHICLE_CGENVEHICLEPROFILE_H

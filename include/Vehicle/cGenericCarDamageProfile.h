// Vehicle::cGenericCarDamageProfile: car-damage settings, set from RWS attributes. RuffKing names the debris prototype
// pointer and name and the hinge-open fraction; CD2's version (0x5C bytes, the registrar's size) has a second
// prototype pointer/name pair. HandleAttributes (0x826A66D8) fills 0x18 from the name at 0x20 and 0x1C from the name
// at 0x3C, so the 0x18/0x20 pair is RuffKing's and the 0x1C/0x3C pair's names are ours. MakeNew (0x826A6550) inlines
// the constructor, which records the object in ms_pInstance (our name); the destructor (0x826A6658) frees both names.
#ifndef Vehicle_cGenericCarDamageProfile_H
#define Vehicle_cGenericCarDamageProfile_H

#include "rws/attributes.h"
#include "fun_runtime/stringc.h"
#include "cd2/layout.h"

namespace GOM { class cObjectPrototype; }

namespace Vehicle
{
    class cGenericCarDamageProfile : public RWS::CAttributeHandler
    {
    public:
        cGenericCarDamageProfile(const RWS::CAttributePacket &)
            : m_pVehicleDebrisPrototype(0), m_pExtraDebrisPrototype(0), m_fHingeOpenFraction(0.8f)
        {
            ms_pInstance = this;
        }
        virtual ~cGenericCarDamageProfile();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

        static cGenericCarDamageProfile *ms_pInstance;

    private:
        GOM::cObjectPrototype *m_pVehicleDebrisPrototype; // 0x18
        GOM::cObjectPrototype *m_pExtraDebrisPrototype;   // 0x1C
        Fun_Runtime::cStringc m_sVehicleDebrisProto;      // 0x20
        Fun_Runtime::cStringc m_sExtraDebrisProto;        // 0x3C
        float m_fHingeOpenFraction;                       // 0x58

        CD2_LAYOUT_CHECKS(cGenericCarDamageProfile,
            CD2_SIZE(cGenericCarDamageProfile, 0x5C)
            CD2_OFFSET(cGenericCarDamageProfile, m_pExtraDebrisPrototype, 0x1C)
            CD2_OFFSET(cGenericCarDamageProfile, m_sVehicleDebrisProto, 0x20)
            CD2_OFFSET(cGenericCarDamageProfile, m_sExtraDebrisProto, 0x3C)
            CD2_OFFSET(cGenericCarDamageProfile, m_fHingeOpenFraction, 0x58))
    };
}

#endif

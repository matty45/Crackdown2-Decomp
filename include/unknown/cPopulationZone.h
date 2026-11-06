#include "rws/attributes.h"
// unknown::cPopulationZone: interface stand-in. CD2 constructor 0x8280C388
// constructs CAttributeHandler at +0 and calls cZone's constructor at +0x18;
// registered-class interface is +0x2C. Instance storage remains incomplete.
// StaticCreateClass (0x8280C090) builds cClass(0x416, "cPopulationZone", 0x150); 0x150 is the size its registrar gives.
#ifndef UNKNOWN_CPOPULATIONZONE_H
#define UNKNOWN_CPOPULATIONZONE_H

#include "fun_runtime/class.h"
#include "unknown/cZone.h"

namespace GangManager { class cGangInfo; }

namespace unknown
{
    class cPopulationZone : public RWS::CAttributeHandler, public cZone
    {
    public:
        // CD2 script registrations name these methods and their two stored gang pointers.
        GangManager::cGangInfo *RetGangInControl() const;
        void SetGangInControl(GangManager::cGangInfo *);
        void SetInitialGangInControl(GangManager::cGangInfo *);
        // CD2 0x8280C068: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // CD2 0x8280BFF8: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x8280C498 clears both gang pointers before cZone's and CAttributeHandler's destructors run.
        virtual ~cPopulationZone();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcPopulationZoneClass;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static Fun_Runtime::cClass &StaticCreateClass();
    private:
        unsigned char m_unmodelled50[4];
        GangManager::cGangInfo *m_pInitialGangInControl;
        GangManager::cGangInfo *m_pGangInControl;
        CD2_LAYOUT_CHECKS(cPopulationZone,
            CD2_OFFSET(cPopulationZone, m_pInitialGangInControl, 0x54)
            CD2_OFFSET(cPopulationZone, m_pGangInControl, 0x58))
    };
}

#endif // UNKNOWN_CPOPULATIONZONE_H

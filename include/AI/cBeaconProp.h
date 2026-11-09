// AI::cBeaconProp (Crackdown 2): STAND-IN with reference base order cMissionCriticalProp, hkEntityListener.
// CD2 constructor 0x8245C470 confirms the listener at +0xE40 and mission pointer at +0xE44, size 0xE50.
// RetClassName (0x8245C278) is primary slot 11 of table 0x82103748, as cNonGameBase's RetClassName.
#ifndef AI_CBEACONPROP_H
#define AI_CBEACONPROP_H

#include "Prop/cProp.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
#include "AI/cMissionCriticalProp.h"
#include "Havok/hkEntityListener.h"

namespace AI
{
    class cBeaconMission;
    class cBeaconProp : public AI::cMissionCriticalProp, public hkEntityListener
    {
    public:
        // RuffKing: cBeaconPropPrototype : cMissionCriticalPropPrototype, 1280 bytes. CD2's MakeNew (0x8245C200)
        // allocates 0x500, calls cPropPrototype's constructor and stores this class's vptrs and the base's zero at
        // 0x4F0: both derived constructors are inline. Init is slot 5 (0x8245C460).
        class cBeaconPropPrototype : public cMissionCriticalProp::cMissionCriticalPropPrototype
        {
        public:
            __forceinline cBeaconPropPrototype(const RWS::CAttributePacket &packet)
                : cMissionCriticalProp::cMissionCriticalPropPrototype(packet) {}
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

            CD2_LAYOUT_CHECKS(cBeaconPropPrototype,
                CD2_SIZE(cBeaconPropPrototype, 0x500))
        };

        // CD2 spawning initializer 0x82F87CA8 names placement factory 0x8245c288.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 0x8245C470: the placement factory (0x8245C288) calls it out of line with the prototype.
        cBeaconProp(GOM::cObjectPrototype *);
        // CD2's deleting wrapper inlines all base-table restores and the cMissionCriticalProp destructor call.
        // Ordinary inline leaves a separate destructor call in this compiler; force the evidenced inlining.
        virtual __forceinline ~cBeaconProp() {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcBeaconPropClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
        // CD2 primary slot 341; cMissionCriticalProp retains cProp's 341-entry primary interface.
        virtual void SetupForBeaconReplication();
        virtual void PreAddToPhysicsWorld();
        virtual void entityAddedCallback(hkEntity *);
        virtual void entityRemovedCallback(hkEntity *);
        virtual void entityDeletedCallback(hkEntity *);
    protected:
        // Reference member name/order; CD2's hkEntityListener starts at +0xE40.
        cBeaconMission *m_pBeaconMission;
        CD2_LAYOUT_CHECKS(cBeaconProp,
            CD2_SIZE(cBeaconProp, 0xE50)
            CD2_OFFSET(cBeaconProp, m_pBeaconMission, 0xE44))
    };
}

#endif // AI_CBEACONPROP_H

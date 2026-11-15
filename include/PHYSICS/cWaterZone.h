#include "rws/attributes.h"
// PHYSICS::cWaterZone: reference base order and member names; CD2 constructor 0x82283450 confirms the layout.
// StaticCreateClass (0x82708208) builds cClass(0x10F, "cWaterZone", 0x120); 0x120 is the size its registrar gives.
#ifndef PHYSICS_CWATERZONE_H
#define PHYSICS_CWATERZONE_H

#include "fun_runtime/class.h"
#include "gom/non_game_base.h"
#include "rws/systemcommands.h"
#include "PHYSICS/cOBBox.h"

namespace PHYSICS
{
    class cColData;
    class cWaterZonePhantom;
    class cWaterZone : public RWS::CSystemCommands, public cNonGameBase
    {
    public:
        // CD2 factory calls this constructor without a packet argument.
        cWaterZone();
        virtual ~cWaterZone();
        virtual Fun_Runtime::RetVal Term();
        virtual void TickUpdate(float);
        bool GetIsAntiWater() { return m_bIsAntiWater; }
        // CD2 0x827081F8: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 0x82708140 / 0x82708150: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcWaterZoneClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    private:
        // CD2 leaves +0x7C untouched, as in cPickupBase with the same empty command mixin.
        unsigned int m_unknown7C;
    public:
        int m_nID;
    protected:
        cColData *m_pCollisionData;
        cWaterZonePhantom *m_pWaterPhantom;
        bool m_bIsAntiWater;
        Fun_Runtime::Mtx m_Transform;
        cOBBox m_OBBox;
        CD2_LAYOUT_CHECKS(cWaterZone,
            CD2_SIZE(cWaterZone, 0x120)
            CD2_OFFSET(cWaterZone, m_nID, 0x80)
            CD2_OFFSET(cWaterZone, m_pCollisionData, 0x84)
            CD2_OFFSET(cWaterZone, m_pWaterPhantom, 0x88)
            CD2_OFFSET(cWaterZone, m_bIsAntiWater, 0x8C)
            CD2_OFFSET(cWaterZone, m_Transform, 0x90)
            CD2_OFFSET(cWaterZone, m_OBBox, 0xD0))
    };
}

#endif // PHYSICS_CWATERZONE_H

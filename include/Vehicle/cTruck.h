// Vehicle::cTruck (Crackdown 2): base cCar (RuffKing; CD2 inheritance registrar 0x82FE9510), size 0x3290 (registrar and
// StaticCreateClass). Fields not modelled.
#ifndef VEHICLE_CTRUCK_H
#define VEHICLE_CTRUCK_H

#include "rws/attributes.h"
#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "fun_runtime/retval.h"
#include "Vehicle/cCar.h"

class hkRigidBody;

namespace Vehicle
{
    class cTruck : public cCar
    {
    public:
        // Name, base, overrides and size (0x4B0, no fields of its own) from RuffKing. CD2's MakeNew (0x826CB3D8) calls
        // cCarPrototype's constructor and then stores this class's tables, so the constructor is inline.
        class cTruckPrototype : public cCar::cCarPrototype
        {
        public:
            cTruckPrototype(const RWS::CAttributePacket &packet) : cCarPrototype(packet) {}
            virtual ~cTruckPrototype();
            virtual void HandleAttributes(const RWS::CAttributePacket &);
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

            CD2_LAYOUT_CHECKS(cTruckPrototype,
                CD2_SIZE(cTruckPrototype, 0x4B0))
        };

        cTruck();
        void RemoveWedge();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2 0x826CB3D8, registered by the class-factory registrar (0x82FE9578).
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcTruckClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

    private:
        // RuffKing field name; CD2 RemoveWedge loads and clears +0x3070.
        hkRigidBody *m_pWedgeRigidBody;
        unsigned char m_unmodelled3074[0x3290 - 0x3074];

        CD2_LAYOUT_CHECKS(cTruck,
            CD2_SIZE(cTruck, 0x3290)
            CD2_OFFSET(cTruck, m_pWedgeRigidBody, 0x3070))
    };
}

#endif

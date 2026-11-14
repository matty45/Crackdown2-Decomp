// Vehicle::cWheelGroup (Crackdown 2): base cLandVehicle (RuffKing), size 0x2A30: CD2's descriptor factory (0x826E1FF0)
// builds cClass(0x641, "cWheelGroup", 0x2A30), RuffKing's size. Fields not modelled.
#ifndef VEHICLE_CWHEELGROUP_H
#define VEHICLE_CWHEELGROUP_H

#include "cd2/layout.h"
#include "Vehicle/cLandVehicle.h"

namespace Vehicle
{
    class cWheelGroup : public cLandVehicle
    {
    public:
        // Name and base from RuffKing, which adds no fields (size 0x440). CD2's cCarPrototype constructor (0x826B7BE0)
        // calls cLandVehiclePrototype's directly, so this constructor is inline.
        class cWheelGroupPrototype : public cLandVehicle::cLandVehiclePrototype
        {
        public:
            cWheelGroupPrototype(const RWS::CAttributePacket &packet) : cLandVehiclePrototype(packet) {}

            CD2_LAYOUT_CHECKS(cWheelGroupPrototype,
                CD2_SIZE(cWheelGroupPrototype, 0x440))
        };

        // CD2 0x826E1FF0 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2 0x822ED488 (cCar's constructor calls it); the deleting destructor 0x826E2088 calls the destructor.
        cWheelGroup();
        virtual ~cWheelGroup();

        // CD2: cWheelGroup's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'),
        // an address its base's table does not hold there, so the class overrides it; names and signatures are the
        // bases'. Primary table 0x8201A1A8 (489 slots); cWheelGroup keeps cLandVehicle's RetClassName.
        virtual Fun_Runtime::RetVal Term();                     // 6: 0x8232CA98
        virtual void Slot13();                                  // 13: 0x826E20D8
        virtual Fun_Runtime::RetVal Init(const GOM::cSpawner *);    // 18: 0x8235BD58
        virtual void vf140();                                   // 140: 0x826E20E0
        virtual void vf167();                                   // 167: 0x826E2238
        virtual void vf296();                                   // 296: 0x826E2178
        virtual void vf342();                                   // 342: 0x826AB2D0
        virtual void ProcessControls(float);                    // 461: 0x822EC9E0
        virtual void UpdateWheelModels(const hkTransform &, float);    // 462: 0x822BE878
        virtual void UpdateWheelInfo();                         // 463: 0x822E0F38
        virtual void UpdateSkids(float);                        // 464: 0x822BF410
        // Slots 484..488 are cWheelGroup's own virtuals; CD2's bodies are all the shared empty function 0x82580578.
        virtual void vf484(); virtual void vf485(); virtual void vf486(); virtual void vf487(); virtual void vf488();
        virtual void HandleEvents(RWS::CMsg &);                 // CEventHandler 5: 0x826B1AE0
        // Registered-class table 0x82135EE0.
        virtual const Fun_Runtime::cClass &RetClass() const;    // 0x826E1F80
        virtual bool IsA(const Fun_Runtime::cClass &) const;    // 0x826E1F90

    private:
        unsigned char m_unmodelled28C0[0x2A30 - 0x28C0];

        CD2_LAYOUT_CHECKS(cWheelGroup,
            CD2_SIZE(cWheelGroup, 0x2A30))
    };
}

#endif

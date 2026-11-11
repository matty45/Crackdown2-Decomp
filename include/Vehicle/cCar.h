// Vehicle::cCar (Crackdown 2): base cWheelGroup (RuffKing), size 0x3070: its class-factory registrar (0x82FE7AE0)
// registers "cCar" with MakeNew (0x826B5D18) and size 0x3070. Fields not modelled.
#ifndef VEHICLE_CCAR_H
#define VEHICLE_CCAR_H

#include "rws/attributes.h"
#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "fun_runtime/retval.h"
#include "gom/object_prototype.h"
#include "Vehicle/cWheelGroup.h"

namespace Vehicle
{
    class cCar : public cWheelGroup
    {
    public:
        // Name, base and size (0x4B0) from RuffKing; CD2's MakeNew (0x826B5D18) allocates 0x4B0 bytes and calls the
        // constructor at 0x826B7BE0. Fields not modelled.
        class cCarPrototype : public cWheelGroup::cWheelGroupPrototype
        {
        public:
            cCarPrototype(const RWS::CAttributePacket &);       // CD2 0x826B7BE0
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);   // CD2 0x826B7CF8

        private:
            unsigned char m_unmodelled440[0x4B0 - 0x440];

            CD2_LAYOUT_CHECKS(cCarPrototype,
                CD2_SIZE(cCarPrototype, 0x4B0))
        };

        // CD2 0x826B5E30; the placement factory (0x826B5D80) forwards only this.
        cCar();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 0x826B5D98 creates the named runtime descriptor; 0x82FE7A50 initializes ms_pcCarClass from it.
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcCarClass;
        // Registered-class table 0x82134618: slot 0 (0x826B5CA8) and slot 1 (0x826B5CB8).
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);

    private:
        unsigned char m_unmodelled2A30[0x3070 - 0x2A30];

        CD2_LAYOUT_CHECKS(cCar,
            CD2_SIZE(cCar, 0x3070))
    };
}

#endif // VEHICLE_CCAR_H

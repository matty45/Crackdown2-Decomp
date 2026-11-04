// CD2 constructor 0x8277EFF0 confirms the shared base constructor chain.
#include "VEHICLE_CONTROL/cHelicopterController.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// unknown::CCarController (Crackdown 2): STAND-IN: constructor-confirmed base; remaining instance fields are not modelled.
// StaticCreateClass (0x8277ED80) builds cClass(0x929, "CCarController", 0xA30); 0xA30 is the size its registrar gives.
#ifndef UNKNOWN_CCARCONTROLLER_H
#define UNKNOWN_CCARCONTROLLER_H

#include "fun_runtime/class.h"

namespace unknown
{
    class CCarController : public VEHICLE_CONTROL::cVehicleController
    {
    public:
        // CD2 factory 0x8277ECE0 forwards only this, without a prototype argument.
        CCarController();
        // CD2 0x8277EBF0: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x8277ECD0: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x83004BE0 names placement factory 0x8277ece0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pCCarControllerClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CCARCONTROLLER_H

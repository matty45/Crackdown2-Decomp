#include "gom/object_prototype.h"
#ifndef Prop_cHingedDoor_H
#define Prop_cHingedDoor_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"
#include "Prop/cHingedProp.h"

namespace Prop
{
    class cHingedDoor : public RWS::CAttributeHandler
    {
    public:
        // CD2 0x82744380: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // CD2 spawning initializer 0x82FFAFA8 names placement factory 0x82744360.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static const Fun_Runtime::cClass *ms_pcHingedDoorClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // RuffKing base/name; CD2 MakeNew 0x827442E0 calls cHingedPropPrototype's
        // constructor and installs this derived prototype's vtable, with no new fields.
        class cHingedDoorPrototype : public cHingedProp::cHingedPropPrototype
        {
        public:
            cHingedDoorPrototype(const RWS::CAttributePacket &packet) : cHingedPropPrototype(packet) {}
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

            CD2_LAYOUT_CHECKS(cHingedDoorPrototype,
                CD2_SIZE(cHingedDoorPrototype, 0x530))
        };
        virtual const char *RetClassName() const;
    };
}

#endif

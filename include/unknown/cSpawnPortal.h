#include "Prop/cHingedProp.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// unknown::cSpawnPortal (Crackdown 2): STAND-IN; derived storage is not modelled yet.
// Base cHingedProp: its prototype derives from cHingedProp's, and the destructor 0x8273E238 calls cHingedProp's (0x82737698).
// StaticCreateClass (0x8273E150) builds cClass(0x1025, "cSpawnPortal", 0xEC0); 0xEC0 is the size its registrar gives.
#ifndef UNKNOWN_CSPAWNPORTAL_H
#define UNKNOWN_CSPAWNPORTAL_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cSpawnPortal : public Prop::cHingedProp
    {
    public:
        // CD2 table 0x821410A8 has 373 primary slots. Names/signatures of these slots remain unrecovered.
        virtual void vf372(); // primary slot 372

        // Prototype name ours, from cSpawnPortal::MakeNew (0x8273DFE8).
        // CD2 confirms the shared parent constructor and Init slot 5 (0x8273E538).
        // MakeNew allocates 0x530 and inlines the constructor over cHingedPropPrototype's (0x82738740): no fields of its own.
        class cSpawnPortalPrototype : public Prop::cHingedProp::cHingedPropPrototype
        {
        public:
            __forceinline cSpawnPortalPrototype(const RWS::CAttributePacket &packet)
                : Prop::cHingedProp::cHingedPropPrototype(packet) {}
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

            // CD2: cSpawnPortalPrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x8273E530
        public:
            CD2_LAYOUT_CHECKS(cSpawnPortalPrototype,
                CD2_SIZE(cSpawnPortalPrototype, 0x530))
        };

        // CD2 0x8273DF78: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x8273DF88: registered-class virtual slot 1.
        virtual bool IsA(const Fun_Runtime::cClass &c) const;
        // CD2 0x8273E238.
        virtual ~cSpawnPortal();
        // CD2 0x8273E058: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FF8CC8 names placement factory 0x8273e068.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcSpawnPortalClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2: cSpawnPortal's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Slot13(); // 13: 0x8273E528
        virtual void Slot23(); // 23: 0x8273E3C0
    };
}

#endif // UNKNOWN_CSPAWNPORTAL_H

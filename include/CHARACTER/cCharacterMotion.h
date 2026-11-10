// STAND-IN: RuffKing cCharacterMotion derives from cNetDynamicBody. CD2 constructor 0x82308218 calls
// cNetDynamicBody's constructor, installs primary table 0x8200FA90 (347 slots), and retains its secondary bases.
// Descriptor 0x8229FDC8 gives size 0x11F0; fields beyond the 0x7A0 base remain unmodelled.
#ifndef CHARACTER_CCHARACTERMOTION_H
#define CHARACTER_CCHARACTERMOTION_H
#include "PHYSICS/cNetDynamicBody.h"
namespace CHARACTER
{
    class cCharacterMotion : public PHYSICS::cNetDynamicBody
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcCharacterMotionClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        // RuffKing names this fieldless prototype base; CD2's character prototype base occupies 0x280 bytes.
        class cCharacterMotionPrototype : public PHYSICS::cDynamicBody::cDynamicBodyPrototype
        {
        public:
            cCharacterMotionPrototype(const RWS::CAttributePacket &);
            // CD2: cCharacterMotionPrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            virtual void Slot3(); // cStreamingResourceClient 3: 0x8254DFE8
            virtual void Slot4(); // cStreamingResourceClient 4: 0x8254DF98
        public:
            CD2_LAYOUT_CHECKS(cCharacterMotionPrototype, CD2_SIZE(cCharacterMotionPrototype, 0x280))
        };
        // Own slots 314..346. Names/signatures are unresolved; CD2's last six entries are pure.
        virtual void vf314();
        virtual void vf315();
        virtual void vf316();
        virtual void vf317();
        virtual void vf318();
        virtual void vf319();
        virtual void vf320();
        virtual void vf321();
        virtual void vf322();
        virtual void vf323();
        virtual void vf324();
        virtual void vf325();
        virtual void vf326();
        virtual void vf327();
        virtual void vf328();
        virtual void vf329();
        virtual void vf330();
        virtual void vf331();
        virtual void vf332();
        virtual void vf333();
        virtual void vf334();
        virtual void vf335();
        virtual void vf336();
        virtual void vf337();
        virtual void vf338();
        virtual void vf339();
        virtual void vf340();
        virtual void vf341() = 0;
        virtual void vf342() = 0;
        virtual void vf343() = 0;
        virtual void vf344() = 0;
        virtual void vf345() = 0;
        virtual void vf346() = 0;
    private:
        unsigned char m_unmodelled7A0[0x11F0 - 0x7A0];
        CD2_LAYOUT_CHECKS(cCharacterMotion, CD2_SIZE(cCharacterMotion, 0x11F0))
    };
}
#endif

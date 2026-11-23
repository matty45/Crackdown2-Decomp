// STAND-IN: RuffKing base cChaseBehaviour; CD2 StaticCreateClass (0x824C90D8)
// gives 0x100 bytes, the same extent as the recovered chase base.
// Constructor 0x824C9180 (out of line, takes only this) calls cChaseBehaviour's and installs table 0x8210B510:
// 120 primary slots, one more than cChaseBehaviour's 119. Slot 119 (0x824C91F0) sets the flag at 0xF6 and calls
// SetState(2); RuffKing's cAgressiveResponseBase declares no new virtual, so its name is not known (vf119 is ours).
// cAgressiveResponseBasePrototype adds no storage (RuffKing: 144 bytes, like cChaseBehaviourPrototype).
#ifndef AI_CAGRESSIVERESPONSEBASE_H
#define AI_CAGRESSIVERESPONSEBASE_H
#include "AI/cChaseBehaviour.h"
namespace AI
{
    class cAgressiveResponseBase : public cChaseBehaviour
    {
    public:
        class cAgressiveResponseBasePrototype : public cChaseBehaviour::cChaseBehaviourPrototype
        {
        public:
            __forceinline cAgressiveResponseBasePrototype(const RWS::CAttributePacket &packet)
                : cChaseBehaviourPrototype(packet)
            {
            }
            // CD2: cAgressiveResponseBasePrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x824CC6F8
        };

        cAgressiveResponseBase();
        // Reference names; CD2 0x824C90B8 returns the class name and
        // 0x824C90C8 loads this class pointer from 0x8381FABC.
        virtual const char *RetClassName() const;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcAgressiveResponseBaseClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual void vf119();
        // CD2: cAgressiveResponseBase's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        // Correction: comparing CD2 tables 0x8210B510 and 0x8210BCA8 shows
        // that only RetClassName differs in primary slots 0..118; slot 119
        // is new here. Both constructors install the same event-handler,
        // script-host and net-role tables. The former declarations in this
        // block described cAgressiveResponseChaseBehaviour's overrides.
    public:
        CD2_LAYOUT_CHECKS(cAgressiveResponseBase, CD2_SIZE(cAgressiveResponseBase, 0x100))
    };
}
#endif

#include "gom/object_prototype.h"
#ifndef AI_REAPER_H
#define AI_REAPER_H

#include "gom/non_game_base.h"
#include "AI/FreakBase.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class Reaper : public FreakBase
    {
    public:
        // CD2 spawning initializer 0x82F93F90 names placement factory 0x824b26a8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        // CD2 0x824B27E0, out of line: SpawnFromPrototype tail-calls it with the prototype.
        Reaper(GOM::cObjectPrototype *prototype);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pReaperClass;

        Reaper();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        // RuffKing: Reaper::ReaperPrototype : FreakPrototype, 880 bytes. CD2's MakeNew (0x824B2640) allocates 0x370 and
        // calls this constructor (0x824B80A8), which calls FreakPrototype's (0x824B0B78).
        class ReaperPrototype : public FreakPrototype
        {
        public:
            ReaperPrototype(const RWS::CAttributePacket &);

        private:
            unsigned char m_unmodelledB0[0x370 - 0xB0];

            CD2_LAYOUT_CHECKS(ReaperPrototype,
                CD2_SIZE(ReaperPrototype, 0x370))
        };

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2: Reaper's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void OnEnter(); // 68: 0x824B2A38
        virtual void OnExit(); // 69: 0x824B2C30
        virtual void Slot71(); // 71: 0x824B5330
        virtual void Slot72(); // 72: 0x824B2CD8
        virtual void Slot80(unsigned char,unsigned char,unsigned char); // 80: 0x824B69F0
        virtual void Slot89(); // 89: 0x824B2D68
        virtual void Update(float); // 96: 0x824B2DB0
        virtual void SetState(int); // 99: 0x824B5518
        virtual void GetState(int); // 100: 0x824B4D38
        virtual void Slot101(); // 101: 0x824B2B08
        virtual void V104(); // 104: 0x824B3150
        virtual void V108(); // 108: 0x824B31F0
        virtual void Slot109(); // 109: 0x824B3760
        virtual void Slot110(); // 110: 0x824B3ED0
        virtual AI::NPCTarget * GetTarget(); // 115: 0x824B2E18
        virtual void V117(); // 117: 0x824B4CC0
        virtual void V118(); // 118: 0x824AE038
    };
}

#endif


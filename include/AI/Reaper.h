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
        // CD2 table 0x82109970 has 185 primary slots.
        virtual void vf179();
        virtual void vf180();
        virtual void vf181();
        virtual void vf182();
        virtual void vf183();
        virtual void vf184();

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

    public:
        // CD2 table 0x82109970 differs from FreakBase at these inherited slots.
        virtual void Slot85(); // slot 85: 0x824A8A90
        virtual void vf120(); // slot 120: 0x824B3278
        virtual void vf121(); // slot 121: 0x824ADFA0
        virtual void vf125(); // slot 125: 0x824B3058
        virtual void vf141(); // slot 141: 0x824B3940
        virtual void vf142(); // slot 142: 0x824B3D28
        virtual void vf147(); // slot 147: 0x824B30A8
        virtual void vf148(); // slot 148: 0x824B4C78
        virtual void vf152(); // slot 152: 0x824B35C0
        virtual void vf157(); // slot 157: 0x824B8050
        virtual void vf161(); // slot 161: 0x824B6D80
        virtual void vf162(); // slot 162: 0x824B7020
        virtual void vf165(); // slot 165: 0x824B7290
        virtual void vf166(); // slot 166: 0x824B6548
        virtual void vf171(); // slot 171: 0x824B65E8
        virtual void vf173(); // slot 173: 0x824B7F50

    public:
        // CD2 table 0x82109970 differs from FreakBase at these inherited slots.
        virtual void V102(); // slot 102: 0x824BACF0
        virtual void V106(); // slot 106: 0x824BB7B8
    };
}

#endif


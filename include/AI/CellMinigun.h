#include "gom/object_prototype.h"
#ifndef AI_CELLMINIGUN_H
#define AI_CELLMINIGUN_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "AI/NPCArmedBehaviour.h"
#include "cd2/layout.h"

namespace AI
{
    class CellMinigun : public NPCArmedBehaviour
    {
    public:
        // CD2 spawning initializer 0x82F95FC0 names placement factory 0x824c3228.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pCellMinigunClass;

        // __forceinline: CD2 inlines this constructor into SpawnFromPrototype (0x824C3228), which calls
        // NPCArmedBehaviour's constructor (0x824A8070) out of line and then initialises the fields below (names ours).
        __forceinline CellMinigun() : m_nUnknownF0(0) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

    private:
        unsigned int m_nUnknownF0; // 0xF0
        unsigned char m_unmodelledF4[0x100 - 0xF4];
        // 0x100: the size CellMinigun's class registrar gives.
        // CD2: CellMinigun's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Slot2(); // cSafeDeletable 2: 0x824C3C98
    private:
        CD2_LAYOUT_CHECKS(CellMinigun,
            CD2_SIZE(CellMinigun, 0x100)
            CD2_OFFSET(CellMinigun, m_nUnknownF0, 0xF0))

    public:
        // CD2 table 0x8200BED0 differs from NPCArmedBehaviour at these inherited slots.
        virtual void OnEnter(); // slot 68: 0x824C33D8
        virtual void OnExit(); // slot 69: 0x824C5648
        virtual void Slot71(); // slot 71: 0x824C3A48
        virtual void Slot73(); // slot 73: 0x824C35F8
        virtual void OnEvent74(NPCTarget *t); // slot 74: 0x824C3510
        virtual void OnEvent75(NPCTarget *t); // slot 75: 0x824C3728
        virtual void Slot79(); // slot 79: 0x824C34C0
        virtual void Slot83(); // slot 83: 0x824C41E8
        virtual void SetReactResupplyPoint(const Fun_Runtime::Vec3 &, const Fun_Runtime::Vec3 &); // slot 85: 0x824C3D30
        virtual void ChangeMainState(eState); // slot 98: 0x824C3870
        virtual void OnIdle(); // slot 102: 0x824C3B18
        virtual void OnInvestigating(); // slot 103: 0x824C3AB0
        virtual void OnPatrolling(); // slot 104: 0x824C3B68
        virtual void OnAttacking(); // slot 105: 0x824C3BB8
        virtual void OnCover(); // slot 106: 0x82580578
        virtual void OnAmbient(); // slot 109: 0x824C3C58
        virtual void OnDrive(); // slot 110: 0x82580578
    protected:
        // Reference method; CD2 ChangeMainState tail-calls 0x824C3888 with the new state.
        void OnEnterState(eState);
    };
}

#endif


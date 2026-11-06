// STAND-IN: RuffKing's base order and fields, confirmed by CD2 factory 0x82868D98.
// CD2 initializes the transform at 0x20, radius at 0x60 and active flag at 0x64.
#ifndef GameManagement_cMultiPlayerTriggerZone_H
#define GameManagement_cMultiPlayerTriggerZone_H
#include "rws/attributes.h"
#include "rws/systemcommands.h"
#include "fun_runtime/mtx.h"
namespace PLAYER { class cPlayer; }
namespace GameManagement
{
    class cMultiPlayerTriggerZone : public RWS::CSystemCommands, public RWS::CAttributeHandler
    {
    protected:
        Fun_Runtime::Mtx m_mTransform;
        float m_fRadius;
        bool m_bActive;
    public:
        // CD2 inlines this construction into MakeNew.
        __forceinline cMultiPlayerTriggerZone(const RWS::CAttributePacket &)
            : m_fRadius(10.0f), m_bActive(false) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void Destruct();
        virtual void InitTriggerZone();
        virtual void TermTriggerZone();
    protected:
        virtual bool CanTrigger(PLAYER::cPlayer *);
        CD2_LAYOUT_CHECKS(cMultiPlayerTriggerZone,
            CD2_SIZE(cMultiPlayerTriggerZone, 0x70)
            CD2_OFFSET(cMultiPlayerTriggerZone, m_mTransform, 0x20)
            CD2_OFFSET(cMultiPlayerTriggerZone, m_fRadius, 0x60)
            CD2_OFFSET(cMultiPlayerTriggerZone, m_bActive, 0x64))
    };
}
#endif

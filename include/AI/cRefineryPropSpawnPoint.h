// AI::cRefineryPropSpawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x824586F8, MakeNew 0x82458790, from its registrars in CD2's
// initializer run); RuffKing names the class in cRefineryPropSpawnPoint.obj. No layout or virtuals are modelled yet;
// base AI::cMissionCriticalPropSpawnPoint from CD2's inheritance registrar. Fields: RuffKing's, 0x30 below its offsets
// (its base is 0x2D0 in CD2); they end at 0x2E0, the size CD2's registrar gives (RuffKing's 0x310 less 0x30).
#ifndef AI_CREFINERYPROPSPAWNPOINT_H
#define AI_CREFINERYPROPSPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "AI/cMissionCriticalPropSpawnPoint.h"
#include "fun_runtime/pointer_list.h"

namespace AI
{
    class cAttachableLight;

    class cRefineryPropSpawnPoint : public cMissionCriticalPropSpawnPoint
    {
    public:
        // CD2 0x82458688 / 0x82458698: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcRefineryPropSpawnPointClass;
        // CD2 0x823B62E8 (outside the scaffolded files); MakeNew applies the packet afterwards.
        cRefineryPropSpawnPoint();

    private:
        Fun_Runtime::cPointerList<cAttachableLight *> m_lLights;
        unsigned int m_nLightActivationTime;

        CD2_LAYOUT_CHECKS(cRefineryPropSpawnPoint,
            CD2_SIZE(cRefineryPropSpawnPoint, 0x2E0)
            CD2_OFFSET(cRefineryPropSpawnPoint, m_lLights, 0x2D0)
            CD2_OFFSET(cRefineryPropSpawnPoint, m_nLightActivationTime, 0x2DC))
    };
}

#endif // AI_CREFINERYPROPSPAWNPOINT_H

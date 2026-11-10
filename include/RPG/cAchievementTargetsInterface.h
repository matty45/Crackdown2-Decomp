// RPG::cAchievementTargetsInterface (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x827775C0, from its registrars in CD2's
// initializer run); RuffKing names the class in cAchievementTargets.obj. No layout or virtuals are modelled yet.
#ifndef RPG_CACHIEVEMENTTARGETSINTERFACE_H
#define RPG_CACHIEVEMENTTARGETSINTERFACE_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace RPG
{
    // Burn derives this data interface directly from CAttributeHandler. CD2's
    // 0x18-byte allocation at 0x827775C0 confirms that it adds no instance fields.
    class cAchievementTargetsInterface : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        cAchievementTargetsInterface(const RWS::CAttributePacket &) {}
        virtual ~cAchievementTargetsInterface();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        // CD2 0x82147AF8 has this virtual in slot 11, followed by Destruct.
        virtual const char *RetClassName() const;
        virtual void Destruct();

        // CD2: cAchievementTargetsInterface's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual bool HandleDataInNewDesignBuild(); // 9: 0x8288FB78
    public:
        CD2_LAYOUT_CHECKS(cAchievementTargetsInterface,
            CD2_SIZE(cAchievementTargetsInterface, 0x18))
    };
}

#endif // RPG_CACHIEVEMENTTARGETSINTERFACE_H

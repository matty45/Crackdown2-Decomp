// CHARACTER::cWingSuitUpdraftZoneProfile (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x82728400, from its registrars in CD2's
// initializer run); RuffKing names the class in cWingSuitUpdraftZone.obj. No layout or virtuals are modelled yet.
#ifndef CHARACTER_CWINGSUITUPDRAFTZONEPROFILE_H
#define CHARACTER_CWINGSUITUPDRAFTZONEPROFILE_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "editor/guid_event_handler.h"

namespace CHARACTER
{
    // Burn's base agrees with the five base-field clears in CD2 0x82728400.
    // Instance fields remain unmodelled.
    class cWingSuitUpdraftZoneProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // CD2 0x82728400 initializes the handler then four zero float defaults.
        cWingSuitUpdraftZoneProfile(const RWS::CAttributePacket &)
            : m_fHeight(0.0f), m_fRadius(0.0f), m_fBottomForce(0.0f), m_fTopForce(0.0f) {}
        virtual ~cWingSuitUpdraftZoneProfile();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        // CD2 table 0x8213D6AC, slot 11.
        virtual const char *RetClassName() const;
        virtual void Destruct();

    public:
        Editor::cGUIDEventHandler<cWingSuitUpdraftZoneProfile> m_EventHandler;

    protected:
        // Burn names and layout, confirmed by CD2's four stores at +0x2C..+0x38.
        float m_fHeight;
        float m_fRadius;
        float m_fBottomForce;
        float m_fTopForce;

        CD2_LAYOUT_CHECKS(cWingSuitUpdraftZoneProfile,
            CD2_SIZE(cWingSuitUpdraftZoneProfile, 0x3C)
            CD2_OFFSET(cWingSuitUpdraftZoneProfile, m_EventHandler, 0x18)
            CD2_OFFSET(cWingSuitUpdraftZoneProfile, m_fHeight, 0x2C)
            CD2_OFFSET(cWingSuitUpdraftZoneProfile, m_fRadius, 0x30)
            CD2_OFFSET(cWingSuitUpdraftZoneProfile, m_fBottomForce, 0x34)
            CD2_OFFSET(cWingSuitUpdraftZoneProfile, m_fTopForce, 0x38))
    };
}

#endif // CHARACTER_CWINGSUITUPDRAFTZONEPROFILE_H

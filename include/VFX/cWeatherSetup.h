// VFX::cWeatherSetup (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x827D7A08, from its registrars in CD2's
// initializer run); RuffKing names the class in cWeather.obj. No layout or virtuals are modelled yet.
#ifndef VFX_CWEATHERSETUP_H
#define VFX_CWEATHERSETUP_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "editor/guid_event_handler.h"

namespace VFX
{
    // Burn's base agrees with the five base-field clears in CD2 0x827D7A08.
    // Instance fields remain unmodelled.
    class cWeatherSetup : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        cWeatherSetup(const RWS::CAttributePacket &) {}
        virtual ~cWeatherSetup();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        // CD2 table 0x8215166C, slot 11.
        virtual const char *RetClassName() const;
        virtual void Destruct();

    protected:
        // Burn member names and offsets; CD2 0x827D7A08 initializes the handler
        // at +0x18 and leaves the fourteen weather values uninitialized.
        Editor::cGUIDEventHandler<cWeatherSetup> m_EventHandler;
        float m_Data[14];

        CD2_LAYOUT_CHECKS(cWeatherSetup,
            CD2_SIZE(cWeatherSetup, 0x64)
            CD2_OFFSET(cWeatherSetup, m_EventHandler, 0x18)
            CD2_OFFSET(cWeatherSetup, m_Data, 0x2C))
    };
}

#endif // VFX_CWEATHERSETUP_H

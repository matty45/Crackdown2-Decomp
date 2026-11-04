#include "fun_runtime/class.h"
// STAND-IN: RuffKing base order; CD2 subobjects at 0x250, 0x294; positional proxy starts at 0x420.
#ifndef CD2_PHYSICS_CDYNAMICBODY_H
#define CD2_PHYSICS_CDYNAMICBODY_H
#include "PHYSICS/cBody.h"
#include "PHYSICS/cIgnitable.h"
#include "Havok/hkEntityActivationListener.h"
namespace PHYSICS
{
    class cDynamicBody : public cBody, public cIgnitable, public hkEntityActivationListener
    {
    public:
        // Interface-only prototype stand-in: name and base from RuffKing.
        // Instance fields and complete size are not recovered; this is not an allocation layout.
        class cDynamicBodyPrototype : public cBody::cBodyPrototype {};

        // CD2 0x82684C80 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual ~cDynamicBody();
        virtual void entityDeactivatedCallback(hkEntity *);
        virtual void entityActivatedCallback(hkEntity *);
    private:
        unsigned char m_unknown298[0x420 - 0x298];
        CD2_LAYOUT_CHECKS(cDynamicBody, CD2_SIZE(cDynamicBody, 0x420))
    };
}
#endif

// Fun_Runtime::cScriptHost: CD2's 0x1C-byte script interface, identified by its class
// descriptor at 0x8276ED30 (class ID 1009, name cScriptHost, size 0x1C).
// The destructor at 0x8276F0C0 restores the primary vtable at +0 and the registered
// interface vtable at +0x14, then calls cSafeDeletable's destructor (0x8264B398).
// cNonGameBase embeds this base at +0x1C. The byte flag at +0x18 is initialized
// to false; its meaning is not established. Slot names remain stand-ins except
// RetPosition, RetName, RetClass and IsA, whose behavior identifies them.
#ifndef FUN_RUNTIME_SCRIPTHOST_H
#define FUN_RUNTIME_SCRIPTHOST_H
#include "fun_runtime/safedeletable.h"
#include "fun_runtime/class.h"
namespace Fun_Runtime {
class cScriptHost : public cSafeDeletable, public cRegisteredClass {
public:
    cScriptHost() : m_bFlag(false) {}
    virtual ~cScriptHost();
    virtual void Slot1();
    virtual void Slot2();
    virtual Vec3 RetPosition() const;
    virtual const char *RetName() const;
    virtual void Slot5();
    virtual const cClass &RetClass() const;
    virtual bool IsA(const cClass &) const;
private:
    bool m_bFlag;
public:
    CD2_LAYOUT_CHECKS(cScriptHost,
        CD2_SIZE(cScriptHost, 0x1C)
        CD2_OFFSET(cScriptHost, m_bFlag, 0x18))
};
}
#endif

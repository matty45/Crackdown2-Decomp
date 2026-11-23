// STAND-IN: standalone manager type from RuffKing, with one virtual destructor.
// CD2's descriptor factory 0x82677F58 names cGangManager and gives size 0x50;
// table 0x8212EA48 contains its deleting destructor at 0x82677FF0.
// CD2 cFactionConfigData::HandleAttributes indexes the faction pointers at 0x30.
#ifndef GANGMANAGER_CGANGMANAGER_H
#define GANGMANAGER_CGANGMANAGER_H
#include "fun_runtime/class.h"
#include "fun_runtime/scripthost.h"
#include "fun_runtime/vectorip.h"
#include "cd2/layout.h"
// Reconstruction update: initialization in CD2 0x825D2300 constructs cScriptHost
// at +0 (safe-pointer sentinel +4, registered interface +0x14, flag +0x18).
// The primary table 0x8212EA48 has six script-host slots; table 0x8212EA60
// supplies RetClass/IsA. Inheritance registrar 0x82FDD638 confirms cScriptHost.
// Reference m_vFactionInfo is the six-entry inline vector: CD2 initializes its
// last pointer at +0x20 to the inline storage at +0x30. No opaque base padding.
namespace GangManager
{
    class cFactionInfo;
    __declspec(align(16)) class cGangManager : public Fun_Runtime::cScriptHost
    {
    public:
        virtual ~cGangManager();
        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2 initializer 0x82FDD610 writes this pointer at 0x83840678.
        static const Fun_Runtime::cClass *ms_pcGangManagerClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static cGangManager *sm_pGangManager;
        static cGangManager *RetGangManager() { return sm_pGangManager; }
    public:
        Fun_Runtime::cVectorip<cFactionInfo *, 6> m_vFactionInfo;
    private:
        CD2_LAYOUT_CHECKS(cGangManager, CD2_OFFSET(cGangManager, m_vFactionInfo, 0x20) CD2_SIZE(cGangManager, 0x50))
    };
}
#endif

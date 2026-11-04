#include "GDb/cDebugPageHandler.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "rws/classfactory.h"
#include "WorldManager/cWorldManager.h"

namespace WorldManager
{
    const char *cWorldManager::RetClassName() const
    {
        return "cWorldManager";
    }
}

#include "cd2/memory.h"

namespace WorldManager
{
    Fun_Runtime::cClass &cWorldManager::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cWorldManagerClass = new Fun_Runtime::cClass(0x60D, "cWorldManager", 0x5DA0);
        return *cWorldManagerClass;
    }
}

namespace WorldManager
{
    const Fun_Runtime::cClass *cWorldManager::ms_pcWorldManagerClass = &cWorldManager::StaticCreateClass();
}

namespace WorldManager
{
    static RWS::CClassFactory::CRegistrar cWorldManagerRegistrar(
        "cWorldManager", cWorldManager::MakeNew, 0x5DA0, false);
}

// CD2 0x8300CFA8: runtime class inheritance registration.
namespace WorldManager
{
    static Fun_Runtime::cInheritanceRegistrar cWorldManagercNonGameBaseInheritRegistrar(
        WorldManager::cWorldManager::StaticCreateClass(), cNonGameBase::StaticCreateClass());
}

// CD2 0x8300D010: runtime class inheritance registration.
namespace WorldManager
{
    static Fun_Runtime::cInheritanceRegistrar cWorldManagercDebugPageHandlerInheritRegistrar(
        WorldManager::cWorldManager::StaticCreateClass(), GDb::cDebugPageHandler::StaticCreateClass());
}

// CD2 0x82809AD8: the class-factory constructor; the constructor stays out of line.
namespace WorldManager
{
    RWS::CAttributeHandler *cWorldManager::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cWorldManager;
    }
}

#include "WorldManager/cWorldManager.h"
#include "fun_runtime/script_type_registrar.h"

namespace WorldManager
{
    // CD2 script-type registration; constructor/table evidence identifies the child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cWorldManager> cWorldManagerScriptRegistrar(
        "cWorldManager", "cNonGameBase");
}

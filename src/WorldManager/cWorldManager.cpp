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
